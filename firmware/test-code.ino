#include <WiFi.h>
#include <WebServer.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <DHT.h>
#include <Preferences.h>

// ==========================================
// 1. ZUGANGSDATEN & HARDWARE
// ==========================================
const char* ssid_global = "FRITZ!Box 7530 NM";
const char* pass_global = "07715701272720165098";

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

#define DHTPIN 4
#define DHTTYPE DHT22
#define MQ135_PIN 34
#define MQ9_PIN 35
#define PM_LED_PIN 23
#define PM_VO_PIN 36
#define BTN_L 18
#define BTN_R 19
#define ESC_PIN 25 // Falls du später den Motor-Pin nutzt

DHT dht(DHTPIN, DHTTYPE);
WebServer server(80);
Preferences prefs;

// ==========================================
// 2. CONFIG & VARIABLEN
// ==========================================
struct Config {
  int manDur;       // Sekunden
  int manSpd;       // 0-100%
  int maxLimit;     // 0-100% Hardware-Bremse
  int t135, t9, tPM; 
  float ramp;       // 0.1 - 5.0
  bool startStop;   // Not-Aus bei Boot?
};
Config cfg;

bool emergencyStop = false;
bool manualMode = false;
int viewMode = 0; // 0=Dash, 1=MQ135, 2=MQ9, 3=PM, 4=Speed
float valT, valH;
int val135, val9, valPM;
float targetSpeed = 0;   // Logische Speed (0-100)
float currentSpeed = 0;  // Physikalische Speed (mit Rampe)

unsigned long manStart = 0;
unsigned long lastSens = 0;
unsigned long btnL_time = 0, btnR_time = 0;
bool blockL = false, blockR = false;

// ==========================================
// 3. SPEICHER FUNKTIONEN
// ==========================================
void saveToFlash() {
  prefs.begin("airpro", false);
  prefs.putInt("dur", cfg.manDur);
  prefs.putInt("mspd", cfg.manSpd);
  prefs.putInt("mlim", cfg.maxLimit);
  prefs.putInt("t135", cfg.t135);
  prefs.putInt("t9", cfg.t9);
  prefs.putInt("tpm", cfg.tPM);
  prefs.putFloat("rmp", cfg.ramp);
  prefs.putBool("ss", cfg.startStop);
  prefs.end();
}

void loadFromFlash() {
  prefs.begin("airpro", true);
  cfg.manDur = prefs.getInt("dur", 60);
  cfg.manSpd = prefs.getInt("mspd", 50);
  cfg.maxLimit = prefs.getInt("mlim", 80); // Standard auf 80% zum Schutz
  cfg.t135 = prefs.getInt("t135", 800);
  cfg.t9 = prefs.getInt("t9", 1000);
  cfg.tPM = prefs.getInt("tpm", 150);
  cfg.ramp = prefs.getFloat("rmp", 0.5);
  cfg.startStop = prefs.getBool("ss", false);
  prefs.end();
}

// ==========================================
// 4. WEB INTERFACE
// ==========================================
String makeHTML() {
  String h = "<!DOCTYPE html><html><head><meta charset='UTF-8'><title>AIR-PRO PLATINUM</title>";
  h += "<style>body{background:#0f0f0f;color:#00ffcc;font-family:monospace;text-align:center;}";
  h += ".card{background:#1a1a1a;border:2px solid #00ffcc;border-radius:15px;padding:20px;margin:15px auto;max-width:450px;}";
  h += "input{background:#000;color:#0f0;border:1px solid #0ff;padding:5px;width:80px;text-align:center;}";
  h += ".btn{background:#00ffcc;color:#000;padding:12px;border:none;border-radius:8px;font-weight:bold;cursor:pointer;width:100%;}";
  h += "</style></head><body>";
  h += "<h1>--- AIR-PRO SYSTEM V5 ---</h1>";
  h += "<div class='card'><h2>LIVE DATA</h2>";
  h += "MODUS: " + String(emergencyStop ? "!!! NOT-AUS !!!" : (manualMode ? "MANUELL" : "AUTOMATIK")) + "<br>";
  h += "TURBINE: " + String((int)targetSpeed) + "% (Real: " + String((int)(currentSpeed)) + "%)</div>";
  
  h += "<form class='card' action='/save'>";
  h += "<h3>SYSTEM SETTINGS</h3>";
  h += "Hardware Max Speed (%): <input name='lim' value='"+String(cfg.maxLimit)+"'><br><br>";
  h += "Beschleunigung (Ramp): <input name='rmp' value='"+String(cfg.ramp, 2)+"'><br><br>";
  h += "Manuell Dauer (Sek): <input name='dur' value='"+String(cfg.manDur)+"'><br><br>";
  h += "Schwellenwert MQ135: <input name='t1' value='"+String(cfg.t135)+"'><br>";
  h += "Schwellenwert MQ9: <input name='t9' value='"+String(cfg.t9)+"'><br>";
  h += "Schwellenwert PM2.5: <input name='tp' value='"+String(cfg.tPM)+"'><br><br>";
  h += "Start mit Not-Aus: <input type='checkbox' name='ss' "+String(cfg.startStop?"checked":"")+"><br><br>";
  h += "<button class='btn' type='submit'>EINSTELLUNGEN SPEICHERN</button></form>";
  h += "</body></html>";
  return h;
}

// ==========================================
// 5. SETUP
// ==========================================
void setup() {
  Serial.begin(115200);
  loadFromFlash();
  emergencyStop = cfg.startStop;

  Wire.begin(21, 22);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  dht.begin();
  
  pinMode(BTN_L, INPUT_PULLUP); 
  pinMode(BTN_R, INPUT_PULLUP);
  pinMode(PM_LED_PIN, OUTPUT);
  pinMode(MQ135_PIN, INPUT);
  pinMode(MQ9_PIN, INPUT);

  WiFi.begin(ssid_global, pass_global);
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setCursor(0,20); display.print("Connect WiFi...");
  display.display();

  while(WiFi.status() != WL_CONNECTED) { delay(500); Serial.print("."); }

  server.on("/", [](){ server.send(200, "text/html", makeHTML()); });
  server.on("/save", [](){
    cfg.maxLimit = server.arg("lim").toInt();
    cfg.ramp = server.arg("rmp").toFloat();
    cfg.manDur = server.arg("dur").toInt();
    cfg.t135 = server.arg("t1").toInt();
    cfg.t9 = server.arg("t9").toInt();
    cfg.tPM = server.arg("tp").toInt();
    cfg.startStop = server.hasArg("ss");
    saveToFlash();
    server.send(200, "text/html", "Gespeichert! Restart...");
    delay(1000); ESP.restart();
  });
  server.begin();
}

// ==========================================
// 6. HAUPTSCHLEIFE
// ==========================================
void loop() {
  server.handleClient();
  
  // Sensoren (Alle 2 Sekunden)
  if (millis() - lastSens > 2000) {
    valT = dht.readTemperature(); valH = dht.readHumidity();
    val135 = analogRead(MQ135_PIN); val9 = analogRead(MQ9_PIN);
    
    // PM Messung
    digitalWrite(PM_LED_PIN, LOW); delayMicroseconds(280);
    valPM = analogRead(PM_VO_PIN); delayMicroseconds(40);
    digitalWrite(PM_LED_PIN, HIGH);
    lastSens = millis();
  }

  handleButtons();
  
  // Motor Logik
  if (emergencyStop) {
    targetSpeed = 0;
  } else if (manualMode) {
    if (millis() - manStart > cfg.manDur * 1000) manualMode = false;
    else targetSpeed = cfg.manSpd;
  } else {
    // Automatik mit Grenzwerten
    float s135 = (val135 > cfg.t135) ? map(val135, cfg.t135, 4095, 10, 100) : 0;
    float s9 = (val9 > cfg.t9) ? map(val9, cfg.t9, 4095, 10, 100) : 0;
    float sPM = (valPM > cfg.tPM) ? map(valPM, cfg.tPM, 1024, 10, 100) : 0;
    targetSpeed = max(s135, max(s9, sPM));
  }

  // Physikalische Rampe & Scaling
  float realTarget = (targetSpeed * cfg.maxLimit / 100.0);
  if (currentSpeed < realTarget) currentSpeed += cfg.ramp;
  if (currentSpeed > realTarget) currentSpeed -= cfg.ramp;
  currentSpeed = constrain(currentSpeed, 0, cfg.maxLimit);

  updateDisplay();
}

// ==========================================
// 7. BUTTON LOGIK
// ==========================================
void handleButtons() {
  bool l = digitalRead(BTN_L) == LOW;
  bool r = digitalRead(BTN_R) == LOW;
  unsigned long now = millis();

  // NOT-AUS UNLOCK (BEIDE DRÜCKEN > 2 SEK)
  if (l && r) {
    if (btnR_time == 0) btnR_time = now;
    if (now - btnR_time > 2000) { emergencyStop = false; manualMode = false; }
    return;
  }

  // LINKS: Lang = Not-Aus / Kurz = Manuell
  if (l && !r) {
    if (btnL_time == 0) btnL_time = now;
    if (now - btnL_time > 2000) emergencyStop = true;
  } else if (!l && btnL_time > 0) {
    if (now - btnL_time < 500 && !emergencyStop) {
      manualMode = !manualMode; manStart = now;
    }
    btnL_time = 0;
  }

  // RECHTS: Kurz = Menü
  if (r && !l) {
    if (btnR_time == 0) btnR_time = now;
  } else if (!r && btnR_time > 0) {
    if (now - btnR_time < 500 && !emergencyStop) viewMode = (viewMode + 1) % 5;
    btnR_time = 0;
  }
}

// ==========================================
// 8. DISPLAY
// ==========================================
void updateDisplay() {
  display.clearDisplay();
  if (emergencyStop) {
    display.fillRect(0,0,128,64,WHITE); display.setTextColor(BLACK);
    display.setTextSize(2); display.setCursor(20,25); display.print("STOP!");
    display.display(); return;
  }

  display.setTextColor(WHITE); display.setTextSize(1);
  display.setCursor(0,0); display.print(WiFi.localIP()); 
  display.setCursor(100,0); display.print(manualMode ? "MAN" : "AUT");
  display.drawFastHLine(0, 10, 128, WHITE);

  int y = 20;
  switch(viewMode) {
    case 0: // DASHBOARD
      display.setCursor(0,y); display.print("TEMP: "); display.print(valT,1); display.print("C");
      display.setCursor(0,y+10); display.print("HUM : "); display.print(valH,1); display.print("%");
      display.setCursor(0,y+25); display.print("Turbine: "); display.print((int)targetSpeed); display.print("%");
      break;
    case 1: // MQ135
      display.setCursor(0,y); display.print("MQ135 (LUFT)");
      display.setCursor(0,y+15); display.setTextSize(2); display.print(val135);
      break;
    case 2: // MQ9
      display.setCursor(0,y); display.print("MQ9 (GAS/CO)");
      display.setCursor(0,y+15); display.setTextSize(2); display.print(val9);
      break;
    case 3: // PM2.5
      display.setCursor(0,y); display.print("PM2.5 (STAUB)");
      display.setCursor(0,y+15); display.setTextSize(2); display.print(valPM);
      break;
    case 4: // MOTOR DETAIL
      display.setCursor(0,y); display.print("TURBINEN SPEED");
      display.setCursor(0,y+12); display.print("Ziel: "); display.print((int)targetSpeed); display.print("%");
      display.setCursor(0,y+22); display.print("Real: "); display.print((int)currentSpeed); display.print("%");
      display.drawRect(0, 55, 128, 8, WHITE);
      display.fillRect(2, 57, map((int)currentSpeed, 0, cfg.maxLimit, 0, 124), 4, WHITE);
      break;
  }
  display.display();
}

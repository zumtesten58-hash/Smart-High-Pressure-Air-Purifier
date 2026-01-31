#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <DHT.h>

// Display Einstellungen
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// Pins für Sensoren
#define DHTPIN 4
#define DHTTYPE DHT22
#define MQ135_PIN 34
#define MQ9_PIN 35

// Pins für Taster
#define BTN_L 18
#define BTN_R 19

DHT dht(DHTPIN, DHTTYPE);

// Variablen
int viewMode = 0; // 0: Klima, 1: Gas, 2: PM Sensor
float temp = 0, hum = 0;
unsigned long lastSensorRead = 0;

void setup() {
  Serial.begin(115200);
  
  // I2C Stabilisierung für das Display
  Wire.begin(21, 22);
  Wire.setClock(100000); // 100kHz für bessere Stabilität

  pinMode(BTN_L, INPUT_PULLUP);
  pinMode(BTN_R, INPUT_PULLUP);
  
  dht.begin();

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("OLED nicht gefunden"));
    for(;;); 
  }
  
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.display();
}

void loop() {
  // Navigation mit L und R Tastern
  if(digitalRead(BTN_L) == LOW) { 
    viewMode--; 
    if(viewMode < 0) viewMode = 2;
    delay(250); // Entprellen
  }
  if(digitalRead(BTN_R) == LOW) { 
    viewMode++; 
    if(viewMode > 2) viewMode = 0;
    delay(250); // Entprellen
  }

  // DHT22 alle 2 Sek auslesen (verhindert Abstürze)
  if (millis() - lastSensorRead > 2000) {
    float t = dht.readTemperature();
    float h = dht.readHumidity();
    if (!isnan(t) && !isnan(h)) {
      temp = t;
      hum = h;
    }
    lastSensorRead = millis();
  }

  // Display-Ausgabe
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0,0);
  display.print("SENSOR-HUB");
  display.drawFastHLine(0, 10, 128, WHITE);

  switch(viewMode) {
    case 0: // DHT22 Ansicht
      display.setCursor(0, 20);
      display.print("KLIMA (DHT22)");
      display.setTextSize(2);
      display.setCursor(0, 35);
      display.print(temp, 1); display.print(" C");
      display.setCursor(0, 50);
      display.print(hum, 1); display.print(" %");
      break;

    case 1: // MQ Gassensoren Ansicht
      display.setCursor(0, 20);
      display.print("LUFTQUALITAET");
      display.setTextSize(1);
      display.setCursor(0, 35);
      display.print("MQ-135 (Luft): "); display.print(analogRead(MQ135_PIN));
      display.setCursor(0, 50);
      display.print("MQ-9   (Gas) : "); display.print(analogRead(MQ9_PIN));
      break;

    case 2: // PM2.5 Sensor
  display.setCursor(0, 20);
  display.print("PM2.5 SENSOR");
  display.setTextSize(1); // Hier Größe 1 statt 2
  display.setCursor(0, 35);
  display.print("Status:NOT BOUGHT YET"); 
  display.setCursor(0, 50);
  display.print("Need Tier 3 for this.");
  break;
  }

  display.display();
  delay(30); 
}
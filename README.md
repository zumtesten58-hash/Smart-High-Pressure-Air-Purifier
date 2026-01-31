# High-Pressure Air Purifier
## Since soldering produces so many fumes, I am building an air purifier with an ESP32. The MQ9 measures carbon monoxide, the MQ135 measures carbon dioxide and smoke, and I am also using a Sharp GP2Y1014AU0F to measure dust and smoke. The DHT 22 measures the temperature and humidity for information purposes.
###  Der ESP32 stellt die Daten auf einem SSD1306 128×64 dar. mit zwei Tastern kann man das Menü steuern. 
#### Functions:
I can navigate through the menu with the right button. I can display the raw data and see how fast (in percent) the motor is turning. I can see the ‘actual’ speed of the motor and the target speed, which affects the start-up speed. If I have limited the power to 50% on the website and the values are very poor, then the actual speed is 50% and the target speed is 100%. I can also set the thresholds on the website.
I can briefly press the left button to turn manual mode on or off. The time and strength can also be set manually. Holding down the button activates the emergency stop. To release it, you have to hold down both buttons for a long time. It can also be set so that the ESP32 always starts in emergency stop mode. 

#### I use a concrete base, then an M6 threaded rod and a TPU 90A for the transition, then the 3D-printed ASA housing.

### shopping list
| Part | Purpose | Link | Price |
| :--- | :--- | :--- | :--- |
|12V power supply unit | energy supply | https://amzn.eu/d/dqCZdYm | 22,14€ |
| L44 batteries | sliding gauge | https://amzn.eu/d/d7gHaOU | 4,02€ |
| 30A ESC with BEC | Motor controller, power supply | [Link]([url](https://de.aliexpress.com/item/1000005040945.html?spm=a2g0o.cart.0.0.5e634ae4sCWPP5&mp=1&pdp_npi=6%40dis%21EUR%21EUR%204.23%21EUR%204.23%21%21EUR%204.23%21%21%21%40211b617b17698548923824789e168b%2112000020358468972%21ct%21AT%214782931091%21%211%210%21&gatewayAdapt=glo2deu)) | 4,23€ |

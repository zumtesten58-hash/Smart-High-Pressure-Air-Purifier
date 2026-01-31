# High-Pressure Air Purifier
## Since soldering produces so many fumes, I am building an air purifier with an ESP32. The MQ9 measures carbon monoxide, the MQ135 measures carbon dioxide and smoke, and I am also using a Sharp GP2Y1014AU0F to measure dust and smoke. The DHT 22 measures the temperature and humidity for information purposes.
###  The ESP32 displays the data on an SSD1306 128×64. The menu can be controlled using two buttons.
#### Functions:
I can navigate through the menu with the right button. I can display the raw data and see how fast (in percent) the motor is turning. I can see the ‘actual’ speed of the motor and the target speed, which affects the start-up speed. If I have limited the power to 50% on the website and the values are very poor, then the actual speed is 50% and the target speed is 100%. I can also set the thresholds on the website.
I can briefly press the left button to turn manual mode on or off. The time and strength can also be set manually. Holding down the button activates the emergency stop. To release it, you have to hold down both buttons for a long time. It can also be set so that the ESP32 always starts in emergency stop mode. 

### I will use it to extract and filter the bad air directly during soldering.
#### I use a concrete base, then an M6 threaded rod and a TPU 90A for the transition, then the 3D-printed ASA housing.

### shopping list
| Part | Purpose | Link | Price |
| :--- | :--- | :--- | :--- |
|12V power supply unit | energy supply | https://amzn.eu/d/dqCZdYm | **22,14€** |
| L44 batteries | sliding gauge | https://amzn.eu/d/d7gHaOU | **4,02€** |
| 30A ESC with BEC | Motor controller, power supply | [AliExpress Link](https://de.aliexpress.com/item/1000005040945.html)| **4,23€** |
| Hepa filter | First filter + 5 replacement filters | [AliExpress Link](https://de.aliexpress.com/item/1005006072703241.html) | **4,51€** |
| GP2Y1014AU0F| dust sensor | [AliExpress Link](https://de.aliexpress.com/item/1005006072703241.html) | **3,69€**|
| **TOTAL** | | | **38,59€** |

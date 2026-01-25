# Smart High-Pressure Air Purifier (ESP32 Powered)

## Overview
This project is a high-performance modular air purifier. Unlike standard purifiers, it is designed for maximum static pressure to overcome dense HEPA filtration using a 7.4V brushless motor at 12V.

## Mechanical Innovation: Stability & Silencing
To handle the high RPM of the brushless motor, the design includes:
* **Concrete-Weighted Base:** I am using a concrete core with an M6 threaded rod to provide mass and lower the center of gravity.
* **TPU Vibration Dampening:** Custom TPU gaskets are used between the motor mount and the frame to isolate high-frequency vibrations.

## Current Progress
* **Electronics:** Successfully soldered logic level shifters (voltage dividers) to safely interface 5V sensors with the 3.3V ESP32.
* **ESC Integration:** Using a 30A ESC with BEC to control the motor speed via PWM.
* **CAD Design:** Initial block-out model in Fusion 360 to plan the airflow and the 50° OLED mount.

## Bill of Materials (BOM)

| Item | Source | Purpose | Price |
| :--- | :--- | :--- | :--- |
| **12V 20A Power Supply** | Amazon | Main system power | €22.14 |
| **LR44 Batteries (20x)** | Amazon | For digital calipers (precision measurements) | €4.02 |
| **Nobufil ASA Filament** | Nobufil | Heat-resistant housing | €31.66 |
| **AliExpress Bundle** | AliExpress | ESC, HEPA Filter, PM Sensor | €10.74 |
| **Total** | | | **€68.56** |

## Notes for Reviewers
The concrete base and TPU gaskets are essential to manage the vibrations of the custom turbine. I am also using LR44 batteries for my calipers to ensure the 3D-printed parts fit the M6 rod and motor perfectly.

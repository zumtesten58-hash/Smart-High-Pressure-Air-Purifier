# Smart High-Pressure Air Purifier (ESP32 Powered)

## Overview
This project is a high-performance modular air purifier designed for maximum static pressure to overcome dense HEPA filtration. I am using an ESP32 to control a 7.4V brushless motor running at 12V for high-RPM performance.

## Current Progress
* **Electronics:** Successfully soldered logic level shifters (voltage dividers) using 1% metal film resistors to safely interface 5V sensors with the 3.3V ESP32.
* **ESC Integration:** Using a 30A ESC with BEC to control the brushless motor speed via PWM from the ESP32.
* **CAD Design:** Initial block-out model in Fusion 360 to plan the 50° OLED display mount and internal airflow.
* **Mechanics:** Planned a concrete-weighted base with an M6 threaded rod core for vibration dampening.

## Bill of Materials (BOM)

| Item | Source | Purpose | Price |
| :--- | :--- | :--- | :--- |
| **12V 20A Power Supply** | Amazon | Main system power | €22.14 |
| **30A ESC (Brushless Controller)** | AliExpress | Motor speed control | €4.29 |
| **LR44 Batteries (20x)** | Amazon | For digital calipers (precision measurements) | €4.02 |
| **Nobufil ASA Filament** | Nobufil | Heat-resistant housing | €31.66 |
| **HEPA Filters & PM Sensor** | AliExpress | Air filtration and monitoring | €10.74 |
| **Total** | | | **€72.85** |

## Notes for Reviewers
The LR44 batteries are essential because my digital calipers are out of power. I need them for exact physical measurements of the motor and ESC to ensure a perfect fit in the 3D-printed housing.

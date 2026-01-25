# Smart High-Pressure Air Purifier (ESP32 Powered)

## Overview
This project is a high-performance modular air purifier designed for maximum static pressure to overcome dense HEPA filtration. I am using an ESP32 to control a 7.4V brushless motor running at 12V for high-RPM performance.

## Current Progress
* **Electronics:** Successfully soldered logic level shifters (voltage dividers) using 1% metal film resistors to safely interface 5V sensors with the 3.3V ESP32.
* **ESC & Motor Control:** Using a 30A ESC with BEC to drive the brushless motor via PWM signals.
* **CAD Design:** Initial block-out model in Fusion 360 to plan the 50° OLED display mount and internal airflow.
* **Mechanics:** Planned a concrete-weighted base with an M6 threaded rod core for maximum stability and vibration dampening.

## Bill of Materials (BOM)

| Item | Source | Purpose | Price |
| :--- | :--- | :--- | :--- |
| **12V 20A Power Supply** | Amazon | Main system power | €22.14 |
| **LR44 Batteries (20x)** | Amazon | For digital calipers (essential for precision measurements) | €4.02 |
| **Nobufil ASA Filament** | Nobufil | Heat-resistant structural housing | €31.66 |
| **AliExpress Bundle** (ESC, HEPA, PM Sensor) | AliExpress | Core filtration and control components | €10.74 |
| **Total** | | | **€68.56** |

## Notes for Reviewers
I've included LR44 batteries in the budget because my digital calipers are out of power. I need them to take exact measurements of the physical components (motor, ESC, sensors) to ensure the final 3D-printed housing has perfect tolerances.

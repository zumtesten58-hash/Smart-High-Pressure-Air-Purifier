# Smart High-Pressure Air Purifier (ESP32 Powered)

## Overview
This project is a high-performance modular air purifier designed for maximum static pressure to overcome dense HEPA filtration. I am using an ESP32 to control a 7.4V brushless motor running at 12V for high-RPM performance.

## Current Progress
* **Electronics:** Successfully soldered logic level shifters (voltage dividers) using 1% metal film resistors to safely interface 5V sensors with the 3.3V ESP32.
* **CAD Design:** Created an initial block-out model in Fusion 360 to plan the internal airflow and the 50° OLED display mount.
* **Mechanics:** Planned a concrete-weighted base with an M6 threaded rod core and TPU vibration dampening for high-speed stability.

## Bill of Materials (BOM)

| Item | Source | Purpose | Price |
| :--- | :--- | :--- | :--- |
| **12V 20A Power Supply** | Amazon | Main system power | €22.14 |
| **LR44 Batteries (20x)** | Amazon | For digital calipers (precision measurements) | €4.02 |
| **Nobufil ASA Filament** | Nobufil | Heat-resistant structural housing | €31.66 |
| **HEPA Filters & PM Sensor** | AliExpress | Air filtration and monitoring | €10.74 |
| **Total** | | | **€68.56** |

## Notes for Reviewers
I included the LR44 batteries because my digital calipers are dead. Precision is key for this project to ensure the 3D-printed parts fit the brushless motor and sensors perfectly.

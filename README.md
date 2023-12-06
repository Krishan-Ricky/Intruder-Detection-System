# Intruder Detection System

## Description
This project presents an Arduino-based security system utilizing an ultrasonic sensor for intruder detection. The system offers real-time alerts via a Telegram bot, including image snapshots. In the absence of internet connectivity, a GSM module ensures SMS alerts are sent. These combined features provide a reliable and robust security solution for diverse environments.

## Components Required
* Arduino Board
* Ultrasonic Sensor
* GSM Module
* Centre Shaft DC Geared Motor
* ESP-32 CAM
* LCD Display
* Buzzer
* Jumper Wires

## Working
**The Intruder Detection System operates as follows:**
1. **Intruder Detection:** *The motor turns 360 degrees, scanning both clockwise and counterclockwise. Simultaneously, an ultrasonic sensor detects intruders within its range.*
2. **Alert Generation:** *When an intruder is detected, the system initiates an alert.*
3. **Telegram Alert (With Internet):** *If an internet connection is available, the Telegram bot sends a real-time alert message along with a captured image.*
4. **SMS Alert (Without Internet):** *In the absence of internet connectivity, the GSM module sends an SMS alert to the predefined mobile number.*
5. **LCD Display and Buzzer Feedback:** *If an intruder is found, the LCD displays "Intruder Detected," and a buzzer sounds for an audible alert.*

<img src="Intruder Detection System.jpg">

# Sensor-Controlled Motor System with Fuzzy Logic (Arduino)

This Arduino sketch demonstrates a system that integrates various sensors and components to control DC motors based on sensor inputs. The code utilizes a DS18B20 waterproof temperature sensor, a pH meter, and an HC-SR04 ultrasonic distance sensor. The motors are controlled using fuzzy logic based on the distance measurement.

## Components Used

- Arduino board (e.g., Arduino Uno)
- DS18B20 waterproof temperature sensor
- pH meter
- HC-SR04 ultrasonic distance sensor
- DC motors
- L298N motor driver

## Libraries Used

- [OneWire](https://www.arduinolibraries.info/libraries/one-wire) - For DS18B20 sensor communication.
- [DallasTemperature](https://www.arduinolibraries.info/libraries/dallas-temperature) - For DS18B20 temperature sensor.

## Setup

1. Connect the components as described in the code comments.
2. Install the required libraries using the Arduino Library Manager.
3. Upload the sketch to your Arduino board.

## Functionality

1. Temperature and pH values are read from sensors.
2. The HC-SR04 ultrasonic sensor measures distance.
3. Motors are controlled based on pH, temperature, and distance conditions using fuzzy logic.

## Usage

1. Upload the provided sketch to your Arduino board.
2. Observe the serial monitor for sensor readings and motor control actions.

## Note

- The code demonstrates the integration of sensors and fuzzy logic for motor control. Additional adjustments may be needed for optimal performance and customization.

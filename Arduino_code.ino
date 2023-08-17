#include <Fuzzy.h> // Include the fuzzy logic library
#include <OneWire.h>
#include <DallasTemperature.h>

// Pin definitions
const int DS18B20_PIN = 12; // Temperature sensor pin
const int pH_SENSOR_PIN = A0; // pH sensor pin
const int ECHO_PIN = 3; // Ultrasonic sensor echo pin
const int TRIG_PIN = 2; // Ultrasonic sensor trigger pin
const int ENA_PIN = 4; // Motor enable pin
const int IN1_PIN = 5; // Motor control pin 1
const int IN2_PIN = 6; // Motor control pin 2

// Thresholds
const float pH_MIN = 5.5;
const float pH_MAX = 7.0;
const float TEMP_THRESHOLD = 30.0;

// Objects for sensors
OneWire oneWire(DS18B20_PIN);
DallasTemperature sensors(&oneWire);

// Motor control functions
void directionControl();
void speedControl();



// Define the fuzzy logic controller
Fuzzy controller;

// Define fuzzy input variables
FuzzyInput* distanceInput;

// Define fuzzy output variables
FuzzyOutput* motorSpeedOutput;

void setup() {
  
   Serial.begin(9600);

  // Set pin modes
  pinMode(pH_SENSOR_PIN, INPUT);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(ENA_PIN, OUTPUT);
  pinMode(IN1_PIN, OUTPUT);
  pinMode(IN2_PIN, OUTPUT);

  // Turn off motors (Initial state)
  digitalWrite(IN1_PIN, LOW);
  digitalWrite(IN2_PIN, LOW)

  // Define and configure fuzzy input variables
  distanceInput = new FuzzyInput(1);
  distanceInput->addTerm(new FuzzyTerm("Close", 0, 20, 30));
  distanceInput->addTerm(new FuzzyTerm("Medium", 20, 30, 50));
  distanceInput->addTerm(new FuzzyTerm("Far", 30, 50, 100));
  controller.addFuzzyInput(distanceInput);

  // Define and configure fuzzy output variables
  motorSpeedOutput = new FuzzyOutput(1);
  motorSpeedOutput->addTerm(new FuzzyTerm("Low", 0, 50));
  motorSpeedOutput->addTerm(new FuzzyTerm("Medium", 40, 100));
  motorSpeedOutput->addTerm(new FuzzyTerm("High", 90, 100));
  controller.addFuzzyOutput(motorSpeedOutput);

  // Define fuzzy rules
  controller.addRule("IF Close THEN High");
  controller.addRule("IF Medium THEN Medium");
  controller.addRule("IF Far THEN Low");

  // ... Rest of the setup code ...
}

void loop() {

    // Read temperature from DS18B20 sensor
  sensors.requestTemperatures();
  float temperatureC = sensors.getTempCByIndex(0) + 137;

  // Read pH from pH sensor
  float analogValue = analogRead(pH_SENSOR_PIN);
  float voltage = analogValue * (3.3 / 4095.0);
  float pH = (3.3 * voltage) + 8;

  // Read distance from ultrasonic sensor
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  long duration = pulseIn(ECHO_PIN, HIGH);
  int distance = duration * 0.034 / 2;

  // Print sensor values
  Serial.print("Temperature: ");
  Serial.print(temperatureC);
  Serial.println(" ℃");

  Serial.print("pH: ");
  Serial.println(pH);

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Motor control based on conditions
  if (pH < pH_MIN || pH > pH_MAX || temperatureC < TEMP_THRESHOLD) {
    directionControl();
    delay(1000);
    speedControl();
    delay(1000);
  }
}

void directionControl() {
  analogWrite(ENA_PIN, 255); // Set motors to maximum speed

  // Rotate motor A
  digitalWrite(IN1_PIN, HIGH);
  digitalWrite(IN2_PIN, LOW);
  delay(2000);

  // Change motor direction
  digitalWrite(IN1_PIN, LOW);
  digitalWrite(IN2_PIN, HIGH);
  delay(2000);

  // Turn off motors
  digitalWrite(IN1_PIN, LOW);
  digitalWrite(IN2_PIN, LOW);
}

void speedControl() {
  digitalWrite(IN1_PIN, LOW);
  digitalWrite(IN2_PIN, HIGH);

  // Accelerate motor
  for (int i = 0; i < 256; i++) {
    analogWrite(ENA_PIN, i);
    delay(20);
  }

  // Decelerate motor
  for (int i = 255; i >= 0; --i) {
    analogWrite(ENA_PIN, i);
    delay(20);
  }

  // Turn off motors
  digitalWrite(IN1_PIN, LOW);
  digitalWrite(IN2_PIN, LOW);
  

  // Apply fuzzy logic to adjust motor speed
  distanceInput->setValue(distance);
  controller.fuzzify();
  int fuzzySpeed = static_cast<int>(motorSpeedOutput->getValue());
  analogWrite(ENA_PIN, fuzzySpeed);

}

  

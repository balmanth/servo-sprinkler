/*!
 * Servomotor sprinkler.
 * @author Silas B. Domingos
 * @version 0.1
 */
#include <SimpleServo.h>

// Input & Output pins.
const int servoPinId = 0;
const int statePinId = 1;
const int sensorPinId = 2;

// Determines whether or not the servomotor was activated.
bool activated = false;

// Servomotor controller.
SimpleServo servo;

/**
 * Loader setup.
 */
void setup() {
  servo.attach(servoPinId);
  pinMode(statePinId, OUTPUT);
  pinMode(sensorPinId, INPUT);
}

/**
 * Loader loop.
 */
void loop() {
  if (!isActive()) {
    activated = false;
    moveFastTo(0);
  }
  else if (!activated) {
    activated = true;
    moveSmoothTo(90, 5);
    moveFastTo(0);
  }
  delay(100);
}

/**
 * Determines whether or not the infra-red sensor is obstructed.
 * @return Returns true when the sensor is obstructed, false otherwise.
 */
bool isActive() {
  const int state = digitalRead(sensorPinId);
  digitalWrite(statePinId, state);
  return state == LOW;
}

/**
 * Move the servomotor to the designated position in one step.
 * @param degree Final position.
 */
void moveFastTo(const unsigned int degree) {
  servo.write(degree);
  delay(15);
}

/**
 * Move the servomotor to the designated position step by step.
 * @param degree Final position.
 * @param increment Step increment.
 */
void moveSmoothTo(const unsigned int degree, const unsigned int increment) {
  for (unsigned int current = 0; current <= degree; current += increment) {
    moveFastTo(current);
  }
}

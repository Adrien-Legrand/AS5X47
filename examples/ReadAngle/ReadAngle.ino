/*
  ReadAngle

  Read the angle position from an AS5047 or AS5147 rotary encoder.
  Start the terminal with a speed of 9600 Bauds to see the measured angle.

  The encoder is connected as follows:
  AS5X47         Arduino Board
    5V <-------------> 5V
   GND <-------------> GND
  MOSI <-------------> MOSI (Pin 11 for Arduino Uno)
  MISO <-------------> MISO (Pin 12 for Arduino Uno)
   SCK <-------------> SCK  (Pin 13 for Arduino Uno)
   CSN <-------------> SS   Arbitrary, Pin 10 in this example.
  See Arduino SPI Reference to see how to connect with other boards.
  https://www.arduino.cc/en/reference/SPI

  Created 18 april 2020
  By Adrien Legrand

  https://github.com/Adrien-Legrand/AS5X47

*/

// Include the library
#include <AS5X47.h>

// Define where the CSN Pin in connected. 
int slaveSelectPin = 10;

// Start connection to the sensor.
AS5X47 as5047p(slaveSelectPin);

void setup() {
  // Initialize a Serial Communication in order to
  // print the measured angle.
  Serial.begin(9600);
}

void loop() {
  // Read the measured angle
  float angle = as5047p.readAngle();

  // Show the measure angle on the Serial Port
  Serial.println(angle);

  // Wait 1 second (1000 milliseconds) before reading again.
  delay(1000);
}

/*
  ConfirgureSensorOTP

  Configure the sensor with advanced parameters and flash the configuration using OTP.
  WARNING ! Once the configuration has been written using OTP, you will not be able to 
  change it on the permanent memory ! (You will still be able to change runtime
  configuration, but after each power cycle, the OTP memory will be loaded again).
  This example shows how to activate the UVW output for a 7 pole pairs motor and how to
  write this configuration to the permanent memory.
  For an advanced list and description of all available parameters, 
  see the manufacturer documentation. All parameters are implemented in this library.

  This example also demostrates how to print debug information.

  Start the terminal with a speed of 9600 Bauds to see the debug information.

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

  // Wait 10 seconds (10 000 milliseconds) in order to let you the time
  // to open the Serial terminal
  delay(10000);
  
  // This command print the debug information to the Serial port.
  // All registers of the encoder will be read and printed.
  // Note: A Serial communication must be opened with Serial.begin() before.
  as5047p.printDebugString();

  // Create a structure corresponding to the SETTINGS1 Register
  // See manufacturer documentation for more details.
  Settings1 settings1;

  // Parameters from SETTINGS1 can be set like this:
  // According to manufacturer documentation, UVW_ABI enables UVW output.
  settings1.values.uvw_abi = 0; 
  // According to manufacturer documentation, DIR inverts the output signal order.
  settings1.values.dir = 0;
  // Write settings to the encoder:
  as5047p.writeSettings1(settings1);

  // Same way, parameters from SETTINGS2 Register can be modified:
  Settings2 settings2;
  // UVWPP sets the number of pole-pairs to emulate for the UVW output.
  settings2.values.uvwpp = 2;
  as5047p.writeSettings2(settings2);

  // This command print the debug information to the Serial port.
  // All registers of the encoder will be read and printed.
  // Note: A Serial communication must be opened with Serial.begin() before.
  as5047p.printDebugString();


  // One Time Programming (OTP) :
  Serial.println("Writting configuration to OTP memory...");
  // Enable OTP : write PROGEN
  as5047p.writeRegister(0x003, 0x01);
  // Start OTP : write PROGOTP
  as5047p.writeRegister(0x003, 0x08);
  
  // Wait for OTP to finish...
  bool otpComplete = false;
  for (int i=0; i<100; i++) {
    delay(100);
    ReadDataFrame df = as5047p.readRegister(0x003);
    if (df.values.data == 0x01) {
      otpComplete = true;
      break;
    }
  }
  if (otpComplete) {
    Serial.println("Configuration written successfully !");
  }
  // You can now power cycle the sensor and check that the configuration
  // is now already loaded at startup.
}

void loop() {
  // Read the measured angle
  float angle = as5047p.readAngle();

  // Show the measure angle on the Serial Port
  Serial.println(angle);

  // Wait 1 second (1000 milliseconds) before reading again.
  delay(1000);
}

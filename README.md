
# AS5X47 Library for Arduino
![AS5047P Encoder with Arduino Mega](extras/images/encoderWithArduino.jpg?raw=true "Encoder with Arduino Mega")![AS5047P Encoder Mount](extras/images/encoderMount.jpg?raw=true "AS5047P Encoder")

AS5X47 is a library for connecting AS5047 and AS5147 magnetic encoders to Arduino boards. It allows to easily read the angle measured from the sensor and also advanced features to reconfigure the encoder.

## Hardware support
This library has been tested with the following encoders:

 - AS5047P
 - AS5047D
 - AS5147P

## Supported Features

 - [x] SPI Communication with encoders
 - [x] Abstraction of SPI Communication
 - [x] Read and Write operations for all registers
 - [x] Abstraction of angle measure
 - [x] Debug string to read the state of all registers at once
 - [ ] One Time Programation (OTP) Abstraction

Please let me know if you tested it with other encoders.

## Installation
**Using the Arduino Library Manager (recommended):** 
Use the Arduino Library Manager and search for AS5X47 library. Select the most recent version and click 'Install'. That's it, the library is installed!

**Installing manually:**
For more information or manually install the library, please refer to the Arduino official page : https://www.arduino.cc/en/guide/libraries

## Usage
### Examples
Two examples are provided within the library :

 - **ReadAngle.ino**  shows how to connect the sensor and how to read the measured angle.
 - **ConfigureSensor.ino** shows how to use advanced features of this library in order to manipulate the encoder registers according to the manufacturer datasheet. 
 
### Wiring
The encoder board must be connected to the SPI Pins of the Arduino Board. In the case of an Arduino Uno, connect as following:
![AS5X47 encoder connection](extras/images/wiring.jpg?raw=true "Wiring with an Arduino Uno")

For other boards, please refer to official Arduino page.

## Contributing
Pull requests are welcome. For major changes, please open an issue first to discuss what you would like to change.



## License
[MIT](https://choosealicense.com/licenses/mit/)

/** @file AS5X47Spi.cpp
 *
 * @brief A library for Arduino boards that reads angles from AS5047 and AS5147 sensors.
 * 		  Also support configuration of the sensor parameters.
 *
 * @par
 * COPYRIGHT NOTICE: MIT License
 *
 * 	Copyright (c) 2020 Adrien Legrand <contact@adrien-legrand.com>
 *
 * 	Permission is hereby granted, free of charge, to any person obtaining a copy
 * 	of this software and associated documentation files (the "Software"), to deal
 * 	in the Software without restriction, including without limitation the rights
 * 	to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * 	copies of the Software, and to permit persons to whom the Software is
 * 	furnished to do so, subject to the following conditions:
 *
 * 	The above copyright notice and this permission notice shall be included in all
 * 	copies or substantial portions of the Software.
 *
 * 	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * 	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * 	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * 	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * 	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * 	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * 	SOFTWARE.
 *
*/

#include "AS5X47Spi.h"

AS5X47Spi::AS5X47Spi(uint8_t chipSelectPin, SPIClass* s) {
	// Initialize SPI Communication
	_chipSelectPin = chipSelectPin;

	_spi_dev = new Adafruit_SPIDevice(chipSelectPin, 10000000, SPI_BITORDER_MSBFIRST,
                                   SPI_MODE1, s);
	_spi_dev->begin();
}

void AS5X47Spi::writeData(uint16_t command, uint16_t value) {
	// @todo Expose the SPI Maximum Frequency in library interface.
	_spi_dev->beginTransaction();
	// Send command
	digitalWrite(_chipSelectPin, LOW);
	_spi_dev->transfer((command >> 8) & 0xFF);
	_spi_dev->transfer(command & 0xFF);
	digitalWrite(_chipSelectPin, HIGH);
	delayMicroseconds(1);
	// Read data
	digitalWrite(_chipSelectPin, LOW);
	_spi_dev->transfer((value >> 8) & 0xFF);
	_spi_dev->transfer(value & 0xFF);
	digitalWrite(_chipSelectPin, HIGH);
	_spi_dev->endTransaction();
	delayMicroseconds(1);

}

uint16_t AS5X47Spi::readData(uint16_t command, uint16_t nopCommand) {
	_spi_dev->beginTransaction();

	// Send Read Command
	digitalWrite(_chipSelectPin, LOW);

	_spi_dev->transfer((command >> 8) & 0xFF);
	_spi_dev->transfer(command & 0xFF);
	digitalWrite(_chipSelectPin, HIGH);
	delayMicroseconds(1);
	// Send Nop Command while receiving data
	digitalWrite(_chipSelectPin, LOW);
	uint16_t d0 = _spi_dev->transfer((nopCommand >> 8) & 0xFF);
	uint16_t d1 = _spi_dev->transfer(nopCommand & 0xFF);
	uint16_t receivedData = (d0 << 8) | d1;
	digitalWrite(_chipSelectPin, HIGH);
	_spi_dev->endTransaction();
	delayMicroseconds(1);
	return receivedData;
}

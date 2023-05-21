# HealthDesk Station

![visitors](https://visitor-badge.glitch.me/badge?page_id=fusiandrea28.HealthDeskStation&left_color=green&right_color=red)

## Device Display examples
<img src="https://github.com/fusiandrea28/HealthDeskStation/blob/main/green1.jpg" alt="LowCo2" width="200"/> <img src="https://github.com/fusiandrea28/HealthDeskStation/blob/main/green2.jpg" alt="LowCo2" width="200"/> <img src="https://github.com/fusiandrea28/HealthDeskStation/blob/main/yellow1.jpg" alt="MidCo2" width="200"/> <img src="https://github.com/fusiandrea28/HealthDeskStation/blob/main/yellow2.jpg" alt="MidCo2" width="200"/> <img src="https://github.com/fusiandrea28/HealthDeskStation/blob/main/red1.jpg" alt="HighCo2" width="200"/> <img src="https://github.com/fusiandrea28/HealthDeskStation/blob/main/red2.jpg" alt="HighCo2" width="200"/>

#### ThingSpeak Interface
<img src="https://github.com/fusiandrea28/HealthDeskStation/blob/main/ThingSpeakChannel.jpg" alt="ThingSpeak Channel" width="800"/>

## Revision History

#### Rev1.2 (TBD)
- Add TVOC sensor (SEN55 from Sensirion

#### Rev1.1
- Added support for TFT SPI display (rounded)
- Replaced GSheet logging to ThingSpeak
- Eco-friendly enclosure for the device
- General improvements

#### Rev1.0
- Temp, Humidity and CO2 from SCD41 sensor
- Publishing to GSheet
- GSheet pulls data from historical weather database
- LED ring effects with NeoPixel library

## Description
An embedded system based on ESP32 device and ThingSpeak.

Arduino IDE is used to flash the ESP32.

The aim of this project is to get useful data about the environment.
This device can be placed in an office to know when there's a need to ventilate (high CO2 values).

## How does it work?

The device connects to a WiFi network with the credentials stored in its memory. 
If the saved network is out of range, or no credentials are present in the memory, the WiFi setup will begin.

The ESP32 enters a WiFi setup mode by turning on an access point.
A smartphone or PC can be used to connect to the ESP32 WiFi network. 
- Navigate to 192.168.4.1
An intuitive webpage lets you pick an SSID and insert a password to connect to.
The device restarts if the connection is successful.

Once the device is connected to the internet, it gathers data every 60 seconds from a Sensirion SCD41 sensor connected via I2C interface.
Temperature, Humidity and CO2 are shown in sequence on the TFT round display.

Every 10 minutes, it also push the temperature, humidity, CO2 and a Status to a ThingSpeak Channel.

## Setup

See the instruction in main.ino for hardware setup. Also pasted here below.

	1.
	Install libraries as below:
	- https://github.com/Sensirion/arduino-i2c-scd4x
	- https://github.com/tzapu/WiFiManager
	- https://github.com/Bodmer/TFT_eSPI
	
	2.
	ThingSpeak setup
	- Create a channel with 3 fields (temperature, humidity, co2) - https://www.mathworks.com/help/thingspeak/collect-data-in-a-new-channel.html
	- Copy channel ID and API key and paste in USER SETUP below
	
	3.
	Change the LED, I2C and SPI pins
	- In the code below, change the SDA and SCL pins in Wire.begin(SDA, SCL) function
	- In the tftRoundSPI.ino follow the instruction at the top of the code
  
--------

MIT License

Copyright (c) 2023 Andrea Fusi

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

# HealthDesk

## Revision History

## Rev1.0
- Temp, Humidity and CO2 from SCD41 sensor
- Publishing to GSheet
- GSheet pulls data from historical weather database
- LED ring effects with NeoPixel library

## Rev1.1 (TBD)
- Add a HMI (e-paper or LCD display)
- Add a way to let the user force the update (before the 30 mins timer)
- Improve conditional formatting

## Rev1.2 (TBD)
- Add TVOC sensor (SEN55 from Sensirion)
- Create an eco-friendly enclosure for the device

## Description
An embedded system based on ESP32 and Google Sheet.

Arduino IDE is used to flash the ESP32.

Google Script code for additional functions on the Google Spreadsheet.

The aim of this project is to get useful data about the environment.
This device can be placed in an office to know when there's a need to ventilate (high CO2 values).
It also helps having an idea of the climate change in Taipei by comparing the weather conditions of today, to those of the past.

## How does it work?

The device connects to a WiFi network with the credentials stored in its memory. 
If the saved network is out of range, or no credentials are present in the memory, the WiFi setup will begin.

The ESP32 enters a WiFi setup mode by turning on an access point.
A smartphone or PC can be used to connect to the ESP32 WiFi network. An intuitive webpage lets you pick an SSID and insert a password to connect to.
The device restarts if the connection is successful.

Once the device is connected to the internet, it gathers data every 30 minutes from a Sensirion SCD41 sensor connected via I2C interface.
It then push the SSID name, current time and date, temperature, humidity and CO2 values to a Google Spreadsheet.

The GSheet runs a Google Script (doGet) to read incoming data from the ESP32.

An additional function is used to gather historical weather data from a different tab in the same sheet (10, 20, 30 and 40 years ago temperature and humidity data).


## Setup

See the instruction in main.ino for hardware setup.
Google Script code is found in this repository.

Google Spreadsheet template should be as below.

<img src="https://github.com/fusiandrea28/HealthDeskStation/blob/main/GSheet_template.jpg" alt="GSheet page"/>
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

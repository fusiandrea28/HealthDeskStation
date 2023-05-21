/************************************************************************************
	*** HealthDesk v1.1 ***
	https://github.com/fusiandrea28/HealthDeskStation
	
	1.
	Install libraries as below:
	- https://github.com/Sensirion/arduino-i2c-scd4x
	- https://github.com/tzapu/WiFiManager
	- https://github.com/Bodmer/TFT_eSPI
	
	2.
	ThingSpeak setup
	- Create a channel with 3 fields (temperature, humidity, co2)
	- Copy channel ID and API key and paste in USER SETUP below
	
	3.
	Change the LED, I2C and SPI pins
	- In the code below, change the SDA and SCL pins in Wire.begin(SDA, SCL) function
	- In the tftRoundSPI.ino follow the instruction at the top of the code

 **********************************************************************************/

// Uncomment line below if not using Arduino IDE
//#include "Arduino.h"

//++++++++++++++++++++++++ USER SETUP +++++++++++++++++++++++++++++++++
//---------------------------------------------------------------------
//----------------- Timers Definition ---------------------------------
#include "millisDelay.h"
millisDelay thingSpeakDelay;
int thingSpeakDelaylenght = 10 *60000; // [minutes] Set the interval to gather data and push to ThingSpeak
int thingSpeakDelayfirstrunlenght = 10 *1000; // [seconds] Set the interval for the first run of timer above
millisDelay readingsSCD41Delay;
int readingsSCD41Delaylenght = 1 *60000; // [minutes] Set the interval to gather data and push to ThingSpeak
int thingSpeakCounter = 0;

millisDelay displayDelay;
int displayDelaylenght = 20 * 1000; // [seconds] Set the interval for the display update
int displayCounter = 0;

//---------------------------------------------------------------------
//-------------- ThingSpeak Deployment Section ------------------------
unsigned long myChannelNumber = YOUR_CHANNEL_ID_HERE;
const char * myWriteAPIKey = "INSERT_YOUR_THINGSPEAK_CHANNEL_API_KEY";
//---------------------------------------------------------------------
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//---------------------------------------------------------------------
//------------------ WiFi Define Section-------------------------------
#include <WiFi.h>
#include <HTTPClient.h>
#include <WiFiManager.h> // https://github.com/tzapu/WiFiManager
WiFiManager wm; // global wm instance
String ssidName;
String hostname = "ESP32 HealthDesk";
#define WiFiReset_pin 27 // Define GPIO for the button that will reset WiFi credentials

#include "ThingSpeak.h" // always include thingspeak header file after other header files and custom macros
WiFiClient  client;

//---------------------------------------------------------------------
//------------- Define Sensirion SCD41 Co2 sensor----------------------
#include <Wire.h>
#include <SensirionI2CScd4x.h>
SensirionI2CScd4x scd4x;
    uint16_t co2 = 0;
    float temperature = 0.0f;
    float humidity = 0.0f;
	uint16_t error;
    char errorMessage[256];

/************************************************************************************
 ********  SETUP  ***********
 **********************************************************************************/
void setup() 
{
	//---------------------------------------------------------------------
	Serial.begin(115200);
	delay(100);
	
	//---------------------------------------------------------------------
	//------------- Initialize DIsplay and call "Hello" -------------------
	displaySetup();
	displayHello();
	delay(3000);
	
	//---------------------------------------------------------------------
	//------------------------ Wi-Fi Manager ------------------------------
	displayWiFi();
	initializeWiFiManager();
	
	pinMode(WiFiReset_pin, INPUT_PULLUP); // Set the wifi reset pin as input with pullup
	
	ThingSpeak.begin(client);  // Initialize ThingSpeak
	
	displayUpdating(); // Display updating screen
	 
	//---------------------------------------------------------------------
	//----------------------- Initialize I2C ------------------------------
	Wire.begin(21, 22);
	
	//---------------------------------------------------------------------
	//----------------------- Initialize SCD41 ----------------------------
	initializeSCD41();
	
	//---------------------------------------------------------------------
	//----------------------- Initialize Timers ----------------------------
	setupTimers();
	
	Serial.println("----- SETUP FINISHED -----");
	Serial.println();	
	
}

/************************************************************************************
 ********  LOOP  ***********
 **********************************************************************************/
void loop() 
{
	//---------------------------------------------------------------------
	//--- Reset Wifi Credential if button pressed -------------------------
	if (digitalRead(WiFiReset_pin) == LOW) 
	{
		resetWiFicredentials();
	}
	
	//---------------------------------------------------------------------
	//--- TIMER ----- Get Readings from SCD41 -----------------------------
	if (readingsSCD41Delay.justFinished()) 
	{
		Serial.println("----------------------------------------------------");
		Serial.println("-------- SCD41 Get Readings Timer RUNNING -------------");
	
		// Restart the delay
		readingsSCD41Delay.start(readingsSCD41Delaylenght);
		Serial.print("Running again in ");
		Serial.print(readingsSCD41Delaylenght / 60000);
		Serial.println(" minutes.");	
		
		// Execute reading function
		getSCD41readings();
	}
	
	//---------------------------------------------------------------------
	//--- TIMER ----- Push to ThingSpeak -----------------
	if (thingSpeakDelay.justFinished()) 
	{
		Serial.println("----------------------------------------------------");
		Serial.println("-------- ThingSpeakDelay Timer RUNNING -------------");
		
		// Restart the delay
		thingSpeakDelay.start(thingSpeakDelaylenght);
		Serial.print("Running again in ");
		Serial.print(thingSpeakDelaylenght / 60000);
		Serial.println(" minutes.");			
		
		// Execute upload function
		thingSpeakUpload();
		
		Serial.println("--------- ThingSpeakDelay Timer EXECUTED -----------");
		Serial.println("----------------------------------------------------");
		Serial.println();
	}
	
	//---------------------------------------------------------------------
	//--- TIMER ----- Read SCD41 and loop display screens -----------------
	if (displayDelay.justFinished()) 
	{
		Serial.println("----------------------------------------------------");
		Serial.println("-------- Display Timer RUNNING -------------");
		
		// Restart the delay
		displayDelay.start(displayDelaylenght);
		Serial.print("Running again in ");
		Serial.print(displayDelaylenght / 1000);
		Serial.println(" seconds.");			
		
		// Execute reading function
		getSCD41readings();
		
		displayTempHumid();
		delay(10000);
		displayCO2();
		
		Serial.println("--------- Display Timer EXECUTED -----------");
		Serial.println("----------------------------------------------------");
		Serial.println();
	}
	
	if (co2 <= 1 && displayCounter == 0) 
	{
		displayReading();
		displayCounter++;
		
	}
	
}

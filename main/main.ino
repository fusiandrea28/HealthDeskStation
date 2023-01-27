/************************************************************************************
	*** HealthDesk v1.0 ***
	
	Firebeetle ESP32-E
	
	Tempeature, Humidity and CO2 values read from Sensirion SCD41 sensor
	Above data is published to GSheet via HTTP (Google AppScript).
	
	1.
	Install libraries as below:
	- https://github.com/FastLED/FastLED
	- https://github.com/Sensirion/arduino-i2c-scd4x
	- https://github.com/tzapu/WiFiManager
	- https://github.com/Bodmer/TFT_eSPI
	- https://github.com/Bodmer/TJpg_Decoder
	
	2.
	Google Script
	- Create a GSheet spreadsheet
	- Copy App script in the Google Spreadsheet (documentation available online)
	- Save and Deploy the script on GSheet as WebApp - Execute as your email - Execute by Anyone
	- Copy the GOOGLE_SCRIPT_ID and paste it below in the code.
	
	3.
	Change the LED, I2C and SPI pins
	- In the ledRingRGB.ino change the #define DATA_PIN to the GPIO you have connected the LEDs to
	- In the code below, change the SDA and SCL pins in Wire.begin(SDA, SCL) function
	- In the tftRoundSPI.ino follow the instruction at the top of the code

 **********************************************************************************/

// Uncomment line below if not using Arduino IDE
//#include "Arduino.h"

//++++++++++++++++++++++++ USER SETUP +++++++++++++++++++++++++++++++++
//---------------------------------------------------------------------
//----------------- Timers Definition ---------------------------------
#include "millisDelay.h"
millisDelay GsheetDelay;
int GsheetDelaylenght = 30 *60000; // [minutes] Set the interval to gather data and push to GSheet
int GsheetDelayfirstrunlenght = 10 *1000; // [seconds] Set the interval for the first run of timer above

//---------------------------------------------------------------------
//-------------- Google Deployment ID Section -------------------------
//ENTER_GOOGLE_DEPLOYMENT_ID
String GOOGLE_SCRIPT_ID = "yourGOOGLESCRIPTIDhere";
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

//---------------------------------------------------------------------
//--------------- Get Time Define Section -----------------------------
#include "time.h"
const char* ntpServer = "pool.ntp.org";
const long  gmtOffset_sec = 28800; // GMT +8 = 28800
const int   daylightOffset_sec = 0;
// Variables to save date and time
char timeStringBuff[10]; // chars should be enough
char dateStringBuff[10]; // chars should be enough

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

/***********************************************************************
 ********  Push Payload to Google Sheet
 ***********************************************************************/
void pushGsheetPayload(String params)
{
    HTTPClient http;
    String url="https://script.google.com/macros/s/"+GOOGLE_SCRIPT_ID+"/exec?"+params;
   
    Serial.println("Posting data to Google Sheet...");
	//---------------------------------------------------------------------
	//----------------- Begin upload to GSheet ----------------------------
    http.begin(url.c_str());
    http.setFollowRedirects(HTTPC_STRICT_FOLLOW_REDIRECTS);
    int httpCode = http.GET();  
	//Serial.print("HTTP Status Code: ");
    //Serial.println(httpCode);

	//---------------------------------------------------------------------
	//---------------- Get response from GSheet ---------------------------
    String payload;
    if (httpCode < 210) {
        payload = http.getString();
        Serial.println("Successfully pushed to GSheet");     
    }
	else {
        Serial.println("Error uploading to GSheet");     
    }
    
	//---------------------------------------------------------------------
	//---------------- Terminate HTTP communication -----------------------
    http.end();
}

/************************************************************************************
 ********  Generate Payload to be pushed to Google Sheet
 **********************************************************************************/
void generateGsheetPayload()
{
    String param;
    param = "temp="+String(temperature);
    param += "&humid="+String(humidity);
    param += "&co2="+String(co2);
	param += "&time="+String(timeStringBuff);
	param += "&date="+String(dateStringBuff);
	param += "&ssid="+ssidName;

    Serial.println(param);
	
	//---------------------------------------------------------------------
	//---------------- Push generated data to GSheet ----------------------
	pushGsheetPayload(param);

}

/************************************************************************************
 ********  SETUP  ***********
 **********************************************************************************/
void setup() 
{
	//---------------------------------------------------------------------
	Serial.begin(115200);
	delay(100);
	
	ledRingSetup();

	Serial.println("LED blink");
	ledLoop();
	
	randomSmoothCircles();
	
	//---------------------------------------------------------------------
	//------------------------ Wi-Fi Manager ------------------------------
	initializeWiFiManager();
	
	pinMode(WiFiReset_pin, INPUT_PULLUP); // Set the wifi reset pin as input with pullup
  
	//---------------------------------------------------------------------
	//------------- Initialize a NTPClient to get time --------------------
	configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
	
	//---------------------------------------------------------------------
	//----------------------- Initialize I2C ------------------------------
	Wire.begin(4, 5);
	
	//---------------------------------------------------------------------
	//----------------------- Initialize SCD41 ----------------------------
	initializeSCD41();
	
	// Start timer interval to gather data and push to GSheet on first run
	GsheetDelay.start(GsheetDelayfirstrunlenght);
	Serial.print("Running first measurement in ");
	Serial.print(GsheetDelayfirstrunlenght / 1000);
	Serial.println(" seconds.");
	
	Serial.println("LED blink");
	ledLoop();
	
	Serial.println("----- SETUP FINISHED -----");
	Serial.println();	
	
}

/************************************************************************************
 ********  LOOP  ***********
 **********************************************************************************/
void loop() 
{
	delay(100);
	//---------------------------------------------------------------------
	//--- Reset Wifi Credential if button pressed -------------------------
	if (digitalRead(WiFiReset_pin) == LOW) 
	{
		resetWiFicredentials();
	}
	
	//---------------------------------------------------------------------
	//--- TIMER ----- Get Readings and push to GSheet ---------------------
	if (GsheetDelay.justFinished()) 
	{
		Serial.println("----------------------------------------------------");
		Serial.println("---------- GsheetDelay Timer RUNNING ---------------");
		
		// Restart the delay
		GsheetDelay.start(GsheetDelaylenght);
		Serial.print("Running again in ");
		Serial.print(GsheetDelaylenght / 60000);
		Serial.println(" minutes.");			

		//---------------------------------------------------------------------
		//--------------------- Get Date and Time -----------------------------
		getPrintLocalTime();
		
		//---------------------------------------------------------------------
		//--------------------- Get SCD41 readings ----------------------------
		getSCD41readings();
		 
		//---------------------------------------------------------------------
		//------------ Generate payload and push to GSheet --------------------
		generateGsheetPayload();
		
		Serial.println("LED blink");
		ledLoop();
		
		Serial.println("---------- GsheetDelay Timer EXECUTED --------------");
		Serial.println("----------------------------------------------------");
		Serial.println();
	}
	
}
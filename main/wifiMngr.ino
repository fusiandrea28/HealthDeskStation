/************************************************************************************
 ********  Reset WiFi Credentials if side button is pressed
 **********************************************************************************/
void resetWiFicredentials()
{
	Serial.println("Reset WiFi Button Pressed...");
	Serial.println("Erasing WiFi credentials and restarting ESP32.");
	wm.resetSettings();
	ESP.restart();		
}

/************************************************************************************
 ********  WiFi Manager
 **********************************************************************************/
void initializeWiFiManager()
{

    WiFi.mode(WIFI_STA); // explicitly set mode, esp defaults to STA+AP
    // it is a good practice to make sure your code sets wifi mode how you want it.
    
	WiFi.config(INADDR_NONE, INADDR_NONE, INADDR_NONE, INADDR_NONE);
	WiFi.setHostname(hostname.c_str()); //define hostname

    //WiFiManager, Local intialization. Once its business is done, there is no need to keep it around
    //WiFiManager wm;

	pinMode(WiFiReset_pin, INPUT);
    // reset settings - wipe stored credentials for testing
    // these are stored by the esp library
    // wm.resetSettings();

    // Automatically connect using saved credentials,
    // if connection fails, it starts an access point with the specified name ( "AutoConnectAP"),
    // if empty will auto generate SSID, if password is blank it will be anonymous AP (wm.autoConnect())
    // then goes into a blocking loop awaiting configuration and will return success result

    bool res;
    // res = wm.autoConnect(); // auto generated AP name from chipid
    // res = wm.autoConnect("ESP32SetupWiFi"); // anonymous ap
    res = wm.autoConnect("ESP32SetupWiFi","esp32wifisetuppsw"); // password protected ap

    if(!res) {
        Serial.println("Failed to connect");
        displayWiFiNG();
		delay(6000);
		ESP.restart();
	}
	
    else {
        //if you get here you have connected to the WiFi    
        Serial.println("Successfully Connected!");
		ssidName = String(WiFi.SSID());
		ssidName.replace(" ", "");
		ssidName.replace("_", "");
		ssidName.replace("-", "");
		Serial.println("SSID name:" + ssidName);
		displayWiFiOK();
		delay(6000);
    }

}

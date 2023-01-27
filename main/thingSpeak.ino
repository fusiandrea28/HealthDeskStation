/************************************************************************************
 ********  Push readings to ThingSpeak channel
 **********************************************************************************/
void thingSpeakUpload()
{
	if (thingSpeakCounter >= 1) {
          displayUpdating();
		  delay(1000);
    }
		
	//---------------------------------------------------------------------
	//--------------------- Get SCD41 readings ----------------------------
	getSCD41readings();
	getSEN55readings();
	
	// set the fields with the values
	ThingSpeak.setField(1, temperature);
	ThingSpeak.setField(2, humidity);
	ThingSpeak.setField(3, co2);
	ThingSpeak.setField(4, massConcentrationPm1p0);
	ThingSpeak.setField(5, massConcentrationPm2p5);
	ThingSpeak.setField(6, massConcentrationPm10p0);
	ThingSpeak.setField(7, vocIndex);
	ThingSpeak.setField(8, noxIndex);
	
	String myStatus = "";
	// figure out the status message
	if (co2 >= 1200) {
		myStatus = String("Very High CO2 levels. Ventilate the area!");
	}
	else if (co2 >= 700){
		myStatus = String("High CO2 levels!");
	}
	else {
		myStatus = String("Low CO2 levels.");
	}
	// set the status
	ThingSpeak.setStatus(myStatus);
	
	// write to the ThingSpeak channel
	int x = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
	if(x == 200){
		Serial.println("ThingSpeak Channel update successful.");
		displayUpdatingOK();
		delay(5000);
	}
	else{
		Serial.println("Problem updating channel. HTTP error code " + String(x));
		displayUpdatingNG();
		delay(5000);
	}	
	
	thingSpeakCounter++;
}
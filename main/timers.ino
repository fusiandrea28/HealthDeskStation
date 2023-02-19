/************************************************************************************
 ********  Timers page
 **********************************************************************************/
void setupTimers()
{
	// Start timer interval to push to ThingSpeak on first run
	thingSpeakDelay.start(thingSpeakDelayfirstrunlenght);
	Serial.print("Running first measurement in ");
	Serial.print(thingSpeakDelayfirstrunlenght / 1000);
	Serial.println(" seconds.");
	
	// Start timer interval to read from SCD41 on first run
	readingsSCD41Delay.start(readingsSCD41Delaylenght);
	
	// Start timer interval to read from SCD41
	displayDelay.start(displayDelaylenght);
}
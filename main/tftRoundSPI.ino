/************************************************************************************

	Need to set the Display - ESP32 connections first.
	
	Go to Documents/ARduino/libraries/TFT_eSPI
	
	Open the file "User_Setup.h" with a text editor like Notepad++
	
	1. Uncomment lines below and change to the pins you are using in your setup for SPI connection.
	
		// For ESP32 Dev board (only tested with GC9A01 display)
		// The hardware SPI can be mapped to any pins
		#define TFT_MOSI 23 // In some display driver board, it might be written as "SDA" and so on.
		#define TFT_SCLK 18
		#define TFT_CS   13  // Chip select control pin
		#define TFT_DC   14  // Data Command control pin
		#define TFT_RST  26  // Reset pin (could connect to Arduino RESET pin)
		#define TFT_BL   25  // LED back-light
	
	2. Comment the section below
	
		// For NodeMCU - use pin numbers in the form PIN_Dx where Dx is the NodeMCU pin designation
		//#define TFT_CS   PIN_D8  // Chip select control pin D8
		//#define TFT_DC   PIN_D3  // Data Command control pin
		//#define TFT_RST  PIN_D4  // Reset pin (could connect to NodeMCU RST, see next line)
		//#define TFT_RST  -1    // Set TFT_RST to -1 if the display RESET is connected to NodeMCU RST or 3.3V
		
	3. Uncomment "#define GC9A01_DRIVER" and comment "#define ILI9341_DRIVER"

 **********************************************************************************/

//----------------------------------------------------------------------------
//------------------ SPI Display Define Section-------------------------------
#include <SPI.h>
#include <TFT_eSPI.h>       // Hardware-specific library
TFT_eSPI tft = TFT_eSPI();  // Invoke custom library

uint16_t* tft_buffer;
bool      buffer_loaded = false;
uint16_t  spr_width = 0;
uint16_t  bg_color =0;
uint16_t  fg_color =0;

int maxco2 = 1500; // define max value for CO2 gauge
int maxpm25 = 30; // define max value for PM2.5 gauge
int maxVOC = 400; // define max value for PM2.5 gauge

void displaySetup() 
{
	tft.init();
    tft.setRotation(0);
    tft.fillScreen(TFT_BLACK);
}

void displayCO2() 
{
	tft.fillScreen(TFT_BLACK);
	
	if (co2 >= 1200) {
          tft.setTextColor(TFT_RED, TFT_BLACK);
		  fg_color = TFT_RED;
        }
        else if (co2 >= 700){
          tft.setTextColor(TFT_ORANGE, TFT_BLACK);
		  fg_color = TFT_ORANGE;
        }
		else {
          tft.setTextColor(TFT_GREEN, TFT_BLACK);
		  fg_color = TFT_GREEN;
    }
	
	uint16_t bg_color = TFT_BLACK;       // This is the background colour used for smoothing (anti-aliasing)
	
	uint16_t x = 120;  // Position of centre of arc
	uint16_t y = 120;
	
	uint8_t radius       = 120; // Outer arc radius
	uint8_t thickness    = 20;     // Thickness
	uint8_t inner_radius = radius - thickness;        // Calculate inner radius (can be 0 for circle segment)
	
	// 0 degrees is at 6 o'clock position
	// Arcs are drawn clockwise from start_angle to end_angle
	uint16_t start_angle = 0; // Start angle must be in range 0 to 360
	uint16_t end_angle   = co2*360/maxco2; // End angle must be in range 0 to 360
	
	//bool arc_end = 2;   // true = round ends, false = square ends (arc_end parameter can be omitted, ends will then be square)
	
	tft.drawSmoothArc(x, y, radius, inner_radius, start_angle, end_angle, fg_color, bg_color);
	
//
	
	uint16_t xco2num = 120;  // Position of number
	uint16_t yco2num = 140;

	uint16_t xco2text = 120;  // Position of text
	uint16_t yco2text = 60;	
	
	if (co2 >= 1000 && co2 <= 1999) {
          xco2num = 110;
    }
	
	// Set datum to Middle Right
	tft.setTextDatum(TC_DATUM);
		
	// Set the padding to the maximum width that the digits could occupy in font 4
	// This ensures small numbers obliterate large ones on the screen
	//tft.setTextPadding( tft.textWidth("-88.88", 4) );
	
	tft.setTextSize(1);

	// Draw a floating point number with 2 decimal places with right datum in font 4
	tft.drawNumber(co2, xco2num, yco2num, 7);
	
	// Reset text padding to 0 otherwise all future rendered strings will use it!
	tft.setTextPadding(0);
	
	tft.setTextSize(5);
	tft.setTextColor(TFT_WHITE, TFT_BLACK);
	tft.drawString("CO2", xco2text, yco2text);
	
	tft.drawLine(40, 120, 200, 120, TFT_WHITE);
	
}

void displayPM25() 
{
	tft.fillScreen(TFT_BLACK);
	
	if (massConcentrationPm2p5 >= 25) {
          tft.setTextColor(TFT_RED, TFT_BLACK);
		  fg_color = TFT_RED;
        }
        else if (massConcentrationPm2p5 >= 15){
          tft.setTextColor(TFT_ORANGE, TFT_BLACK);
		  fg_color = TFT_ORANGE;
        }
		else {
          tft.setTextColor(TFT_GREEN, TFT_BLACK);
		  fg_color = TFT_GREEN;
    }
	
	uint16_t bg_color = TFT_BLACK;       // This is the background colour used for smoothing (anti-aliasing)
	
	uint16_t x = 120;  // Position of centre of arc
	uint16_t y = 120;
	
	uint8_t radius       = 120; // Outer arc radius
	uint8_t thickness    = 20;     // Thickness
	uint8_t inner_radius = radius - thickness;        // Calculate inner radius (can be 0 for circle segment)
	
	// 0 degrees is at 6 o'clock position
	// Arcs are drawn clockwise from start_angle to end_angle
	uint16_t start_angle = 0; // Start angle must be in range 0 to 360
	uint16_t end_angle   = massConcentrationPm2p5*360/maxpm25; // End angle must be in range 0 to 360
	
	//bool arc_end = 2;   // true = round ends, false = square ends (arc_end parameter can be omitted, ends will then be square)
	
	tft.drawSmoothArc(x, y, radius, inner_radius, start_angle, end_angle, fg_color, bg_color);
	
//
	
	uint16_t xpm25num = 120;  // Position of number
	uint16_t ypm25num = 140;

	uint16_t xpm25text = 120;  // Position of text
	uint16_t ypm25text = 60;	
	
	// Set datum to Middle Right
	tft.setTextDatum(TC_DATUM);
		
	// Set the padding to the maximum width that the digits could occupy in font 4
	// This ensures small numbers obliterate large ones on the screen
	//tft.setTextPadding( tft.textWidth("-88.88", 4) );
	
	tft.setTextSize(1);

	// Draw a floating point number with 2 decimal places with right datum in font 4
	tft.drawNumber(massConcentrationPm2p5, xpm25num, ypm25num, 7);
	
	// Reset text padding to 0 otherwise all future rendered strings will use it!
	tft.setTextPadding(0);
	
	tft.setTextSize(5);
	tft.setTextColor(TFT_WHITE, TFT_BLACK);
	tft.drawString("PM2.5", xpm25text, ypm25text);
	
	tft.drawLine(40, 120, 200, 120, TFT_WHITE);
	
}

void displayVOC() 
{
	tft.fillScreen(TFT_BLACK);
	
	if (vocIndex >= 300) {
          tft.setTextColor(TFT_RED, TFT_BLACK);
		  fg_color = TFT_RED;
        }
        else if (vocIndex >= 110){
          tft.setTextColor(TFT_ORANGE, TFT_BLACK);
		  fg_color = TFT_ORANGE;
        }
		else {
          tft.setTextColor(TFT_GREEN, TFT_BLACK);
		  fg_color = TFT_GREEN;
    }
	
	uint16_t bg_color = TFT_BLACK;       // This is the background colour used for smoothing (anti-aliasing)
	
	uint16_t x = 120;  // Position of centre of arc
	uint16_t y = 120;
	
	uint8_t radius       = 120; // Outer arc radius
	uint8_t thickness    = 20;     // Thickness
	uint8_t inner_radius = radius - thickness;        // Calculate inner radius (can be 0 for circle segment)
	
	// 0 degrees is at 6 o'clock position
	// Arcs are drawn clockwise from start_angle to end_angle
	uint16_t start_angle = 0; // Start angle must be in range 0 to 360
	uint16_t end_angle   = vocIndex*360/maxVOC; // End angle must be in range 0 to 360
	
	//bool arc_end = 2;   // true = round ends, false = square ends (arc_end parameter can be omitted, ends will then be square)
	
	tft.drawSmoothArc(x, y, radius, inner_radius, start_angle, end_angle, fg_color, bg_color);
	
//
	
	uint16_t xvocnum = 120;  // Position of number
	uint16_t yvocnum = 140;

	uint16_t xvoctext = 120;  // Position of text
	uint16_t yvoctext = 60;	
	
	// Set datum to Middle Right
	tft.setTextDatum(TC_DATUM);
		
	// Set the padding to the maximum width that the digits could occupy in font 4
	// This ensures small numbers obliterate large ones on the screen
	//tft.setTextPadding( tft.textWidth("-88.88", 4) );
	
	tft.setTextSize(1);

	// Draw a floating point number with 2 decimal places with right datum in font 4
	tft.drawNumber(vocIndex, xvocnum, yvocnum, 7);
	
	// Reset text padding to 0 otherwise all future rendered strings will use it!
	tft.setTextPadding(0);
	
	tft.setTextSize(5);
	tft.setTextColor(TFT_WHITE, TFT_BLACK);
	tft.drawString("VOC", xvoctext, yvoctext);
	
	tft.drawLine(40, 120, 200, 120, TFT_WHITE);
	
}

void displayTempHumid() 
{
	tft.fillScreen(TFT_BLACK);
	
	uint16_t xtempnum = 95;  // Position of temperature
	uint16_t ytempnum = 55;
	
	uint16_t xhumidnum = 95;  // Position of humidity
	uint16_t yhumidnum = 140;

	tft.setTextColor(TFT_WHITE, TFT_BLACK);
	
	// Set datum to Middle Right
	tft.setTextDatum(TC_DATUM);
		
	// Set the padding to the maximum width that the digits could occupy in font 4
	// This ensures small numbers obliterate large ones on the screen
	tft.setTextPadding( tft.textWidth("88.88", 7) );
	
	tft.setTextSize(1);

	// Draw a floating point number with 1 decimal places with right datum in font 4
	tft.drawNumber(temperature, xtempnum, ytempnum, 7);
		
	// Draw a floating point number with 1 decimal places with right datum in font 4
	tft.drawNumber(humidity, xhumidnum, yhumidnum, 7);

	// Reset text padding to 0 otherwise all future rendered strings will use it!
	tft.setTextPadding(0);
	
	tft.setTextSize(5);
	tft.drawString("C", xtempnum + 75, ytempnum);
	tft.drawString("%", xhumidnum + 75, yhumidnum);
	
	tft.drawLine(40, 120, 200, 120, TFT_WHITE);

//
	
	if (co2 >= 1200) {
          tft.setTextColor(TFT_RED, TFT_BLACK);
		  fg_color = TFT_RED;
        }
        else if (co2 >= 700){
          tft.setTextColor(TFT_ORANGE, TFT_BLACK);
		  fg_color = TFT_ORANGE;
        }
		else {
          tft.setTextColor(TFT_GREEN, TFT_BLACK);
		  fg_color = TFT_GREEN;
    }
	
	uint16_t bg_color = TFT_BLACK;       // This is the background colour used for smoothing (anti-aliasing)
	
	uint16_t x = 120;  // Position of centre of arc
	uint16_t y = 120;
	
	uint8_t radius       = 120; // Outer arc radius
	uint8_t thickness    = 20;     // Thickness
	uint8_t inner_radius = radius - thickness;        // Calculate inner radius (can be 0 for circle segment)
	
	// 0 degrees is at 6 o'clock position
	// Arcs are drawn clockwise from start_angle to end_angle
	uint16_t start_angle = 0; // Start angle must be in range 0 to 360
	uint16_t end_angle   = co2*360/maxco2; // End angle must be in range 0 to 360
	
	//bool arc_end = 2;   // true = round ends, false = square ends (arc_end parameter can be omitted, ends will then be square)
	
	tft.drawSmoothArc(x, y, radius, inner_radius, start_angle, end_angle, fg_color, bg_color);
	
}

void displayReading() 
{

    tft.fillScreen(TFT_BLACK);

	uint16_t xco2text = 120;  // Position of text
	uint16_t yco2text = 120;	
	
	// Set datum to Middle Right
	tft.setTextDatum(MC_DATUM);
		
	tft.setTextSize(4);
	tft.setTextColor(TFT_WHITE, TFT_BLACK);
	tft.drawString("Wait...", xco2text, yco2text);
	
}

void displayUpdating() 
{
	tft.fillScreen(TFT_BLACK);
	
	uint16_t fg_color = TFT_WHITE; 
	uint16_t bg_color = TFT_BLACK;       // This is the background colour used for smoothing (anti-aliasing)
	
	uint16_t x = 120;  // Position of centre of arc
	uint16_t y = 120;
	
	uint8_t radius       = 120; // Outer arc radius
	uint8_t thickness    = 10;     // Thickness
	uint8_t inner_radius = radius - thickness;        // Calculate inner radius (can be 0 for circle segment)
	
	// 0 degrees is at 6 o'clock position
	// Arcs are drawn clockwise from start_angle to end_angle
	uint16_t start_angle = 0; // Start angle must be in range 0 to 360
	uint16_t end_angle   = 360; // End angle must be in range 0 to 360
	
	//bool arc_end = 2;   // true = round ends, false = square ends (arc_end parameter can be omitted, ends will then be square)
	
	tft.drawSmoothArc(x, y, radius, inner_radius, start_angle, end_angle, fg_color, bg_color);
	
//

	uint16_t xco2text = 120;  // Position of text
	uint16_t yco2text = 120;	
	
	// Set datum to Middle Right
	tft.setTextDatum(MC_DATUM);
		
	tft.setTextSize(4);
	tft.setTextColor(TFT_WHITE, TFT_BLACK);
	tft.drawString("-UPLOAD-", xco2text, yco2text);
	
}

void displayUpdatingOK() 
{
	
	uint16_t fg_color = TFT_GREEN; 
	uint16_t bg_color = TFT_BLACK;       // This is the background colour used for smoothing (anti-aliasing)
	
	uint16_t x = 120;  // Position of centre of arc
	uint16_t y = 120;
	
	uint8_t radius       = 120; // Outer arc radius
	uint8_t thickness    = 10;     // Thickness
	uint8_t inner_radius = radius - thickness;        // Calculate inner radius (can be 0 for circle segment)
	
	// 0 degrees is at 6 o'clock position
	// Arcs are drawn clockwise from start_angle to end_angle
	uint16_t start_angle = 0; // Start angle must be in range 0 to 360
	uint16_t end_angle   = 360; // End angle must be in range 0 to 360
	
	//bool arc_end = 2;   // true = round ends, false = square ends (arc_end parameter can be omitted, ends will then be square)
	
	tft.drawSmoothArc(x, y, radius, inner_radius, start_angle, end_angle, fg_color, bg_color);
	
}

void displayUpdatingNG() 
{
	uint16_t fg_color = TFT_RED; 
	uint16_t bg_color = TFT_BLACK;       // This is the background colour used for smoothing (anti-aliasing)
	
	uint16_t x = 120;  // Position of centre of arc
	uint16_t y = 120;
	
	uint8_t radius       = 120; // Outer arc radius
	uint8_t thickness    = 10;     // Thickness
	uint8_t inner_radius = radius - thickness;        // Calculate inner radius (can be 0 for circle segment)
	
	// 0 degrees is at 6 o'clock position
	// Arcs are drawn clockwise from start_angle to end_angle
	uint16_t start_angle = 0; // Start angle must be in range 0 to 360
	uint16_t end_angle   = 360; // End angle must be in range 0 to 360
	
	//bool arc_end = 2;   // true = round ends, false = square ends (arc_end parameter can be omitted, ends will then be square)
	
	tft.drawSmoothArc(x, y, radius, inner_radius, start_angle, end_angle, fg_color, bg_color);
}

void displayHello() 
{
	tft.fillScreen(TFT_BLACK);

	uint16_t xco2text = 120;  // Position of text
	uint16_t yco2text = 120;	
	
	// Set datum to Middle Right
	tft.setTextDatum(MC_DATUM);
		
	tft.setTextSize(5);
	tft.setTextColor(TFT_WHITE, TFT_BLACK);
	tft.drawString("Hello!", xco2text, yco2text);
	
}

void displayWiFIAP() 
{
	tft.fillScreen(TFT_BLACK);
	
	// Set datum to Middle Right
	tft.setTextDatum(MC_DATUM);
	
	uint16_t xAP1 = 120;  // Position of text
	uint16_t yAP1 = 120;	
	
	tft.setTextSize(2);
	tft.setTextColor(TFT_WHITE, TFT_BLACK);
	tft.drawString("Connect to WiFi", xAP1, yAP1);
	
}

void displayAccessPoint() 
{
	tft.fillScreen(TFT_BLACK);
	
	uint16_t xAP2 = 120;  // Position of text
	uint16_t yAP2 = 35;	
	
		// Set datum to Middle Right
	tft.setTextDatum(MC_DATUM);
	
	tft.setTextSize(2);
	tft.setTextColor(TFT_WHITE, TFT_BLACK);
	tft.drawString("SSID, PSW:", xAP2, yAP2);
	
	uint16_t xAP3 = 120;  // Position of text
	uint16_t yAP3 = 70;
	
		// Set datum to Middle Right
	tft.setTextDatum(MC_DATUM);
	
	tft.setTextSize(2);
	tft.setTextColor(TFT_WHITE, TFT_BLACK);
	tft.drawString("ESP32, 444ap444", xAP3, yAP3);
	
	uint16_t xAP4= 120;  // Position of text
	uint16_t yAP4 = 120;
	
		// Set datum to Middle Right
	tft.setTextDatum(MC_DATUM);
	
	tft.setTextSize(2);
	tft.setTextColor(TFT_WHITE, TFT_BLACK);
	tft.drawString("Visit:", xAP4, yAP4);
	
	uint16_t xAP5 = 120;  // Position of text
	uint16_t yAP5 = 170;
	
		// Set datum to Middle Right
	tft.setTextDatum(MC_DATUM);
	
	tft.setTextSize(3);
	tft.setTextColor(TFT_WHITE, TFT_BLACK);
	tft.drawString("192.168.4.1", xAP5, yAP5);
	
}

void displayWiFiOK() 
{
	tft.fillScreen(TFT_BLACK);
	
	// Set datum to Middle Right
	tft.setTextDatum(MC_DATUM);
	
	uint16_t xAP6 = 120;  // Position of text
	uint16_t yAP6 = 80;
	
	tft.setTextSize(2);
	tft.setTextColor(TFT_WHITE, TFT_BLACK);
	tft.drawString("Connected to:", xAP6, yAP6);
	
	uint16_t xAP7 = 120;  // Position of text
	uint16_t yAP7 = 125;
	
		// Set datum to Middle Right
	tft.setTextDatum(MC_DATUM);
	
	tft.setTextSize(2);
	tft.setTextColor(TFT_WHITE, TFT_BLACK);
	tft.drawString(ssidName, xAP7, yAP7);
	
	uint16_t fg_color = TFT_GREEN; 
	uint16_t bg_color = TFT_BLACK;       // This is the background colour used for smoothing (anti-aliasing)
	
	uint16_t x = 120;  // Position of centre of arc
	uint16_t y = 120;
	
	uint8_t radius       = 120; // Outer arc radius
	uint8_t thickness    = 20;     // Thickness
	uint8_t inner_radius = radius - thickness;        // Calculate inner radius (can be 0 for circle segment)
	
	// 0 degrees is at 6 o'clock position
	// Arcs are drawn clockwise from start_angle to end_angle
	uint16_t start_angle = 0; // Start angle must be in range 0 to 360
	uint16_t end_angle   = 360; // End angle must be in range 0 to 360
	
	//bool arc_end = 2;   // true = round ends, false = square ends (arc_end parameter can be omitted, ends will then be square)
	
	tft.drawSmoothArc(x, y, radius, inner_radius, start_angle, end_angle, fg_color, bg_color);
}

void displayWiFiNG() 
{
	tft.fillScreen(TFT_BLACK);
	
	// Set datum to Middle Right
	tft.setTextDatum(MC_DATUM);
	
	uint16_t fg_color = TFT_RED; 
	uint16_t bg_color = TFT_BLACK;       // This is the background colour used for smoothing (anti-aliasing)
	
	uint16_t x = 120;  // Position of centre of arc
	uint16_t y = 120;
	
	uint8_t radius       = 120; // Outer arc radius
	uint8_t thickness    = 20;     // Thickness
	uint8_t inner_radius = radius - thickness;        // Calculate inner radius (can be 0 for circle segment)
	
	// 0 degrees is at 6 o'clock position
	// Arcs are drawn clockwise from start_angle to end_angle
	uint16_t start_angle = 0; // Start angle must be in range 0 to 360
	uint16_t end_angle   = 360; // End angle must be in range 0 to 360
	
	//bool arc_end = 2;   // true = round ends, false = square ends (arc_end parameter can be omitted, ends will then be square)
	
	tft.drawSmoothArc(x, y, radius, inner_radius, start_angle, end_angle, fg_color, bg_color);
}
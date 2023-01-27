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

//---------------------------------------------------------------------
//------------------ SPI Display Define Section-------------------------------
#include <SPI.h>
#include <TFT_eSPI.h>       // Hardware-specific library
#include "qrCode.h"
#include "TJpg_Decoder.h"
TFT_eSPI tft = TFT_eSPI();  // Invoke custom library

#define NEEDLE_LENGTH 35  // Visible length
#define NEEDLE_WIDTH   5  // Width of needle - make it an odd number
#define NEEDLE_RADIUS 90  // Radius at tip
#define NEEDLE_COLOR1 TFT_MAROON  // Needle periphery colour
#define NEEDLE_COLOR2 TFT_RED     // Needle centre colour
#define DIAL_CENTRE_X 120
#define DIAL_CENTRE_Y 120

uint16_t* tft_buffer;
bool      buffer_loaded = false;
uint16_t  spr_width = 0;
uint16_t  bg_color =0;

// =======================================================================================
// This function will be called during decoding of the jpeg file
// =======================================================================================
bool tft_output(int16_t x, int16_t y, uint16_t w, uint16_t h, uint16_t* bitmap)
{
  // Stop further decoding as image is running off bottom of screen
  if ( y >= tft.height() ) return 0;

  // This function will clip the image block rendering automatically at the TFT boundaries
  tft.pushImage(x, y, w, h, bitmap);

  // Return 1 to decode next block
  return 1;
}

/***********************************************************************
 ********  Initialize SPI display and print QR image
 ***********************************************************************/
void printQRcode()
{
  // The byte order can be swapped (set true for TFT_eSPI)
	TJpgDec.setSwapBytes(true);
	
	// The jpeg decoder must be given the exact name of the rendering function above
	TJpgDec.setCallback(tft_output);
	
	tft.begin();
	tft.setRotation(0);
	tft.fillScreen(TFT_BLACK);
	
	TJpgDec.drawJpg(0, 0, qrCodepic, sizeof(qrCodepic));
	tft.drawCircle(DIAL_CENTRE_X, DIAL_CENTRE_Y, NEEDLE_RADIUS-NEEDLE_LENGTH, TFT_DARKGREY);
}

void randomSmoothCircles() {

	tft.init();
	tft.fillScreen(TFT_BLACK); // Background is black
	tft.setCursor(0, 0);
	
	// Draw some random smooth rounded rectangles
	for (int i = 0; i < 20; i++)
	{
	int radius = random(60);
	int w = random(2 * radius, 160);
	int h = random(2 * radius, 160);
	int t = random(1, radius / 3);
	int x = random(tft.width() - w);
	int y = random(tft.height() - h);
	
	// Random colour is anti-aliased (blended) with background colour (black in this case)
	tft.drawSmoothRoundRect(x, y, radius, radius - t, w, h, random(0x10000), TFT_BLACK);
	}
	tft.print("Variable thickness");
	delay(2000);
	
	tft.fillScreen(TFT_BLACK);
	tft.setCursor(0, 0);
	
	// Draw some random minimum thickness smooth rounded rectangles
	for (int i = 0; i < 20; i++)
	{
	int radius = random(60);
	int w = random(2 * radius, 160);
	int h = random(2 * radius, 160);
	int t = 0;
	int x = random(tft.width() - w);
	int y = random(tft.height() - h);
	
	// Random colour is anti-aliased (blended) with background colour (black in this case)
	tft.drawSmoothRoundRect(x, y, radius, radius - t, w, h, random(0x10000), TFT_BLACK);
	}
	tft.print("Minimum thickness");
	delay(2000);
}
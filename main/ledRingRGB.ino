#include <FastLED.h>

#define NUM_LEDS 12      /* The amount of pixels/leds you have */
#define DATA_PIN 19       /* The pin your data line is connected to */
#define LED_TYPE WS2812B /* I assume you have WS2812B leds, if not just change it to whatever you have */
#define BRIGHTNESS 50   /* Control the brightness of your leds */
#define SATURATION 255   /* Control the saturation of your leds */

CRGB leds[NUM_LEDS];

void ledRingSetup() {
  FastLED.addLeds<LED_TYPE, DATA_PIN>(leds, NUM_LEDS);
}

void ledLoop() {
  for (int j = 0; j < 255; j++) {
    for (int i = 0; i < NUM_LEDS; i++) {
      leds[i] = CHSV(i - (j * 2), SATURATION, BRIGHTNESS); /* The higher the value 4 the less fade there is and vice versa */ 
    }
    FastLED.show();
    delay(50); /* Change this to your hearts desire, the lower the value the faster your colors move (and vice versa) */
  }
}
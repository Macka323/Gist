#include <FastLED.h>
#define LED_PIN     7
#define NUM_LEDS    360
CRGB leds[NUM_LEDS];
void setup() {
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
}
void loop() {
  for (int i = 0; i <= 360; i++) {
    leds[i] = CRGB ( 255, 255, 255);
    FastLED.show();
    delay(40);
    }
}
  

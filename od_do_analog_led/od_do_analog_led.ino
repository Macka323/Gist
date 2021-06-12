#include <FastLED.h>
#define LED_PIN     7
#define NUM_LEDS    20

CRGB leds[NUM_LEDS];

void setup() {
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
  
}
  
void loop() {
        
int val = analogRead(2);
        int numLedsToLight = map(val, 0, 1023, 0, 20);

        // First, clear the existing led values
        FastLED.clear();
        for(int led = 5; led < numLedsToLight; led++) { 
            leds[led] = CRGB::Blue; 
        }
        FastLED.show();
}
        

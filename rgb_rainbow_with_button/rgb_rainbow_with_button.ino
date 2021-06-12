#include <FastLED.h>

#if defined(FASTLED_VERSION) && (FASTLED_VERSION < 3001000)
#warning "Requires FastLED 3.1 or later; check github for latest code."
#endif

#define DATA_PIN    7
#define LED_TYPE    WS2811
#define COLOR_ORDER GRB
#define NUM_LEDS    360
CRGB leds[NUM_LEDS];
const int switchPin = 8;
int buttonState = 0;

#define BRIGHTNESS          96
#define FRAMES_PER_SECOND  120

void setup(){
    FastLED.addLeds<LED_TYPE,DATA_PIN,COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
    FastLED.setBrightness(BRIGHTNESS);
    pinMode(switchPin, INPUT);
}

typedef void (*SimplePatternList[])();
SimplePatternList gPatterns = { rainbow, /*rainbowWithGlitter/* confetti, sinelon, juggle, bpm*/ };

uint8_t gCurrentPatternNumber = 0; 
uint8_t gHue = 0; 
void loop()
{
  // Call the current pattern function once, updating the 'leds' array
  gPatterns[gCurrentPatternNumber]();

  // send the 'leds' array out to the actual LED strip
  FastLED.show();  
  // insert a delay to keep the framerate modest
  FastLED.delay(1000/FRAMES_PER_SECOND); 

  // do some periodic updates
  EVERY_N_MILLISECONDS( 20 ) { gHue++; } // slowly cycle the "base color" through the rainbow
  /*EVERY_N_SECONDS( 10 ) { nextPattern(); } // change patterns periodically*/
}

#define ARRAY_SIZE(A) (sizeof(A) / sizeof((A)[0]))

void rainbow() 
{
  buttonState = digitalRead(switchPin);
  if (buttonState == HIGH) {
  // FastLED's built-in rainbow generator
  fill_rainbow( leds, NUM_LEDS, gHue, 7);
  }
}

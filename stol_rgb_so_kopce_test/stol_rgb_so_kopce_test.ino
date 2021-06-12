#include <FastLED.h>
#define LED_PIN     7
#define NUM_LEDS    60
const int switchPin = 8;
const int switchPin1 = 9;
CRGB leds[NUM_LEDS];
int buttonState = 0;
int buttonState1 = 0;


void setup() {
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
  
  pinMode(switchPin, INPUT);
  pinMode(switchPin1, INPUT);

}
void loop() {
  
  buttonState = digitalRead(switchPin);
  buttonState1 = digitalRead(switchPin1);
  
  if (buttonState == HIGH) {
  leds[0] = CRGB(255, 0, 0);
  FastLED.show();
  delay(500);  
  leds[1] = CRGB(0, 255, 0);
  FastLED.show();
  delay(500);
  leds[2] = CRGB(0, 0, 255);
  FastLED.show();
  delay(500);
  leds[5] = CRGB(150, 0, 255);
  FastLED.show();
  delay(500);
  leds[9] = CRGB(255, 200, 20);
  FastLED.show();
  delay(500);
  leds[14] = CRGB(85, 60, 180);
  FastLED.show();
  delay(500);
  leds[19] = CRGB(50, 255, 20);
  FastLED.show();
  delay(500);
  
  }

  else {
     leds[0] = CRGB(0, 0, 0);
  FastLED.show();
  delay(500);  
  leds[1] = CRGB(0, 0, 0);
  FastLED.show();
  delay(500);
  leds[2] = CRGB(0, 0, 0);
  FastLED.show();
  delay(500);
  leds[5] = CRGB(150, 0, 0);
  FastLED.show();
  delay(500);
  leds[9] = CRGB(255, 200, 20);
  FastLED.show();
  delay(500);
  leds[14] = CRGB(85, 60, 180);
  FastLED.show();
  delay(500);
  leds[19] = CRGB(50, 255, 20);
  FastLED.show();
  delay(500);
    
  }
}

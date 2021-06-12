/*
  Keyboard Message test

  For the Arduino Leonardo and Micro.

  Sends a text string when a button is pressed.

  The circuit:
  - pushbutton attached from pin 4 to +5V
  - 10 kilohm resistor attached from pin 4 to ground

  created 24 Oct 2011
  modified 27 Mar 2012
  by Tom Igoe
  modified 11 Nov 2013
  by Scott Fitzgerald

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/KeyboardMessage
*/

#include "Keyboard.h"
char ctrlKey = KEY_LEFT_GUI;


const int buttonPin = 4;          // input pin for pushbutton
int previousButtonState = HIGH;   // for checking the state of a pushButton
int counter = 0;                  // button push counter
void setup() {
  // make the pushButton pin an input:
  pinMode(buttonPin, INPUT);
  // initialize control over the keyboard:
  Keyboard.begin();
}

void loop() {
  
 
  
  // read the pushbutton:
  int buttonState = digitalRead(buttonPin);
  // if the button state has changed,
  if ((buttonState != previousButtonState)
      // and it's currently pressed:
      && (buttonState == HIGH)) {
    // increment the button counter
    counter++;
    // type out a message
  while (digitalRead(buttonPin) == HIGH) {
    // do nothing until pin 2 goes low
    delay(500);
  }
  delay(1000);
  // new document:
  Keyboard.press(ctrlKey);
  Keyboard.press('r');
  
  delay(100);
  Keyboard.releaseAll();
  // wait for new window to open:
  
 
    Keyboard.write(92);
    Keyboard.write(92);
    Keyboard.write('?');
    Keyboard.write(92);
    
    Keyboard.print("Volume{2c5d07e8-0000-0000-0000-007603000000}");
    Keyboard.write(92);
    Keyboard.press(176);
    Keyboard.releaseAll();
    delay(1000);
    Keyboard.press('n');
    Keyboard.press(176);
    Keyboard.releaseAll();
    
  }
  // save the current button state for comparison next time:
  previousButtonState = buttonState;
}

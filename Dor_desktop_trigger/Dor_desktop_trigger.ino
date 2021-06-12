//
#include "Keyboard.h"





void setup()
{
  pinMode(2, INPUT);
 
  pinMode(7, OUTPUT);
}

void loop()
{
  if (digitalRead(2) == HIGH) {
   Keyboard.press(KEY_LEFT_GUI);
    Keyboard.press('d');
    Keyboard.releaseAll();
    while (!(digitalRead(2) == LOW)) {
      digitalWrite(7, HIGH);
    }
  }
  if (digitalRead(2) == LOW) {
    Keyboard.press(KEY_LEFT_GUI);
    Keyboard.press('d');
    Keyboard.releaseAll();
    while (!(digitalRead(2) == HIGH)) {
      digitalWrite(7, HIGH);
    }
  }
  delay(10); // Delay a little bit to improve simulation performance
}

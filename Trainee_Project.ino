/* 
Project     : Trainee Project Experimantal
Description : Function test and trial area
 _ _____   _   _  __  ___ _  __ __  
| |_   _| | | | |/__\| _ \ |/ /' _/ 
| | | |   | 'V' | \/ | v /   <`._`. 
|_| |_|   !_/ \_!\__/|_|_\_|\_\___/ 
*/

#include <LiquidCrystal.h>
#include "bitmaps.h"

/* ==== PINS ASSIGNMENT ==========
 * LCD RS pin to digital pin 8
 * LCD EN pin to digital pin 9
 * LCD D4 pin to digital pin 4
 * LCD D5 pin to digital pin 5
 * LCD D6 pin to digital pin 6
 * LCD D7 pin to digital pin 7
 * Backlight PWM control to Pin 10
 * LCD R/W pin to ground
 */

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

int analogPin = A0;
int keyInput = -1;
int lastKeyInput = -1;  // Variable to store last key input
int numKeys = 5;
int analogKeyValues[5] = { 30, 150, 360, 535, 760 };

String msgs[5] = { "Right Key OK",
                   "Up Key OK",
                   "Down Key OK",
                   "Left Key OK",
                   "Select Key OK" };

void setup() {
  pinMode(10, OUTPUT);
  analogWrite(10, 100);

  lcd.begin(16, 2);
  lcd.clear();

  lcd.print("1234567891234567");
  lcd.setCursor(0, 1);
  lcd.print("ABCDEFGHIJKLMNOP");
  delay(3 * 1000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Keypad Test");
  lcd.createChar(7, dino);
  lcd.createChar(6, cacti);
  lcd.createChar(5, bird);
  lcd.createChar(4, block);
  lcd.setCursor(12, 0);
  lcd.write((uint8_t)7);
  lcd.setCursor(13, 0);
  lcd.write((uint8_t)6);
  lcd.setCursor(14, 0);
  lcd.write((uint8_t)5);
  lcd.setCursor(15, 0);
  lcd.write((uint8_t)4);
  lcd.setCursor(0, 1);
  lcd.print("Pls press any");

  Serial.begin(9600);  // Begin serial communication at 9600 baud
}

void loop() {
  keyInput = getKey(analogRead(analogPin));

  if (keyInput != -1) {
    Serial.print("Key Input (number): ");
    Serial.println(keyInput);

    lcd.setCursor(0, 1);
    lcd.println("                ");
    lcd.setCursor(0, 1);
    lcd.print(msgs[keyInput]);
  }
  keyInput = -1;
}

int getKey(unsigned int input) {
  int x;

  for (x = 0; x < numKeys; x++) {
    if (input < analogKeyValues[x])
      return x;
  }

  if (x >= numKeys)
    x = -1;  // No valid key pressed

  return x;
}
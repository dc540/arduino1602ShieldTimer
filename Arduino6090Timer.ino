/*
Simple timer for Arduino + DFRobot 1602 LCD Shield with buttons
19 Mar 2021
by Bob German/DC540
https://dc540.org/xxx
*/

#include <LiquidCrystal.h>
#include "pitches.h"

//LCD pin to Arduino
const int pin_RS = 8; 
const int pin_EN = 9; 
const int pin_d4 = 4; 
const int pin_d5 = 5; 
const int pin_d6 = 6; 
const int pin_d7 = 7; 
const int buzzer = 3;
const int pin_BL = 10; 
#include "pitches.h"

// notes in the melody:
int melody[] = {
  NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4
};

// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = {
  4, 8, 8, 4, 4, 4, 4, 4
};


LiquidCrystal lcd( pin_RS,  pin_EN,  pin_d4,  pin_d5,  pin_d6,  pin_d7);
  bool delayRunning = false;
  unsigned long delayStart = 0;
  unsigned long delayTime = 0;
  int prevSeconds = 0;

void setup() {
  Serial.begin(9600); // open the serial port at 9600 bps:
  Serial.print("begin");
  lcd.begin(16, 2);

  Serial.print("LCD print");
  lcd.print("Up - 60sec timer");
  lcd.setCursor(0,1);
  lcd.print("Dn - 90sec timer");
  // Set BL pin to LOW to deal with badly implemented shields
  // should always be safe - never set to HIGH and OUTPUT
  digitalWrite(pin_BL, LOW);
  // pinMode(pin_BL, OUTPUT);
  digitalWrite(buzzer, HIGH);
  pinMode(buzzer, OUTPUT);
  bool delayRunning = false;
  unsigned long delayStart = 0;
}  

void loop() {
  int secondsLeft = 0;
  if (delayRunning) {
    if (((millis() - delayStart) >= delayTime)) {
      delayRunning = false;
      lcd.setCursor(0,1);
      lcd.print("Countdown Finished");
      /*tone(buzzer,666);
      delay(500);
      noTone(buzzer);
      delay(500);
      tone(buzzer,666);
      delay(500);
      noTone(buzzer);
      delay(500);
      tone(buzzer,666);
      delay(500);
      noTone(buzzer);
      */
       // iterate over the notes of the melody:
  for (int thisNote = 0; thisNote < 8; thisNote++) {

    // to calculate the note duration, take one second divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = 1000 / noteDurations[thisNote];
    tone(buzzer, melody[thisNote], noteDuration);

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(buzzer);
  }

      pinMode(pin_BL, OUTPUT);
    }  else {
      secondsLeft = int((delayTime/1000) - int((millis() - delayStart)/1000));
      if (secondsLeft != prevSeconds) {
        lcd.setCursor(1,1);
        lcd.print(" ");
        lcd.setCursor(0,1);
        lcd.print(secondsLeft);
        lcd.setCursor(3,1);
        lcd.print("Seconds Left");
        prevSeconds = secondsLeft;
      }
    }
  }
  int x;
  x = analogRead (0);
  lcd.setCursor(10,1);
  if (x < 60) {
    lcd.print ("Right ");
    Serial.print("Right ");
    lcd.begin(16,2);
    lcd.setCursor(0,1);
    lcd.print("Buzzer");
    tone(buzzer,666);
    delay(5000);
    noTone(buzzer);
    pinMode(pin_BL, OUTPUT);    
  }
  else if (x < 200) {
    Serial.print("Up    ");  
    pinMode(pin_BL, INPUT);
    lcd.begin(16,2);
    lcd.print("60 Second Timer");
    lcd.setCursor(0,1);
    lcd.print("60 Seconds");
    delayTime = 60000;
    delayStart = millis();
    delayRunning = true;
  }
  else if (x < 400){
    Serial.print("Down  ");
    pinMode(pin_BL, INPUT);
    lcd.begin(16,2);
    lcd.print("90 Second Timer");
    lcd.setCursor(0,1);
    lcd.print("90 Seconds");
    delayTime = 90000;
    delayStart = millis();
    delayRunning = true;

  }
  else if (x < 600){
    Serial.print("Left  ");
    pinMode(pin_BL, INPUT);
  }
  else if (x < 800){
    Serial.print("Select");
    pinMode(pin_BL, INPUT);
  }
}

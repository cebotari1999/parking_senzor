#include <LiquidCrystal.h>

LiquidCrystal LCD(3, 4, 5, 6, 10, 11); 
const int contrast = 100;

const int trig = 12;    // Trigger pin
const int echo = 13;    // Echo pin
const int buzzer = 2; // Buzzer pin

long cm, inches;
int duration;
int distance;

void setup() {
  // Serial Port begin
  Serial.begin(9600);
  
  // Define inputs and outputs
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(buzzer, OUTPUT);

 // Initialize the LCD
  analogWrite(9, contrast);
  LCD.begin(16, 2);



}

void loop() {
  // The sensor is triggered by a HIGH pulse of 10 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  digitalWrite(trig, LOW);
  delayMicroseconds(5);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  
  // Read the signal from the sensor: a HIGH pulse whose
  // duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  pinMode(echo, INPUT);
  duration = pulseIn(echo, HIGH);

  // Convert the time into a distance
  cm = (duration / 2) / 29.1;
  inches = (duration / 2) / 74;

 // The buzzer emits a sound. Frequency of sound depends it depends 
  // on how close the object is 
  if (cm <= 5) {
    tone(buzzer, 400);
  }
  else if (cm > 5 && cm <= 15) {
    tone(buzzer, 370);
  }
  else if (cm > 15 && cm < 30) {
    tone(buzzer, 340);
  } else {
    noTone(buzzer);
  }

 
  LCD.clear();
  
   LCD.setCursor(0, 0);
  LCD.print("dist. cm :"); // Print the massage
  LCD.setCursor(11, 0);
  LCD.print(cm); // Prints the distance in cm
  
  LCD.setCursor(0, 1); 
  LCD.print("dist. inch:"); // Print the massage
  LCD.setCursor(11, 1);
  LCD.print(inches); // Prints the distance in meter
  
  delay(200);
};

/*
  Analog Input
  Demonstrates analog input by reading an analog sensor on analog pin 0 and
  turning on and off a light emitting diode(LED)  connected to digital pin 13.
  The amount of time the LED will be on and off depends on
  the value obtained by analogRead().

  The circuit:
   Potentiometer attached to analog input 0
   center pin of the potentiometer to the analog pin
   one side pin (either one) to ground
   the other side pin to +5V
   LED anode (long leg) attached to digital output 13
   LED cathode (short leg) attached to ground

   Note: because most Arduinos have a built-in LED attached
  to pin 13 on the board, the LED is optional.


  Created by David Cuartielles
  modified 30 Aug 2011
  By Tom Igoe

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/AnalogInput

*/

int sensorPin = A0;    // select the input pin for the potentiometer
int ledPin = 13;      // select the pin for the LED
int sensorValue = 0;  // variable to store the value coming from the sensor

byte seven_seg_digits[10][7] = { { 1, 1, 1, 1, 1, 0, 1 }, // = 0
  { 1, 1, 1, 1, 0, 1, 1 }, // = 1
  { 1, 1, 1, 0, 1, 1, 1 }, // = 2
  { 1, 1, 0, 1, 1, 1, 1 }, // = 3
  { 1, 0, 1, 1, 1, 1, 1 }, // = 4
  { 0, 1, 1, 1, 1, 1, 1 }, // = 5
};

void setup() {
  // declare the ledPin as an OUTPUT:
  pinMode(ledPin, OUTPUT);

  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);

  Serial.begin(115200);
}

void sevenSegWrite(byte digit) {
  byte pin = 2;
  for (byte segCount = 0; segCount < 7; ++segCount) {
    digitalWrite(pin, seven_seg_digits[digit][segCount]);
    ++pin;
  }
}

void loop() {

  for (byte count = 6; count > 0; --count) {
    // read the value from the sensor:
    sensorValue = analogRead(sensorPin);
    Serial.println(sensorValue);
    // turn the ledPin on
    digitalWrite(ledPin, HIGH);
    for (byte count = 6; count > 0; --count) {
      sensorValue = analogRead(sensorPin);
      delay(sensorValue);
      sevenSegWrite(count - 1);
    }

    digitalWrite(ledPin, LOW);
  }
}

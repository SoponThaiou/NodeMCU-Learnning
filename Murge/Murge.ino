#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

#define IN2  2
#define IN3  3
#define IN4  4
#define IN5  5
#define IN6  6
#define IN7  7
#define IN8  8
#define IN9  9
#define IN10  10
#define IN11  11
#define IN12  12

int Steps = 0;
boolean Direction = true;// gre
boolean Direction_buf = true;// gre
unsigned long last_time;
unsigned long currentMillis;
int stepL = 1000;
int steps_left = stepL;
long time;

int sensorPin = A0;    // select the input pin for the potentiometer
int ledPin = 13;      // select the pin for the LED
int sensorValue = 0;  // variable to store the value coming from the sensor
int sensorValue_buf = 0; // for caculate

byte seven_seg_digits[10][7] = { { 1, 1, 1, 1, 1, 0, 1 }, // = 0
  { 1, 1, 1, 1, 0, 1, 1 }, // = 1
  { 1, 1, 1, 0, 1, 1, 1 }, // = 2
  { 1, 1, 0, 1, 1, 1, 1 }, // = 3
  { 1, 0, 1, 1, 1, 1, 1 }, // = 4
  { 0, 1, 1, 1, 1, 1, 1 }, // = 5
};

void setup() {
  // declare the ledPin as an OUTPUT:
  //pinMode(ledPin, OUTPUT);

  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(IN5, OUTPUT);
  pinMode(IN6, OUTPUT);
  pinMode(IN7, OUTPUT);
  pinMode(IN8, OUTPUT);
  pinMode(IN9, OUTPUT);
  pinMode(IN10, OUTPUT);
  pinMode(IN11, OUTPUT);
  pinMode(IN12, OUTPUT);

  Serial.begin(115200);
  lcd.begin();
  lcd.home();
  lcd.print("Direction = ");
  lcd.print(Direction);
  lcd.setCursor(0, 1);
  lcd.print("SPEED = ");
  lcd.print(sensorValue);
  ShowStatusLCD();
}

void sevenSegWrite(byte digit) {
  byte pin = 2;
  for (byte segCount = 0; segCount < 7; ++segCount) {
    digitalWrite(pin, seven_seg_digits[digit][segCount]);
    ++pin;
  }
}

void ShowStatusLCD() {
  if (Direction_buf != Direction) {
    if (Direction_buf) {
      lcd.setCursor(12, 0);
      lcd.print(">>>");
    } else {
      lcd.setCursor(12, 0);
      lcd.print("<<<");
    }
    Direction_buf = Direction;
  } else {
    //lcd.print("SPEED = ");
    lcd.print("        ");
    lcd.setCursor(8, 1);
    lcd.print(sensorValue);
  }
  Serial.println(time);
  Serial.println("SPEED = ");
  sensorValue_buf = sensorValue;
  sensorValue_buf = pow(sensorValue_buf - 315, 2);
  Serial.println(sensorValue_buf);
  delay(sensorValue);
}

void SetDirection() {
  if (Direction == 1) {
    Steps++;
  }
  if (Direction == 0) {
    Steps--;
  }
  if (Steps > 7) {
    Steps = 0;
  }
  if (Steps < 0) {
    Steps = 7;
  }
}

void loop() {
  for (byte count = 6; count > 0; --count) {
    ShowStatusLCD();
    // read the value from the sensor:
    sensorValue = analogRead(sensorPin);
    delay(sensorValue);
    sevenSegWrite(count - 1);
  }

  Direction = !Direction;
}

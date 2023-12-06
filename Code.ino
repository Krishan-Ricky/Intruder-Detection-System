// Includes the Servo lib
#include <Servo.h>
#include <SoftwareSerial.h>
#include <LiquidCrystal.h>

SoftwareSerial mySerial(A0, 4);
Servo myServo;

const int rs = 8, en = 9, d4 = 10, d5 = 11, d6 = 12, d7 = 13;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// Defines Trig and Echo pins of the Ultrasonic Sensor
const int trigPin = 6;
const int echoPin = 7;
const int buz = 3;
int m1 = A2;
int m2 = A1;
int ir = 5;

// Variables for the duration and the distance
long duration;
int distance;
int i = 0;
int kk = 0;

void setup() {
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT);  // Sets the echoPin as an Input
  pinMode(buz, OUTPUT);
  pinMode(m1, OUTPUT);
  pinMode(m2, OUTPUT);
  pinMode(ir, INPUT);

  lcd.begin(16, 2);
  lcd.print("   WELCOME");

  mySerial.begin(9600);
  Serial.begin(9600);

  myServo.attach(A4); // Defines on which pin the servo motor is attached
  delay(1000);

  digitalWrite(m1, 1);
  digitalWrite(m2, 0);
}

void loop() {
  // Rotates the servo motor from 15 to 165 degrees
  if (digitalRead(ir) == 1) {
    digitalWrite(m1, 1 - digitalRead(m1));
    digitalWrite(m2, 1 - digitalRead(m2));
    while (digitalRead(ir) == 1) {
      delay(10);
    }
  }

  i = i + 1;
  if (i == 360)
    i = 0;
  delay(30);

  distance = calculateDistance(); // Calls a function for calculating the distance measured by the Ultrasonic sensor for each degree

  lcd.clear();
  lcd.print("DIST:" + String(distance) + "Cm");

  if (distance < 15 && kk == 0) {
    lcd.setCursor(0, 1);
    lcd.print("ALERT");
    kk = 1;
    Serial.println("Intruder Alert &0&1");
    digitalWrite(m1, 0);
    digitalWrite(m2, 0);
    delay(500);
    send_sms();
    digitalWrite(m1, 1);
    digitalWrite(m2, 0);
  }

  if (distance >= 15)
    kk = 0;
}

// Function for calculating the distance measured by the Ultrasonic sensor
int calculateDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH); // Reads the echoPin, returns the sound wave travel time in microseconds
  distance = duration * 0.034 / 2;
  return distance;
}

void send_sms() {
  digitalWrite(buz, 1);

  mySerial.println("Sending SMS...");
  mySerial.println("AT");
  delay(1000);
  mySerial.println("ATE0");
  delay(1000);
  mySerial.println("AT+CMGF=1");
  delay(1000);
  mySerial.print("AT+CMGS=\"x\"\r\n"); // Replace x with the mobile number
  delay(1000);
  mySerial.println("Alert: Intruder detected");
  delay(100);
  mySerial.println((char)26); // ASCII code of CTRL+Z
  delay(5000);

  digitalWrite(buz, 0);
}

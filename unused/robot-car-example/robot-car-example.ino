/*
 * Firmware for the "2WD Ultrasonic Motor Robot Car Kit"
 *
 * Stephen A. Edwards
 *
 * Hardware configuration:
 *  A pair of DC motors driven by an L298N H bridge motor driver
 *  An HC-SR04 ultrasonic range sensor mounted atop a small hobby servo
 */

#include <Servo.h>
#include <SoftwareSerial.h>

// Ultrasonic Module pins
const int trigPin = 13;  // 10 microsecond high pulse causes chirp, wait 50 us
const int echoPin = 12;  // Width of high pulse indicates distance

// Servo motor that aims ultrasonic sensor.
const int servoPin = 11; // PWM output for hobby servo

// Motor control pins: L298N H bridge
const int enAPin = 6; // Left motor PWM speed control
const int in1Pin = 7; // Left motor Direction 1
const int in2Pin = 5; // Left motor Direction 2
const int in3Pin = 4; // Right motor Direction 1
const int in4Pin = 2; // Right motor Direction 2
const int enBPin = 3; // Right motor PWM speed control

enum Motor { LEFT, RIGHT };

Servo servo;
SoftwareSerial mySerial(10, 9); // TX/RX pins


void setup() {
  mySerial.begin(115200);
  Serial.begin(9600);
  mySerial.println("- Bluetooth Driver Communications-");
  Serial.println("- USB Serial -");

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  digitalWrite(trigPin, LOW);

  pinMode(enAPin, OUTPUT);
  pinMode(in1Pin, OUTPUT);
  pinMode(in2Pin, OUTPUT);
  pinMode(in3Pin, OUTPUT);
  pinMode(in4Pin, OUTPUT);
  pinMode(enBPin, OUTPUT);

  servo.attach(servoPin);
  servo.write(150);

  // make sure the motors are reset to 0 speed on reupload
  setSpeed(LEFT, 0);
  setSpeed(RIGHT, 0);

}

int angle = 140;

void loop() {
  Serial.println(readDistance());
  String t; //string to hold data from BT module 

  while(mySerial.available()) { //keep reading bytes while they are still more in the buffer
    t = (char)mySerial.read(); //read byte, convert to char, and append it to string
  }
  
  if(t.length()) { //if string is not empty do the following
    switch (t.charAt(0)) {
          Serial.print(t);

      case 'w':
        Serial.print("Forward\n");
        setSpeed(LEFT, 150);
        setSpeed(RIGHT, -150); // right is reversed
        break;
      case 'd':
        Serial.print("Right\n");
        setSpeed(LEFT, 150);
        break;
      case 'a':
        Serial.print("Left\n");
        setSpeed(RIGHT, 150);
        break;
      case 's':
        Serial.print("Backward\n");
        setSpeed(LEFT, -150);
        setSpeed(RIGHT, 150);
        break;
      case ' ':
        setSpeed(LEFT, 0);
        setSpeed(RIGHT, 0);
        break;
      default:
        Serial.print("Invalid Syntax\n");
        setSpeed(LEFT, 0);
        setSpeed(RIGHT, 0);
        break;
    }
  }
  
  delay(10);
  servo.write(angle);
  angle += 2;
  if(angle > 160) {
    angle = 130;
  }
}


// Magic Code - Do Not Touch Unless You Know What You Are Doing


// Set motor speed: 255 full ahead, -255 full reverse, 0 stop
void setSpeed(enum Motor m, int speed)
{
  digitalWrite(m == LEFT ? in1Pin : in3Pin, speed > 0 ? HIGH : LOW );
  digitalWrite(m == LEFT ? in2Pin : in4Pin, speed <= 0 ? HIGH : LOW );
  analogWrite(m == LEFT ? enAPin : enBPin, speed < 0 ? -speed : speed );
}

// Read distance from the ultrasonic sensor, return mm
// Speed of sound in dry air, 20C is 343 m/s
// pulseIn returns time in microseconds (10^-6)
// 2d = p * 10^-6 s * 343 m/s = p * 0.00343 m = p * 0.343 mm/us
unsigned int readDistance()
{
  digitalWrite( trigPin, HIGH );
  delayMicroseconds(10);
  digitalWrite( trigPin, LOW );
  unsigned long period = pulseIn( echoPin, HIGH );
  return period * 343 / 2000;
}

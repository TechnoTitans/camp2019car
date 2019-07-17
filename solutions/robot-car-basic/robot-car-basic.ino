#include <SoftwareSerial.h>
#include <Servo.h>

SoftwareSerial SerialBT(10, 9);
Servo arm;

char d;
int armPos = 90;
unsigned long period;

const int in1Pin = 4; // Left motor Direction 1
const int in2Pin = 3; // Left motor Direction 2
const int in3Pin = 2; // Right motor Direction 1
const int in4Pin = 5; // Right motor Direction 2
const int armPin = 11; //signal pin for ultrasonic servo
const int triggerPin = 13;
const int echoPin = 12;

void setup() {
  SerialBT.begin(38400);
  Serial.begin(115200);
  Serial.println("ready");

  pinMode(in1Pin, OUTPUT);
  pinMode(in2Pin, OUTPUT);
  pinMode(in3Pin, OUTPUT);
  pinMode(in4Pin, OUTPUT);
  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin, INPUT);

  digitalWrite(triggerPin, LOW);
  arm.attach(armPin);
  arm.write(90);
}

void loop() {
  if (SerialBT.available() > 0) {
    d = SerialBT.read();

    if (d == 'W') {
      fwd();
    }
    else if (d == 'S') {
      bwd();
    }
    else if (d == 'A') {
      left();
    }
    else if (d == 'D') {
      right();
    }
    else if (d == 'R') {
      armPos += 3;
    }
    else if (d == 'L') {
      armPos -= 3;
    }
    else if (d == 'Z') {
      autonomous();
    }
  }
  else stop();
  constrain(armPos, LOW, 180);
  arm.write(armPos);
}

void fwd() {
  digitalWrite(in1Pin, HIGH);
  digitalWrite(in2Pin, LOW);
  digitalWrite(in3Pin, HIGH);
  digitalWrite(in4Pin, LOW);
  delay(100);
}

void bwd() {
  digitalWrite(in1Pin, LOW);
  digitalWrite(in2Pin, HIGH);
  digitalWrite(in3Pin, LOW);
  digitalWrite(in4Pin, HIGH);
  delay(100);
}

void left() {
  digitalWrite(in1Pin, HIGH);
  digitalWrite(in2Pin, LOW);
  digitalWrite(in3Pin, LOW);
  digitalWrite(in4Pin, HIGH);
  delay(75);
}

void right() {
  digitalWrite(in1Pin, LOW);
  digitalWrite(in2Pin, HIGH);
  digitalWrite(in3Pin, HIGH);
  digitalWrite(in4Pin, LOW);
  delay(75);
}

void stop() {
  digitalWrite(in1Pin, LOW);
  digitalWrite(in2Pin, LOW);
  digitalWrite(in3Pin, LOW);
  digitalWrite(in4Pin, LOW);
}

unsigned int readDistance()
{
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  period = pulseIn(echoPin, HIGH);
  return period * 343 / 2000;
}

bool mazeComplete = false;
void autonomous() {
  Serial.println("Auto Engaged");
  while(!mazeComplete) {    
    if (SerialBT.available()) {
      d = SerialBT.read();
    }
    if (d == 'X') {
      // we will stop the autonomous if we send the letter 'X'
      break;
    }
    // Write your autonomous code under this line
    // use the functions:
    // fwd(), bwd(), left(), right(), and stop()
    // you can also use readDistance() to get the distance from the ultrasonic sensor

    // Here is an example auto. It is bad, but you will make it better

    // Movement
    if(readDistance() < 100) {
      left();
      delay(500); // CHANGE THIS VALUE. how many seconds should we turn?
      stop();
    } else {
      fwd();
      delay(500); // CHANGE THIS VALUE. how many seconds should we go forward?
      stop();
    }

    // Goal Tracking
    // if there is an opening that is super far, 
    if(readDistance() > 2000) { // choose the distance that 
      mazeComplete = true; // we decide that we finished our maze
    }


  }
  Serial.println("Auto Finished");
}
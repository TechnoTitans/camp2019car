#include <SoftwareSerial.h>
#include <Servo.h>

SoftwareSerial SerialBT(10, 9); // Make sure you connect the bluetooth to these pins
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
  SerialBT.begin(9600); //Bluetooth device name
  Serial.begin(115200);
  Serial.println("ready");

  pinMode([blank], OUTPUT); // what are the four motor pins (hint: look at lines 11-14)
  pinMode([blank], OUTPUT); 
  pinMode([blank], OUTPUT);
  pinMode([blank], OUTPUT);
  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin, INPUT);

  digitalWrite(triggerPin, LOW);
  arm.attach([blank]); // what is the pin for the arm
  arm.write([blank]);  // what angle do you want the arm to start off at?
}

void loop() {
  if (SerialBT.available() > 0) {
    d = SerialBT.read();

    // this part handles the controls
    if (d == 'F') {
      fwd();
    }
    else if (d == 'B') {
      bwd();
    }
    else if (d == 'L') {
      left();
    }
    else if (d == 'R') {
      right();
    }
    else if (d == 'Q') {
      // remember, the arm is a servo
      armPos += [blank]; // how many degrees do you want the arm to move right by
    }
    else if (d == 'A') {
      armPos -= [blank]; // how many degrees do you want the arm to move left by
    }
    else if (d == 'Z') {
      autonomous();
    }
  }
  else stop();
  constrain(armPos, 0, 180);
  arm.write(armPos);
  //SerialBT.("e"); // E
}

void fwd() {
  // fill in the blanks with HIGH or LOW so that the motors turn forward
  digitalWrite(in1Pin, [blank]); // do we want to turn on pin one? type in HIGH or LOW
  digitalWrite(in2Pin, [blank]); // do we want to turn on pin two? type in HIGH or LOW
  digitalWrite(in3Pin, [blank]); // do we want to turn on pin three? type in HIGH or LOW
  digitalWrite(in4Pin, [blank]); // do we want to turn on pin four? type in HIGH or LOW
  delay(100);
}

void bwd() {
  // here, make the car turn backwards
  // go back to fwd() if you need help
  digitalWrite([blank], [blank]); // fill in the two blanks. the first blank should be a pin variable. the second should be HIGH or LOW
  digitalWrite([blank], [blank]); // fill in the two blanks. the first blank should be a pin variable. the second should be HIGH or LOW
  digitalWrite([blank], [blank]); // fill in the two blanks. the first blank should be a pin variable. the second should be HIGH or LOW
  digitalWrite([blank], [blank]); // fill in the two blanks. the first blank should be a pin variable. the second should be HIGH or LOW
  delay(100);
}

void left() {
  // here, make the car turn left
  // go back to fwd() if you need help
  digitalWrite([blank], [blank]); // fill in the two blanks.
  digitalWrite([blank], [blank]); // fill in the two blanks.
  digitalWrite([blank], [blank]); // fill in the two blanks.
  digitalWrite([blank], [blank]); // fill in the two blanks.
  delay(75);
}

void right() {
  // here, make the car turn right
  // go back to fwd() if you need help
  digitalWrite([blank], [blank]); // fill in the two blanks.
  digitalWrite([blank], [blank]); // fill in the two blanks.
  digitalWrite([blank], [blank]); // fill in the two blanks.
  digitalWrite([blank], [blank]); // fill in the two blanks.
  delay(75);
}

void stop() {
  // do the same as fwd() or bwd()
  // hint, all pins should be turned off
  digitalWrite([blank], [blank]); // fill in the two blanks.
  digitalWrite([blank], [blank]); // fill in the two blanks.
  digitalWrite([blank], [blank]); // fill in the two blanks.
  digitalWrite([blank], [blank]); // fill in the two blanks.
}


// REPLACE THIS CODE WHEN INSTRUCTED

//===========================================================
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
    

  }
  Serial.println("Auto Finished");
}
//===========================================================

// MAGIC CODE - DO NOT TOUCH

unsigned int readDistance()
{
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  period = pulseIn(echoPin, HIGH);
  return period * 343 / 2000;
}


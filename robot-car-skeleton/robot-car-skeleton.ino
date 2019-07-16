#include <Servo.h>
#include <SoftwareSerial.h>


/*
 * 
 * ========= IMPORTANT =========
 * 
 * LIST OF PROVIDED FUNCTIONS:
 * setSpeed(enum Motor, int speed) - sets the speed of the motor
 * readDistance() - gets the distance from the ultrasonic sensor
 */








// Ultrasonic Module pins
const int trigPin = /* put the correct pin number here */;
const int echoPin = /* put the correct pin number here */; 

// Servo motor that aims ultrasonic sensor.
const int servoPin = /* put the correct pin number here */; // PWM output for hobby servo

// Motor control pins: L298N H bridge
const int enAPin = /* put the correct pin number here */; // Left motor PWM speed control
const int in1Pin = /* put the correct pin number here */; // Left motor Direction 1
const int in2Pin = /* put the correct pin number here */; // Left motor Direction 2
const int in3Pin = /* put the correct pin number here */; // Right motor Direction 1
const int in4Pin = /* put the correct pin number here */; // Right motor Direction 2
const int enBPin = /* put the correct pin number here */; // Right motor PWM speed control

enum Motor { LEFT, RIGHT };

Servo servo;
SoftwareSerial mySerial(10, 9); // TX/RX pins

int angle = /* Fill in the angle you want the servo to start at */;

void setup() {
  mySerial.begin(115200);
  Serial.begin(9600);

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
  servo.write(angle);

  // make sure the motors are reset to 0 speed on reupload
  setSpeed(LEFT, 0);
  setSpeed(RIGHT, 0);
}



void loop() {
  Serial.print("The distance is: ");
  Serial.println(/* call the appropriate function here */ ); // [blank] look at the list of provided functions, and find a function that gives you the distance
  
  String btCommand; //string to hold data from BT module 

  btCommand = readBluetoothCommand();
  
  if(t.length()) { //if string is not empty do the following
    switch (t.charAt(0)) {
          Serial.print(t);

      case 'w':
        Serial.print("Forward\n");
        // [blank] What lines of code do you need to make the car go forward?
        setSpeed(/* fill in the info */);
        setSpeed(/* fill in the info */);
        break;
      case 'd':
        Serial.print("Right\n");
        // [blank] What lines of code do you need to make the car go right?
        setSpeed(/* fill in the info */);
        setSpeed(/* fill in the info */);
        break;
      case 'a':
        Serial.print("Left\n");
        // [blank] What lines of code do you need to make the car go left?
        setSpeed(/* fill in the info */);
        setSpeed(/* fill in the info */);
        break;
      case 's':
        Serial.print("Backward\n");
        // [blank] What lines of code do you need to make the car go backward?
        setSpeed(/* fill in the info */);
        setSpeed(/* fill in the info */);
        break;
      case ' ':
        // [blank] What lines of code do you need to make the car stop?
        setSpeed(/* fill in the info */);
        setSpeed(/* fill in the info */);
        break;
      default:
        Serial.print("Invalid Command\n");
        // [blank] What lines of code do you need to make the car stop (same as above)?
        setSpeed(/* fill in the info */);
        setSpeed(/* fill in the info */);
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


// Magic Code - Do Not Touch

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


char readBluetoothCommand() {
  // TODO should it be available() > 0?
  while(mySerial.available()) { //keep reading bytes while they are still more in the buffer
    return (char) mySerial.read(); //read byte, convert to char, and append it to string
  }
}

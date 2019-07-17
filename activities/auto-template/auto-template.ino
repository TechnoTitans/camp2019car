// Replace the autonomous code in the robot-car-basic with this code to get started

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
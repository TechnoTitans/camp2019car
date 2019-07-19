void checkDelay(int milliseconds) {
  for (int i = 0; i < milliseconds / 10; i++) {
    mazeComplete = SerialBT.read() == 'X';
    delay(10);
    if (mazeComplete) {
      break;
    }
  }
}

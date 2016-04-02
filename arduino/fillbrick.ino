//Pin connected to ST_CP of 74HC595
const int LATCHPIN = 12;
//Pin connected to SH_CP of 74HC595
const int CLOCKPIN = 11;
// Pin connected to DS of 74HC595
const int DATAPIN = 13;
// Number of pins
const int BOARDHEIGHT = 5;
// Delay
const int DELAY = 200;

void sendData(byte data) {
  // 001010
  for (int i = 0; i < boardHeight; i++) {
    digitalWrite(LATCHPIN, LOW);
    // shift out the bits:
    digitalWrite(DATAPIN, data[i]);
    //take the latch pin high so the LEDs will light up:
    digitalWrite(LATCHPIN, HIGH);
    Serial.print(bitRead(data, i));
  }
  //digitalWrite(0);
  Serial.print(0);
  Serial.println();
}

void diagonalLines() {
  // count from 1 (0x00001) to 32 (0x10000)
  // note: the furthest right pin is disconnected; drop the right most digit in binary
  for (byte a = 1; a< 32;a*=2) {
    sendData(a);
    delay(DELAY);
  }
}

void setup() {
  pinMode(LATCHPIN, OUTPUT);
  pinMode(CLOCKPIN, OUTPUT);
  pinMode(DATAPIN, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  diagonalLines()
}

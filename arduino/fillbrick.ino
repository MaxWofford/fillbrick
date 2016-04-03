//Pin connected to ST_CP of 74HC595
const int LATCHPIN = 12;
//Pin connected to SH_CP of 74HC595
const int CLOCKPIN = 11;
// Pin connected to DS of 74HC595
const int DATAPIN = 13;
// Number of pins
const int BOARDHEIGHT = 5;
// Refresh rate
const int DELAY = 200;

// Test pattern smiley face
const int data[10] = {7,1,13,1,1,13,1,7,0,0};

void diagonalLines() {
  // count from 1 (0x00001) to 32 (0x10000)
  // note: the furthest right pin is disconnected; drop the right most digit in binary
  for (byte a = 1; a < 8; a++) {
    shiftOut(DATAPIN, CLOCKPIN, LSBFIRST, a);
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
  for (int a = 0; a < 10; a++) {
    // Bit shift twice because the first pin on each shift register is unused
    int b = data[a] << 2;
    digitalWrite(LATCHPIN, LOW);
    shiftOut(DATAPIN, CLOCKPIN, LSBFIRST, b);
    digitalWrite(LATCHPIN, HIGH);
    delay(DELAY);
  }
}

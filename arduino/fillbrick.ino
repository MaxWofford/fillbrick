//Pin connected to ST_CP of 74HC595
const int latchPin = 12;
//Pin connected to SH_CP of 74HC595
const int clockPin = 11;
////Pin connected to DS of 74HC595
const int dataPin = 13;

void setup() {
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
}

void loop() {
  // count from 2 (0x00001) to 32 (0x10000)
  // note: the furthest right pin is disconnected; drop the right most digit in binary
  for (int a = 2 ; a< 32;a*=2) {
    digitalWrite(latchPin, LOW);
    // shift out the bits:
    shiftOut(dataPin, clockPin, MSBFIRST, data[a]);
    //take the latch pin high so the LEDs will light up:
    digitalWrite(latchPin, HIGH);
    // pause before next value:
    delay(500);
  }
}


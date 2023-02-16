#include <PZEM004Tv30.h>

#define RX_PZEM 17
#define TX_PZEM 16

PZEM004Tv30 pzem(Serial1,0x03);

const unsigned long interval = 1000;    // 10 s interval to send message
unsigned long previousMillis = 0;  // will store last time message sent


void setup() {
  // put your setup code here, to run once:
  Serial.begin(19200);
}

void loop() {
  if (millis() - previousMillis > interval) {
    readSensor();
    previousMillis = millis();
  }
}

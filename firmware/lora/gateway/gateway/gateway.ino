/*
  LoRa Duplex communication

  Sends a message every half second, and polls continually
  for new incoming messages. Implements a one-byte addressing scheme,
  with 0xFF as the broadcast address.

  Uses readString() from Stream class to read payload. The Stream class'
  timeout may affect other functuons, like the radio's callback. For an

  created 28 April 2017
  by Tom Igoe
*/
#include <SPI.h>              // include libraries
#include <LoRa.h>

const int csPin = 5;          // LoRa radio chip select
const int resetPin = 27;       // LoRa radio reset
const int irqPin = 1;         // change for your board; must be a hardware interrupt pin

String outgoing;              // outgoing message
String dataIn = "";
String dataParse[2];
int flag_dataParse = 0;

byte msgCount = 0;            // count of outgoing messages
byte localAddress = 0x01;     // address of this device
byte destination = 0x02;      // destination to send to
int destinationFinal = 0x03;
long lastSendTime = 0;        // last send time
int interval = 2000;          // interval between sends

void setup() {
  Serial.begin(9600);                   // initialize serial
  while (!Serial);

  Serial.println("LoRa Duplex");

  // override the default CS, reset, and IRQ pins (optional)
  LoRa.setPins(csPin, resetPin, irqPin);// set CS, reset, IRQ pin

  if (!LoRa.begin(915E6)) {             // initialize ratio at 915 MHz
    Serial.println("LoRa init failed. Check your connections.");
    while (true);                       // if failed, do nothing
  }

  Serial.println("LoRa init succeeded.");
}

void loop() {
  if (Serial.available()) {
    char inByte = (char)Serial.read();
    dataIn += inByte;
    if (inByte == '\n') {
      for (int i = 0; i < dataIn.length() - 1; i++) {
        if (dataIn[i] == '*') {
          flag_dataParse++;
        }
        else {
          dataParse[flag_dataParse] += dataIn[i];
        }
      }
      destinationFinal = dataParse[0].toInt();
      sendMessage(dataParse[1]);
      dataIn = "";
      flag_dataParse = 0;

      for (int i = 0; i < 2; i++) {
        dataParse[i] = "";
      }
    }
  }

  // parse for a packet, and call onReceive with the result:
  onReceive(LoRa.parsePacket());
}

void sendMessage(String outgoing) {
  LoRa.beginPacket();                   // start packet
  LoRa.write(destination);              // add destination address
  LoRa.write(destinationFinal);         // add destination address Final
  LoRa.write(localAddress);             // add sender address
  LoRa.write(localAddress);
  LoRa.write(msgCount);                 // add message ID
  LoRa.write(outgoing.length());        // add payload length
  LoRa.print(outgoing);                 // add payload
  LoRa.endPacket();                     // finish packet and send it
  msgCount++;                           // increment message ID
}

void onReceive(int packetSize) {
  if (packetSize == 0) return;          // if there's no packet, return

  // read packet header bytes:
  int recipient = LoRa.read();          // recipient address
  int recipientFinal = LoRa.read();     // recipient address Final
  byte sender = LoRa.read();            // sender address
  byte senderReqRes = LoRa.read();     // sender request data address
  byte incomingMsgId = LoRa.read();     // incoming msg ID
  byte incomingLength = LoRa.read();    // incoming msg length

  String incoming = "";

  while (LoRa.available()) {
    incoming += (char)LoRa.read();
  }

  if (incomingLength != incoming.length()) {   // check length for error
    Serial.println("error: message length does not match length");
    return;                             // skip rest of function
  }

  // if the recipient isn't this device or broadcast,
  if (recipient != localAddress && recipient != 0xFF) {
    Serial.println("This message is not for me.");
    return;                             // skip rest of function
  }

  // if message is for this device, or broadcast, print details:
  Serial.println("Received from: 0x" + String(sender, HEX));
  Serial.println("Received Request from: 0x" + String(senderReqRes, HEX));
  Serial.println("Sent to: 0x" + String(recipient, HEX));
  Serial.println("Sent to: 0x" + String(recipientFinal, HEX));
  Serial.println("Message ID: " + String(incomingMsgId));
  Serial.println("Message length: " + String(incomingLength));
  Serial.println("Message: " + incoming);
  Serial.println("RSSI: " + String(LoRa.packetRssi()));
  Serial.println("Snr: " + String(LoRa.packetSnr()));
  Serial.println();
}

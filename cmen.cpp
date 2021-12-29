#include "cmen.h"

bool sender = false;
bool receiver = false;

RF24 radio(CE_pin, CSN_pin);

void genericSetup() {
  SerialUSB.begin(69);
  while(!SerialUSB);
  SerialUSB.println("Serial ready - performing system checks...");

  radio.begin();
  while(!radio.isChipConnected());
  SerialUSB.println("Transceiver found");
  while(!radio.isValid());
  SerialUSB.println("Radio is valid");
}

void setAsReceiver(int address_index) {
  genericSetup();
  receiver = true;
  SerialUSB.println("Unit set as receiver");
  radio.openReadingPipe(0, Setup::addresses[address_index]);
  radio.startListening();
}

void setAsSender(int address_index) {
  genericSetup();
  sender = true;
  SerialUSB.println("Unit set as sender");
  radio.openWritingPipe(Setup::addresses[address_index]);
  radio.stopListening();
}

void setAsDuplex(int r, int w) {
  genericSetup();
  sender = true;
  receiver = true;
  SerialUSB.println("Unit set as duplex");
  radio.openReadingPipe(0, Setup::addresses[r]);
  radio.openWritingPipe(Setup::addresses[w]);
  radio.startListening();
}

void sendData() {
  const char text[] = "Hello World";
  radio.write(&text, sizeof(text));
  SerialUSB.print("Sent: ");
  SerialUSB.print(text);
  SerialUSB.print(": ");
  SerialUSB.println(sizeof(text));
  delay(1000);
}

void receiveData() {
  if(radio.available()) {
    char text[32] = {0};
    radio.read(&text, sizeof(text));
    SerialUSB.print("Received: ");
    SerialUSB.println(text);

    if(String(text) == "pattern_1") {
      SerialUSB.println("Pattern 1 detected!");
    }
  }
}

void transceiveData() {
  if(sender == true) {
    sendData();
  }

  if(receiver == true) {
    receiveData();
  }
}

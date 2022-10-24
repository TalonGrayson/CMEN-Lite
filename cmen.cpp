#include "cmen.h"

bool sender = false;
bool receiver = false;

RF24 radio(CE_pin, CSN_pin);

void genericSetup() {
  if(debug == true) {
    SerialUSB.begin(69);
    while(!SerialUSB);
    SerialUSB.println("Serial ready - performing system checks...");
  }

  radio.begin();
  while(!radio.isChipConnected());
  if(debug == true) {
    SerialUSB.println("Transceiver found");
  }
  while(!radio.isValid());
  if(debug == true) {
    SerialUSB.println("Radio is valid");
  }
}

void setAsReceiver(int address_index) {
  genericSetup();
  receiver = true;
  if(debug == true) {
    SerialUSB.println("Unit set as receiver");
    SerialUSB.print("Listening on ");
    SerialUSB.println(address_index);
  }
  radio.openReadingPipe(0, Setup::addresses[address_index]);
  radio.startListening();
}

void setAsSender(int address_index) {
  genericSetup();
  sender = true;
  if(debug == true) {
    SerialUSB.println("Unit set as sender");
    SerialUSB.print("Sending on ");
    SerialUSB.println(address_index);
  }
  radio.openWritingPipe(Setup::addresses[address_index]);
  radio.stopListening();
}

void setAsDuplex(int r, int w) {
  genericSetup();
  sender = true;
  receiver = true;
  if(debug == true) {
    SerialUSB.println("Unit set as duplex");
  }
  radio.openReadingPipe(0, Setup::addresses[r]);
  radio.openWritingPipe(Setup::addresses[w]);
  radio.startListening();
}

void sendData() {
  const char text[] = "hello_world";
  radio.write(&text, sizeof(text));
  if(debug == true) {
    SerialUSB.print("Sent: ");
    SerialUSB.print(text);
    SerialUSB.print(": ");
    SerialUSB.println(sizeof(text));
  }
  delay(1000);
}

void receiveData() {
  if(radio.available()) {
    char text[32] = {0};
    radio.read(&text, sizeof(text));
    if(debug == true) {
      SerialUSB.print("Received: ");
      SerialUSB.println(text);

      if(String(text) == "hello_world") {
        SerialUSB.println("hello_world received!");
      }
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

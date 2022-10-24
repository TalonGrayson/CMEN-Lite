// Cosplay Modular Effects Network

#include "cmen.h"

int CE_pin = 6;         // Should match TX pin
int CSN_pin = 7;        // Should match RX pin
int address_index = 0;  // Can be 0-5
bool debug = false;  // Set to true to see output in Serial Monitor - if this is true when not connected to USB, CMEN won't work.
  
void setup() {
  setAsSender(address_index);
}
 
void loop() {
  transceiveData();
}

// Cosplay Modular Effects Network

#include "cmen.h"

int CE_pin = 6;         // Should match TX pin
int CSN_pin = 7;        // Should match RX pin
int address_index = 0;  // Can be 0-5
  
void setup() {
  setAsReceiver(address_index);
}
 
void loop() {
  transceiveData();
}

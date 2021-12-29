#ifndef CMEN_H
#define CMEN_H
#include <Arduino.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

namespace Setup {
  const uint8_t addresses[][6] = {"1CMEN", "2CMEN", "3CMEN", "4CMEN", "5CMEN", "6CMEN"};
}

extern int CE_pin;
extern int CSN_pin;
//extern int address_index;

// Prototypes
void genericSetup();
void setAsReceiver(int address_index);
void setAsSender(int address_index);
void setAsDuplex(int r, int w);
void sendData();
void receiveData();
void transceiveData();

#endif

/*
 * iboard-mysensors-ethernet-gateway.ino - Firmware for iboard based MySensors EthernetUDP Gateway
 *
 * Copyright (C) 2014  Tomas Hozza <thozza@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, see <http://www.gnu.org/licenses/>.
 *
 * Authors:
 * Tomas Hozza <thozza@gmail.com>
 *
 * MySensors library - http://www.mysensors.org/
 * iboard - http://imall.iteadstudio.com/development-platform/arduino/arduino-compatible-mainboard/im120410001.html
 * nRF24L01+ spec - https://www.sparkfun.com/datasheets/Wireless/Nordic/nRF24L01P_Product_Specification_1_0.pdf
 */

#include <SoftSPI.h>
#include <MyGateway.h>
#include <SPI.h>
#include <Ethernet.h>
#include <EthernetUdp.h>

#define SERVER_PORT 5003
#define IP_RENEWAL_INTERVAL 60000  // in milliseconds

/***********************************/
/********* PIN DEFINITIONS *********/
/***********************************/
#define RF24_CE_pin 3
#define RF24_CS_pin 8

/*****************************/
/********* FUNCTIONS *********/
/*****************************/
byte *get_random_mac();
void renewIP();
void writeEthernet(char *writeEthernet);

/************************************/
/********* GLOBAL VARIABLES *********/
/************************************/
MyGateway gateway(RF24_CE_pin, RF24_CS_pin);
EthernetUDP server;
static char recvBuffer[MAX_RECEIVE_LENGTH];

/**********************************/
/********* IMPLEMENTATION *********/
/**********************************/
/**
 * Initialization
 */
void setup() {
  Serial.begin(115200);
  // Configure Ethernet with random MAC address
  if (Ethernet.begin(get_random_mac()) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
  } else {
    Serial.print("My IP address: ");
    Serial.println(Ethernet.localIP());
  }
  // give the Ethernet chip second to initialize
  delay(1000);

  /* configure the UDP server */
  server.begin(SERVER_PORT);
  
  gateway.begin(RF24_PA_LEVEL_GW, RF24_CHANNEL, RF24_DATARATE, writeEthernet);
}

/**
 * Main logic
 */
void loop() {
  /* renew the IP address */
  renewIP();

  int packet_size = server.parsePacket();
  if (server.available()) {
   server.read(recvBuffer, MAX_RECEIVE_LENGTH);
   gateway.parseAndSend(recvBuffer);
  }

  gateway.processRadioMessage();
}

/**
 * Send data to the remote controller via UDP
 */
void writeEthernet(char *writeBuffer) {
#ifndef GATEWAY_CONTROLLER_DISCOVERY
  server.write(writeBuffer);
#else
  char buffer[16];
  snprintf_P(buffer, 16, PSTR("0;0;%d;0;%d;"), C_INTERNAL, I_CONTROLLER_DISCOVERY);

  if (strstr(writeBuffer, buffer) != NULL) {
    /* Controller Discovery msg -> broadcast it! */
    server.beginPacket(getBroadcastIP(Ethernet.localIP(), Ethernet.subnetMask()), gateway.getControllerPort());
  }
  else if (gateway.getControllerIP() == INADDR_NONE) {
    Serial.println(PSTR("Invalid controller IP - NOT Sending ethernet msg"));
    return;
  }
  else {
    server.beginPacket(gateway.getControllerIP(), gateway.getControllerPort());
  }
  server.write(writeBuffer, strlen(writeBuffer));
  server.endPacket();
#endif /* GATEWAY_CONTROLLER_DISCOVERY */
}

/**
 * Renew the IP address
 */
void renewIP() {
  /* renew/rebind IP address
  0 - nothing happened
  1 - renew failed
  2 - renew success
  3 - rebinf failed
  4 - rebind success
  */
  static unsigned long next_time = millis() + IP_RENEWAL_INTERVAL;
  unsigned long now = millis();

  // http://playground.arduino.cc/Code/TimingRollover
  if ((long)(now - next_time) < 0)
    return;

  if (Ethernet.maintain() & ~(0x06)) {
    Serial.println("Failed to renew/rebind IP address using DHCP");
    return;
  }

  next_time = now + IP_RENEWAL_INTERVAL;
  Serial.print("My IP address: ");
  Serial.println(Ethernet.localIP());
  return;
}

/**
 * Get random MAC address.
 */
byte *get_random_mac() {
  static byte mac[6];
  mac[0] = 0xDE;
  mac[1] = 0xAD;
  mac[2] = 0xBB;

  /* initialize the random generator */
  randomSeed(analogRead(0));

  for (int i = 3; i < 6; ++i) {
    mac[i] = random(0x00, 0xFF);
  }

  return mac;
}

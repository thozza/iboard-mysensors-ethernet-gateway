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

#define SERVER_PORT 42424
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
bool renewIP();
void writeUDP(char *data);

/************************************/
/********* GLOBAL VARIABLES *********/
/************************************/
MyGateway gateway(RF24_CE_pin, RF24_CS_pin);
EthernetUDP server;
static char recvBuffer[UDP_TX_PACKET_MAX_SIZE];
IPAddress CONTROLLER_IP(192, 168, 122, 1);

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
  
  gateway.begin(RF24_PA_LEVEL_GW, RF24_CHANNEL, RF24_DATARATE, writeUDP);
}

/**
 * Main logic
 */
void loop() {
  /* renew the IP address */
  if (renewIP() == false)
    return;

  int packet_size = server.parsePacket();
  if (server.available()) {
   server.read(recvBuffer, UDP_TX_PACKET_MAX_SIZE);
   gateway.parseAndSend(recvBuffer);
  }

  gateway.processRadioMessage();
}

/**
 * Send data to the remote controller via UDP
 */
void writeUDP(char *data) {
  Serial.print("Data for controller: ");
  Serial.println(data);

  server.beginPacket(CONTROLLER_IP, SERVER_PORT);
  server.write((const uint8_t*)data, strlen(data));
  server.endPacket();
}

/**
 * Renew the IP address
 */
bool renewIP() {
  /* renew/rebind IP address
  0 - nothing happened
  1 - renew failed
  2 - renew success
  3 - rebinf failed
  4 - rebind success
  */
  static unsigned long last_time = millis();
  unsigned long now = millis();
  
  // TODO: may fail on overflow
  if (last_time + IP_RENEWAL_INTERVAL > now)
    return true;

  if (Ethernet.maintain() & ~(0x06)) {
    Serial.println("Failed to renew/rebind IP address using DHCP");
    return false;
  }

  last_time = now;
  Serial.print("My IP address: ");
  Serial.println(Ethernet.localIP());
  return true;
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

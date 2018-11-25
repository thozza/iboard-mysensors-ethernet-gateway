/*
 * iboard-mysensors-ethernet-gateway.ino - Firmware for iboard based MySensors EthernetUDP Gateway
 *
 * Copyright (C) 2014-2018  Tomas Hozza <thozza@gmail.com>
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

#define MY_DEBUG
#define MY_DEBUG_VERBOSE
//#define MY_DEBUG_VERBOSE_RF24
//#define MY_SIGNAL_REPORT_ENABLED

#define MY_RADIO_RF24
#define MY_GATEWAY_W5100

#define MY_RF24_CE_PIN 3
#define MY_RF24_CS_PIN 8
#define MY_RF24_IRQ_PIN 2

/**
 * - 0 => 2400 Mhz (RF24 channel 1)
 * - 1 => 2401 Mhz (RF24 channel 2)
 * - 76 => 2476 Mhz (RF24 channel 77)
 * - 83 => 2483 Mhz (RF24 channel 84)
 * - 124 => 2524 Mhz (RF24 channel 125)
 * - 125 => 2525 Mhz (RF24 channel 126)
 * @see http://www.bundesnetzagentur.de/SharedDocs/Downloads/DE/Sachgebiete/Telekommunikation/Unternehmen_Institutionen/Frequenzen/Allgemeinzuteilungen/2013_10_WLAN_2,4GHz_pdf.pdf
 */
#define MY_RF24_CHANNEL         76             //RF channel for the sensor net, 0-127
#define MY_RF24_DATARATE        RF24_250KBPS   //RF24_250KBPS for 250kbs, RF24_1MBPS for 1Mbps, or RF24_2MBPS for 2Mbps
#define MY_RF24_PA_LEVEL 	      RF24_PA_MAX    //Sensor PA Level == RF24_PA_MIN=-18dBm, RF24_PA_LOW=-12dBm, RF24_PA_HIGH=-6dBM, and RF24_PA_MAX=0dBm
#define MY_RF24_BASE_RADIO_ID   0x00,0xFC,0xE1,0xA8,0xA8

//#define MY_RX_MESSAGE_BUFFER_FEATURE

#define MY_SOFTSPI
#define MY_SOFT_SPI_SCK_PIN 7
#define MY_SOFT_SPI_MISO_PIN 6
#define MY_SOFT_SPI_MOSI_PIN 5

//#define MY_NODE_ID (AUTO)
//#define MY_PARENT_NODE_ID (AUTO)

#define MY_IP_RENEWAL_INTERVAL 60*60*1000ul   // in ms

#define MY_PORT 5003
//#define MY_MAC_ADDRESS 0xDE,0xAD,0xBE,0xEF,0xFE,0xED

#define MY_DEFAULT_LED_BLINK_PERIOD 300

#define MY_DEFAULT_ERR_LED_PIN A2  // Error led pin
#define MY_DEFAULT_RX_LED_PIN  A3  // Receive led pin
#define MY_DEFAULT_TX_LED_PIN  A4  // Transmit led pin

#define MY_SPLASH_SCREEN_DISABLED

#include <Ethernet.h>
#include <MySensors.h>

/**********************************/
/********* IMPLEMENTATION *********/
/**********************************/

void setup()
{
  // Setup locally attached sensors
}

void presentation()
{
  // Present locally attached sensors here
}

void loop()
{
  // Send locally attached sensors data here
}

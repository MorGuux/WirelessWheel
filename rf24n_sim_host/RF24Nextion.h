/*
  RF24Nextion.h - Nextion manager for WirelessWheel
  Created by Morgan Gardner, November 23th, 2020.
  Released under the GPL-3.0 license.
*/

#ifndef Nextion_h
#define Nextion_h

#include "Arduino.h"

class Nextion
{
  public:
    void initNextion()
    {

    }
    
    void receiveNextion(RF24NetworkHeader& header)
    {
      network.read(header, &nexData, sizeof(nexData));


    }

    void sendNextion()
    {
        int ledLC = Serial.readBytesUntil('\n', nexData, sizeof(nexData));
        RF24NetworkHeader nexReader(PERIPHERAL_ADDRESS, 'n'); //"n" packet for nextion
        network.write(nexReader, &nexData, sizeof(nexData));
    }
  private:
    byte nexData[24];
};

#endif

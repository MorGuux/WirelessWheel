
/*
  HIDHandler.h - HID manager for WirelessWheel
  Created by Morgan Gardner, November 23th, 2020.
  Released under the GPL-3.0 license.
*/

#ifndef HIDHandler_h
#define HIDHandler_h

#include "Arduino.h"
#include <Joystick.h>

class HIDHandler
{
  public:

    void sendButtons(int buttonIndex, bool value)
    {
      bitWrite(buttonData.btnData, buttonIndex, value);  //write "value" to "btnData" at position "buttonIndex"
  
      RF24NetworkHeader btnHeader(HOST_ADDRESS, 'b');   //create header of label "b" for buttons
      network.write(btnHeader, &buttonData, sizeof(buttonData));
    }

  private:

    struct buttondef
    {
      uint32_t btnData; //32 button data
    };

    struct rotariesdef
    {
      byte pin1;
      byte pin2;
      int ccwchar;
      int cwchar;
      volatile unsigned char state;
    };

    buttondef buttonData;


};

#endif

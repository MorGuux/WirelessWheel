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
    void initHID()
    {
      Joystick.begin();
    }

    void setButtonState(int index, bool state)
    {
        Joystick.setButton(index, state);
    }

    bool getButtonState(int index)
    {
        return Joystick.getButtonState(index);
    }

    void receiveButtons(RF24NetworkHeader& header)
    {
        network.read(header, &buttonData, sizeof(buttonData));

        for (int i = 0; i < buttonCount; i++)  //per button
        {
            setButtonState(i, bitRead(buttonData.btnData, i)); //set button "i" to "buttonData" bit value
        }
    }

  private:
    Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID,      //report id
        JOYSTICK_TYPE_MULTI_AXIS,   //joystick type
        NUM_BUTTONS,    //number of buttons
        2,      //hat switch count
        true,   //x axis
        true,   //y axis
        true,   //z axis
        true,   //Rx axis
        true,   //Ry axis
        true,   //Rz axis
        true,   //Rudder axis
        true,   //Throttle axis
        true,   //Accelerator axis
        true,   //Brake axis
        true);  //Steering axis

        struct buttondef
        {
            uint32 btnData; //32 button data
        }

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

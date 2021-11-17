/*
  RF24ButtonMatrix.h - Button matrix manager for WirelessWheel
  Created by Morgan Gardner, November 23th, 2020.
  Released under the GPL-3.0 license.
*/

#ifndef ButtonMatrix_h
#define ButtonMatrix_h

#include "Arduino.h"
#include <Keypad.h>

class ButtonMatrix
{
  public:
    void initMatrix()
    {
      rotaryInit(); //initialise rotaries
    }

    
  private:

  void rotaryInit()
  {
    for (int i = 0; i < NUM_ROTARIES; i++)
    {
      pinMode(rotaries[i].pin1, INPUT);
      pinMode(rotaries[i].pin2, INPUT);
    #ifdef ENABLE_PULLUPS
      digitalWrite(rotaries[i].pin1, HIGH);
      digitalWrite(rotaries[i].pin2, HIGH);
    #endif
    }
  }


};

#endif

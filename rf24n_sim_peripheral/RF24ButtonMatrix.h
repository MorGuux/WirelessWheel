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
      //initButtonStruct();
    }


  private:
    //byte buttons[NUM_ROWS][NUM_COLS] = {};

    byte buttons[NUM_ROWS][NUM_COLS] = {
  {0,1,2,3,4},
  {5,6,7,8,9},
  {10,11,12,13,14},
  {15,16,17,18,19},
  {20,21,22,23},
};

    struct rotariesdef
    {
      byte pin1;
      byte pin2;
      int ccwchar;
      int cwchar;
      volatile unsigned char state;
    };

    rotariesdef rotaries[NUM_ROTARIES]
    {
      {0,1,24,25,0},
      {2,3,26,27,0},
      {4,5,28,29,0},
      {6,7,30,31,0},
    };

    void rotaryInit()
    {
      for (int i = 0; i < NUM_ROTARIES; i++)
      {
//        &rotaries[i] = new rotariesdef;
//        &rotaries[i].pin1 = i;
//        &rotaries[i].pin2 = i + 1;
//        &rotaries[i].ccwchar = i + 24;
//        &rotaries[i].cwchar = (i * 2) + 24;
        
        pinMode(&rotaries[i].pin1, INPUT);
        pinMode(&rotaries[i].pin2, INPUT);
      #ifdef ENABLE_PULLUPS
        digitalWrite(&rotaries[i].pin1, HIGH);
        digitalWrite(&rotaries[i].pin2, HIGH);
      #endif
      }
    }

    void initButtonStruct()
    {
      int arrayIndex;
      for(int x = 0; x < NUM_ROWS; x++) //row
      {
        for (int i = (x * NUM_COLS); i < ((x + 1) * NUM_COLS); i++) //column
        {
          buttons[x][arrayIndex] = i;
          arrayIndex++;
        }
      }
    }

};

#endif

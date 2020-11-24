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

    void CheckAllButtons(void)
    {
      if (buttonPad.getKeys())
      {
        for (int i = 0; i < LIST_MAX; i++)
        {
          if ( buttonPad.key[i].stateChanged )
          {
            switch (buttonPad.key[i].kstate) {
              case PRESSED:
              case HOLD:
                hid.sendButtons(buttonPad.key[i].kchar, true);
                break;
              case RELEASED:
              case IDLE:
                hid.sendButtons(buttonPad.key[i].kchar, false);
                break;
            }
          }
        }
      }
    }

  private:

    //byte buttons[NUM_ROWS][NUM_COLS] = {};

    byte buttons[NUM_ROWS][NUM_COLS] =
    {
      {0, 1, 2, 3, 4},
      {5, 6, 7, 8, 9},
      {10, 11, 12, 13, 14},
      {15, 16, 17, 18, 19},
      {20, 21, 22, 23},
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
      {0, 1, 24, 25, 0},
      {2, 3, 26, 27, 0},
      {4, 5, 28, 29, 0},
      {6, 7, 30, 31, 0},
    };

    Keypad buttonPad = Keypad( makeKeymap(buttons), ROW_PINS, COL_PINS, NUM_ROWS, NUM_COLS);

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
      for (int x = 0; x < NUM_ROWS; x++) //row
      {
        for (int i = (x * NUM_COLS); i < ((x + 1) * NUM_COLS); i++) //column
        {
          buttons[x][arrayIndex] = i;
          arrayIndex++;
        }
      }
    }

#define DIR_CCW 0x10
#define DIR_CW 0x20
#define R_START 0x0

#ifdef HALF_STEP
#define R_CCW_BEGIN 0x1
#define R_CW_BEGIN 0x2
#define R_START_M 0x3
#define R_CW_BEGIN_M 0x4
#define R_CCW_BEGIN_M 0x5
    const unsigned char rotaryTable[6][4] = {
      // R_START (00)
      {R_START_M,            R_CW_BEGIN,     R_CCW_BEGIN,  R_START},
      // R_CCW_BEGIN
      {R_START_M | DIR_CCW, R_START,        R_CCW_BEGIN,  R_START},
      // R_CW_BEGIN
      {R_START_M | DIR_CW,  R_CW_BEGIN,     R_START,      R_START},
      // R_START_M (11)
      {R_START_M,            R_CCW_BEGIN_M,  R_CW_BEGIN_M, R_START},
      // R_CW_BEGIN_M
      {R_START_M,            R_START_M,      R_CW_BEGIN_M, R_START | DIR_CW},
      // R_CCW_BEGIN_M
      {R_START_M,            R_CCW_BEGIN_M,  R_START_M,    R_START | DIR_CCW},
    };
#else
#define R_CW_FINAL 0x1
#define R_CW_BEGIN 0x2
#define R_CW_NEXT 0x3
#define R_CCW_BEGIN 0x4
#define R_CCW_FINAL 0x5
#define R_CCW_NEXT 0x6

    const unsigned char rotaryTable[7][4] = {
      // R_START
      {R_START,    R_CW_BEGIN,  R_CCW_BEGIN, R_START},
      // R_CW_FINAL
      {R_CW_NEXT,  R_START,     R_CW_FINAL,  R_START | DIR_CW},
      // R_CW_BEGIN
      {R_CW_NEXT,  R_CW_BEGIN,  R_START,     R_START},
      // R_CW_NEXT
      {R_CW_NEXT,  R_CW_BEGIN,  R_CW_FINAL,  R_START},
      // R_CCW_BEGIN
      {R_CCW_NEXT, R_START,     R_CCW_BEGIN, R_START},
      // R_CCW_FINAL
      {R_CCW_NEXT, R_CCW_FINAL, R_START,     R_START | DIR_CCW},
      // R_CCW_NEXT
      {R_CCW_NEXT, R_CCW_FINAL, R_CCW_BEGIN, R_START},
    };
#endif

};

#endif

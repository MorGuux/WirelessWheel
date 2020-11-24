#include <Keypad.h>
#include <RF24.h>
#include <RF24Network.h>

//-----NRF-----//
RF24 radio(8, 10);  //CE, CSN

RF24Network network(radio);

const uint16_t this_node = 01;       // Address of sender
const uint16_t other_node = 00;      // Address of receiver

//array of bytes for button status' (32 bits)
uint32_t btnData;

//-----BUTTON_MATRIX-----//
//Define rows, columns, button count, rotary count and pullup toggle
#define ENABLE_PULLUPS
#define NUMROTARIES 4
#define NUMBUTTONS 24
#define NUMROWS 3
#define NUMCOLS 3

//Define button matrix
byte buttons[NUMROWS][NUMCOLS] = {
  {0, 1, 2},
  {3, 4, 5},
  {6, 7, 8}
};

struct rotariesdef {
  byte pin1;
  byte pin2;
  int ccwchar;
  int cwchar;
  volatile unsigned char state;
};

rotariesdef rotaries[NUMROTARIES] {
  {0, 1, 24, 25, 0},
  {2, 3, 26, 27, 0},
  {4, 5, 28, 29, 0},
  {6, 7, 30, 31, 0},
};

#define DIR_CCW 0x10
#define DIR_CW 0x20
#define R_START 0x0

#ifdef HALF_STEP
#define R_CCW_BEGIN 0x1
#define R_CW_BEGIN 0x2
#define R_START_M 0x3
#define R_CW_BEGIN_M 0x4
#define R_CCW_BEGIN_M 0x5
const unsigned char ttable[6][4] = {
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

const unsigned char ttable[7][4] = {
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

//Define row and column pins
byte rowPins[NUMROWS] = {2, 3, 4};
byte colPins[NUMCOLS] = {5, 6, 7};

Keypad buttonPad = Keypad( makeKeymap(buttons), rowPins, colPins, NUMROWS, NUMCOLS);

void setup()
{

  rotaryInit();  //Initialise rotaries

  //Initialise NRF24 and network
  radio.begin();
  network.begin(90, this_node); //channel, node_address

}


void loop()
{

  network.update();

  CheckAllEncoders();

  CheckAllButtons();

}

void UpdateButton(int buttonIndex, bool value)
{

  bitWrite(btnData, buttonIndex, value);  //write "value" to "btnData" at position "buttonIndex"
  
  RF24NetworkHeader btnHeader(other_node, 'b');   //create header of label "b" for buttons
  network.write(btnHeader, &btnData, sizeof(btnData));
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
            UpdateButton(buttonPad.key[i].kchar, true);
            break;
          case RELEASED:
          case IDLE:
            UpdateButton(buttonPad.key[i].kchar, false);
            break;
        }
      }
    }
  }
}


void rotaryInit()
{
  for (int i = 0; i < NUMROTARIES; i++) {
    pinMode(rotaries[i].pin1, INPUT);
    pinMode(rotaries[i].pin2, INPUT);
#ifdef ENABLE_PULLUPS
    digitalWrite(rotaries[i].pin1, HIGH);
    digitalWrite(rotaries[i].pin2, HIGH);
#endif
  }
}


unsigned char rotaryProcess(int _i)
{
  unsigned char pinstate = (digitalRead(rotaries[_i].pin2) << 1) | digitalRead(rotaries[_i].pin1);
  rotaries[_i].state = ttable[rotaries[_i].state & 0xf][pinstate];
  return (rotaries[_i].state & 0x30);
}

void CheckAllEncoders(void)
{
  for (int i = 0; i < NUMROTARIES; i++)
  {
    unsigned char result = rotaryProcess(i);
    if (result == DIR_CCW)
    {
      UpdateButton(rotaries[i].ccwchar, true);
      delay(50);
      UpdateButton(rotaries[i].ccwchar, false);
      
    };
    if (result == DIR_CW)
    {
      UpdateButton(rotaries[i].cwchar, true);
      delay(50);
      UpdateButton(rotaries[i].cwchar, false);
    };
  }
}

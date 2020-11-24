#include <RF24.h>
#include <RF24Network.h>
#include <Joystick.h>

//NRF Setup
const int CE_pin = 9;   //CE Pin Assignment
const int CS_pin = 10;  //CSN Pin Assignment
const uint16_t this_node = 00;    // Address of receiver
const uint16_t other_node = 01;   // Address of sender

RF24 radio(CE_pin, CS_pin);                 // nRF24L01(+) radio

//Radio init
RF24Network network(radio);

//Button setup
const int buttonCount = 32;

Joystick_ Joystick;


void setup(void)
{

  radio.begin();
  network.begin(90, this_node);

  Joystick.begin();

}

void loop(void) {

  network.update();                   // Check the network regularly

  while ( network.available() ) {     // Is there anything ready for us?

    RF24NetworkHeader header;        // If so, grab it and print it out
    network.peek(header);

    //leaving room for expandability
    switch (header.type)
    {
      case 'b':   //button packet
        UpdateButton(header);
        break;

      default:    //Unknown packet
        break;
    }

  }
}

void UpdateButton(RF24NetworkHeader& header)
{
  uint32_t btnData;
  network.read(header, &btnData, sizeof(btnData));

  for (int i = 0; i < buttonCount; i++)  //per button
  {
    Joystick.setButton(i, bitRead(btnData, i)); //set button "i" to "btnData" bit value
  }
}

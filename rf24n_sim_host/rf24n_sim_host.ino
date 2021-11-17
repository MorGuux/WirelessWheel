#include <RF24.h>
#include <RF24Network.h>
#include "printf.h"

#include "rf24n_config.h"

RF24 radio(CE_PIN,CS_PIN);                  // nRF24L01(+) radio

//Radio init
RF24Network network(radio);

#ifdef ENABLE_LEDS
#include "RF24LEDS.h"
LED led;
#endif

#ifdef ENABLE_NEXTION
#include "RF24Nextion.h"
Nextion nextion;
#endif

#include "HIDHandler.h"
HIDHandler hid;

void setup(void)
{
  Serial.begin(115200);
  
  hid.initHID();  //Initialise HID

  #ifdef ENABLE_LEDS  //LED SETUP
  led.initLEDS();
  #endif

  #ifdef ENABLE_NEXTION   //NEXTION SETUP

  #endif

  #ifdef ENABLE_BATTERY_MONITORING    //BATTERY MONITOR SETUP

  #endif
  
  radio.begin();
  network.begin(90, PERIPHERAL_ADDRESS);
}

void loop(void)
{
  
  network.update();
  
  while ( network.available() )
  {
    
    RF24NetworkHeader header;
    network.peek(header);

    switch (header.type)
    {
      case 'i':   //Init packet
        //run init sequence to setup host with all peripherals (to-do)
        break;

      case 'l':   //LED packet
        #ifdef ENABLE_LEDS
          led.sendLEDs();
        #endif
        break;
      
      case 'n':   //Nextion packet
        #ifdef ENABLE_NEXTION
          nextion.sendNextion();
        #endif
        break;

      case 'b':   //Button packet
        #ifdef ENABLE_BUTTONS
          hid.receiveButtons(header);
        #endif
        break;

      default:    //Unknown packet

        break;
    }

  }
}

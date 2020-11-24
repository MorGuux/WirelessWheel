#include <RF24.h>
#include <RF24Network.h>


#include "rf24n_config.h"

RF24 radio(CE_PIN,CS_PIN);                  // nRF24L01(+) radio

//Radio init
RF24Network network(radio);

#ifdef ENABLE_LEDS
  #include "RF24LEDS.h"
  LED led;
#endif

#ifdef ENABLE_BUTTONS
  #ifdef BUTTON_MATRIX
    #include "RF24ButtonMatrix.h"
    ButtonMatrix matrix;
  #endif
#endif

//to-do
#ifdef ENABLE_NEXTION
  #include "RF24Nextion.h"
  Nextion nextion;
#endif

void setup(void)
{
  radio.begin();
  network.begin(90, HOST_ADDRESS); //channel, node_address

  #ifdef ENABLE_BUTTONS
    #ifdef BUTTON_MATRIX
      matrix.initMatrix();
    #endif
  #endif

  #ifdef ENABLE_NEXTION
    nextion.initNextion();
  #endif
}

void loop()
{
  network.update();   // Check the network regularly

  while ( network.available() )
  {
    
    RF24NetworkHeader header;
    network.peek(header);

    switch (header.type)
    {

      case 'l':   //LED Data
        #ifdef ENABLE_LEDS
          led.receiveLEDS(header);
        #endif
        break;

      case 'n':   //Nextion Data
        
        #ifdef ENABLE_NEXTION
          nextion.receiveNextion(header);
        #endif
        break;
    }
  }
}

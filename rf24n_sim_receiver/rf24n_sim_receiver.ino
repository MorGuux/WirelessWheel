#include "FastLED.h"
#include <RF24.h>
#include <RF24Network.h>
#include "printf.h"

//NRF Setup
const int CE_pin = 8;   //CE Pin Assignment
const int CS_pin = 10;  //CSN Pin Assignment
const uint16_t this_node = 00;    // Address of receiver
const uint16_t other_node = 01;   // Address of sender

//LED Setup
const int LED_pin = 3;
const int NUM_LEDS = 8;

RF24 radio(CE_pin,CS_pin);                  // nRF24L01(+) radio

//Radio init
RF24Network network(radio);


//LED init
CRGB leds[NUM_LEDS];


void setup(void)
{
  FastLED.addLeds<NEOPIXEL, LED_pin>(leds, NUM_LEDS);
  FastLED.clear();
  FastLED.show();
  
  radio.begin();
  network.begin(90, this_node);
}

void loop(void){
  
  network.update();                   // Check the network regularly
  
  while ( network.available() ) {     // Is there anything ready for us?
    
    RF24NetworkHeader header;        // If so, grab it and print it out
    network.peek(header);

    switch (header.type)
    {
      case 'l':   //LED packet
      UpdateLED(header);
      break;
      
      case 'n':   //Nextion packet
      UpdateNextion(header);
      break;

      default:    //Unknown packet

      break;
    }

  }
}

void UpdateLED(RF24NetworkHeader& header)
{
    byte ledData[NUM_LEDS * 3];
    network.read(header,&ledData,sizeof(ledData));

    for (int i = 0; i <= NUM_LEDS - 1; i++)  //per LED
    {
      leds[i].r = ledData[(i*3)];
      leds[i].g = ledData[(i*3)+1];
      leds[i].b = ledData[(i*3)+2];
    }

    FastLED.show();
}

void UpdateNextion(RF24NetworkHeader& header)
{

}

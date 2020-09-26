#include "FastLED.h"
#include <RF24.h>
#include <RF24Network.h>
#include "printf.h"

RF24 radio(8,10);                  // nRF24L01(+) radio attached using Getting Started board 

RF24Network network(radio);       // Network uses that radio
const uint16_t this_node = 00;    // Address of our node in Octal format ( 04,031, etc)
const uint16_t other_node = 01;   // Address of the other node in Octal format

//LED setup
#define NUM_LEDS 8
CRGB leds[NUM_LEDS];


void setup(void)
{
  FastLED.addLeds<NEOPIXEL, 3>(leds, NUM_LEDS);
  FastLED.clear();
  FastLED.show();
  
  radio.begin();
  network.begin(/*channel*/ 90, /*node address*/ this_node);
}

void loop(void){
  
  network.update();                   // Check the network regularly
  
  while ( network.available() ) {     // Is there anything ready for us?
    
    RF24NetworkHeader header;        // If so, grab it and print it out
    byte ledData[24];
    network.read(header,&ledData,sizeof(ledData));

    for (int i = 0; i <= 7; i++)  //per LED
    {
      leds[i].r = ledData[(i*3)];
      leds[i].g = ledData[(i*3)+1];
      leds[i].b = ledData[(i*3)+2];
    }

    FastLED.show();
  }
}

String getValue(String data, char separator, int index)
{
  int found = 0;
  int strIndex[] = {0, -1};
  int maxIndex = data.length()-1;

  for(int i=0; i<=maxIndex && found<=index; i++){
    if(data.charAt(i)==separator || i==maxIndex){
        found++;
        strIndex[0] = strIndex[1]+1;
        strIndex[1] = (i == maxIndex) ? i+1 : i;
    }
  }

  return found>index ? data.substring(strIndex[0], strIndex[1]) : "";
}

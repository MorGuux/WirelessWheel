/*
  RF24LEDS.h - LED manager for WirelessWheel
  Created by Morgan Gardner, November 20th, 2020.
  Released under the GPL-3.0 license.
*/

#ifndef LED_h
#define LED_h

#include "Arduino.h"
#include "FastLED.h"

class LED
{
  public:
    void initLEDS()
    {
      FastLED.addLeds<LED_TYPE, LED_PIN>(leds, NUM_LEDS);
      FastLED.clear();
      FastLED.show();   //clear all LEDs
    }
    
    void receiveLEDS(RF24NetworkHeader& header)
    {
      byte ledData[NUM_LEDS * 3];
      network.read(header, &ledData, sizeof(ledData));

      for (int i = 0; i <= NUM_LEDS - 1; i++)  //per LED
      {
        leds[i].r = ledData[(i * 3)];
        leds[i].g = ledData[(i * 3) + 1];
        leds[i].b = ledData[(i * 3) + 2];
      }

      FastLED.show();
    }

    void sendLEDs()
    {
        int ledLC = Serial.readBytesUntil('\n', ledData, sizeof(ledData));
        RF24NetworkHeader ledReader(PERIPHERAL_ADDRESS, 'l'); //"l" packet for LEDs
        network.write(ledReader, &ledData, sizeof(ledData));
    }
  private:
    CRGB leds[NUM_LEDS];
    byte ledData[NUM_LEDS * 3];
};

#endif

/*
  rf24n_config.h - Configuration file for the host/peripheral sketches.
  Created by Morgan Gardner, October 21st, 2020.
  Released under the GPL-3.0 license.
*/

#ifndef __RF24N_CONFIG__
#define __RF24N_CONFIG__

///!<----UNCOMMENT FEATURES TO ENABLE----!>///

#define ENABLE_BUTTONS
#define ENABLE_LEDS
//#define ENABLE_NEXTION
//#define ENABLE_BATTERY_MONITORING

///NRF Setup Defines
#define CE_PIN 9         //Chip Enable
#define CS_PIN 10        //Chip Select
#define HOST_ADDRESS 00
#define PERIPHERAL_ADDRESS 01

#ifdef ENABLE_BUTTONS

#define NUM_BUTTONS 24   //button count
#define NUM_ROTARIES 4   //rotary count

///BUTTON MAPPING TYPE
#define BUTTON_MATRIX    //matrixed grid of buttons
//#define BUTTON_LINEAR

#ifdef BUTTON_MATRIX

#define ENABLE_PULLUPS   //input pullups on pins
#define NUM_ROWS 5       //row count
#define NUM_COLS 5       //column count

const byte ROW_PINS[NUM_ROWS] = {1,2,3,4,5};  //pin assignments for rows and columns
const byte COL_PINS[NUM_COLS] = {6,7,8,9,10};

#endif



#endif


#ifdef ENABLE_LEDS

#define LED_TYPE NEOPIXEL		//LED Type
#define LED_PIN 3		        //LED Pin
#define NUM_LEDS 8		      //LED Count

#endif


#ifdef ENABLE_NEXTION

#endif

//to-do
#ifdef ENABLE_BATTERY_MONITORING

#endif

#endif

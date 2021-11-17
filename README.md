# WirelessWheel

[![Verify Arduino files](https://github.com/MorGuux/WirelessWheel/actions/workflows/main.yml/badge.svg)](https://github.com/MorGuux/WirelessWheel/actions/workflows/main.yml)

## NIGHTLY BUILD, CAN BE BROKEN, DO NOT COMPILE AND USE ON AN ARDUINO

NRF24 powered wireless steering wheel, complete with buttons, leds, nextions and SimHub support.

## Hardware Supported

- ATMEGA32U4-based Arduino (Pro Micro, Leonardo, Lilypad USB etc.)
- NRF24L01 RF Module
- Button Matrix
- Rotary Encoders
- WS2812 LEDs
- Nextion displays
- Battery monitoring

## Dependencies

- [FastLED](https://github.com/FastLED/FastLED)
- [BatterySense](https://github.com/rlogiacco/BatterySense)
- [RF24](https://github.com/nRF24/RF24)
- [RF24Network](https://github.com/nRF24/RF24Network)
- [ArduinoJoystickLibrary](https://github.com/MHeironimus/ArduinoJoystickLibrary)
- [Keypad](https://playground.arduino.cc/Code/Keypad/)

## Intended Use

#### Sender

- HID-compatible Arduino (Pro Micro, Leonardo, Lilypad USB, anything ATMEGA32U4)
- NRF24L01 module

#### Receiver

- Any Arduino
- NRF24L01 module
- Button Matrix
- Nextion screen
- WS2812 LEDs

###### Powering can be done via your own method

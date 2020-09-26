#include <RF24.h>
#include <RF24Network.h>

RF24 radio(9, 10);  //CE, CSN

RF24Network network(radio);

const uint16_t this_node = 01;       // Address of sender
const uint16_t other_node = 00;      // Address of receiver

byte ledData[24];
byte nexData[24];

void setup(void)
{
  Serial.begin(115200);

  radio.begin();
  network.begin(90, this_node); //channel, node_address
}

void loop() {

  network.update();                          // Check the network regularly

  while (Serial.available() > 0) {

    switch (Serial.read()) {

      case 'l':   //LED Data
        int ledLC = Serial.readBytesUntil('\n', ledData, sizeof(ledData));
        //if (ledLC == sizeof(ledData))
        RF24NetworkHeader ledReader(other_node, 'l');
        network.write(ledReader, &ledData, sizeof(ledData));
        break;

      case 'n':   //Nextion Data
        int nextionLC = Serial.readBytesUntil('\n', nexData, sizeof(nexData));

        RF24NetworkHeader nexHeader(other_node, 'l');
        network.write(nexHeader, &nexData, sizeof(nexData));
        break;
    }
  }
}

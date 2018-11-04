 /*
* Getting Started example sketch for nRF24L01+ radios
* This is a very basic example of how to send data from one node to another
* Updated: Dec 2014 by TMRh20
*/

#include <Wire.h>

#include <RF24_config.h>
#include <printf.h>
#include <nRF24L01.h>
#include <SPI.h>
#include <SoftwareSerial.h>
#include "RF24.h"
#include "../shared/joydata.h"

RF24 radio(9, 10);
byte addresses[][6] = { "1Node", "2Node" };

void setup() 
{
    Serial.begin(115200);
    Serial.println(F("SENDER"));

    radio.begin();
    radio.setRetries(0, 15);
    radio.setPALevel(RF24_PA_HIGH);

    radio.openWritingPipe(addresses[0]);
    radio.stopListening();
}


void displayBufferOnLcd(char* buffer, int maxLex)
{
    Serial.print(F("Buffer: "));
    Serial.println(buffer);
}

char buffer[128];

void loop()
{
    JoyData joyData;
    joyData.X = analogRead(A0);
    joyData.Y = analogRead(A1);
    joyData.Button = analogRead(A2);
    joyData.Id = 0;

    printJoyData(joyData, Serial);
  
    Serial.print(F("..."));
    if (!radio.write(&joyData, sizeof(joyData)))
    {
        Serial.println(F("NOK"));
    }
    else
    {
        Serial.println(F("OK"));
    }
}

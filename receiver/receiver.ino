/*
* Basic example sourced from RF library example
*/

#include <CStringBuilder.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#include <SSD1306Ascii.h>
#include <SSD1306AsciiWire.h>

#include "joydata.h"

#define CEPIN 9
#define CSPIN 10

RF24 radio(CEPIN, CSPIN);
byte addresses[][6] = { "1Node" };

#define OLED_I2C_ADDRESS 0x3C
SSD1306AsciiWire display;



void setup()
{
    Serial.begin(115200);   
    Serial.println(F("Receiver"));
	

	display.begin(&Adafruit128x32, OLED_I2C_ADDRESS);
	display.set400kHz();
	display.setFont(Adafruit5x7);
	display.clear();
	display.setCursor(0, 0);
	display.print(F("Receiver"));

    radio.begin();
    radio.setPALevel(RF24_PA_LOW);
    radio.setAutoAck(1);
    radio.setRetries(0, 15);
    radio.openReadingPipe(0, addresses[0]);
    radio.startListening();
}

void loop()
{      
    while (radio.available())
    {      
      JoyData joyData;
      radio.read(&joyData, sizeof(joyData));    
      printlnJoyData(joyData, Serial);
      char buff[128];
      CStringBuilder sb(buff, 128);
      printlnJoyData(joyData, sb);

	  display.home();
	  display.clearToEOL();
	  display.print(buff);
    }
}

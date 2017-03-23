#include "Arduino.h"
#include "SDRfid.h"

SDRfid::SDRfid()
{
    card = 0;
    rfcmdsent = false;
    pinset = false;
    readcmd = false;
}

void SDRfid::setPins(int sensor, HardwareSerial* serialid)
{   
    key = sensor;
    pinMode(key,INPUT);      //Virtual card pin
    digitalWrite(key, HIGH);
    
    if (!SD.begin(SD_CS)) {
      return;
    }

    if(key == RFID_VITURAL_1){
      fileName = CARD_FILE_1;
    }
    else{
      fileName = CARD_FILE_2;
    }
    
    pinset=true;
}


void SDRfid::update()
{
    if (!pinset)
        return;
    if (!readcmd)
        return;

	if (digitalRead(key))            // Hold Virtual Card 
	{
    byte buf = 0;
    cardFile = SD.open(fileName);   // Open card file
    if(cardFile){
        int i;
        
        //Read card
        for (i = 0; cardFile.available() && i < 16; i++) {
          byte c = cardFile.read();
          if(c > 64 && c < 71)
            c -= 55;
          else if(c > 96 && c < 103)
            c -= 87;
          else if(c > 47 && c < 58)
            c -= 48;
          else
            break;
          if(i%2 == 0)
            buf = c<<4;
          else{
            buf |= c;
            uid[i/2] = buf;
          }
        }
        
        if(i == 16)
          card = 0;
          
        readcmd = false;//reading finished (no card found)
        rfcmdsent = false;
        cardFile.close();
      
    }
    else{
      readcmd = false;//reading finished (no card found)
      rfcmdsent = false;
    }
	}
	else
	{
		readcmd = false;//reading finished (card found)
		card = 1;

	}
}

byte SDRfid::isCardPresent()
{
    return card;
}

void SDRfid::read()
{
    readcmd=true;
}

void SDRfid::getUID(byte* uida)
{
    memcpy(uida,uid,8);
}

bool SDRfid::isVirtual()
{
    return true;
}


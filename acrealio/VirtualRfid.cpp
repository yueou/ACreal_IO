#include "Arduino.h"
#include "VirtualRfid.h"

VirtualRfid::VirtualRfid()
{
    card = 0;
    rfcmdsent = false;
    pinset = false;
    readcmd = false;
}

void VirtualRfid::setPins(int sensor, HardwareSerial* serialid)
{   
    key = sensor;
    pinMode(key,INPUT);      //Virtual card pin
    digitalWrite(key, HIGH);

    //Read card uid
    char* cUID;
    byte buf;
    
    if(key == RFID_VITURAL_1)
      cUID= CARD_1;
    else
      cUID= CARD_2;

    for (int i = 0;  i < 16; i++) {
      byte c = cUID[i];
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
    
    pinset=true;
}

void VirtualRfid::update()
{
    if (!pinset)
        return;
    if (!readcmd)
        return;

	if (digitalRead(key))            // Hold Virtual Card 
	{
		card = 0;
		rfcmdsent = false;
		readcmd = false;//reading finished (no card found)
	}
	else
	{
		readcmd = false;//reading finished (card found)
		card = 1;

	}
}

byte VirtualRfid::isCardPresent()
{
    return card;
}

void VirtualRfid::read()
{
    readcmd=true;
}

void VirtualRfid::getUID(byte* uida)
{
    memcpy(uida,uid,8);
}

bool VirtualRfid::isVirtual()
{
    return true;
}


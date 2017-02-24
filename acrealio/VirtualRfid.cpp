#include "Arduino.h"
#include "VirtualRfid.h"

VirtualRfid::VirtualRfid()
{
    card = 0;
    rfcmdsent = false;
    pinset = false;
    readcmd = false;
	
	//Read card uid
	uid[0]= CARD_1_A;		
	uid[1]= CARD_1_B;
	uid[2]= CARD_1_C;
	uid[3]= CARD_1_D;
	uid[4]= CARD_1_E;
	uid[5]= CARD_1_F;
	uid[6]= CARD_1_G;
	uid[7]= CARD_1_H;
}

void VirtualRfid::setPins(int sensor, HardwareSerial* serialid)
{   
    rfSENSOR = sensor;
    rfSerial = serialid;

    pinMode(rfSENSOR,INPUT);                            // Rfid sensor
    rfSerial->begin(RFID_BAUD);
    
    pinset=true;
}

void VirtualRfid::setKey(byte key){
	
    pinMode(key,INPUT);			//Virtual card pin
    digitalWrite(key, HIGH);
	this->key = key;
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


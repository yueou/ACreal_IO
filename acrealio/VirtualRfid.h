#ifndef VIRTUAL_RFID
#define VIRTUAL_RFID

#include "Arduino.h"
#include "RfidModule.h"

class VirtualRfid : public RfidModule
{
public:
    VirtualRfid();
    void setPins(int sensor, HardwareSerial* serialid);
    void read();
    void update();
    byte isCardPresent();
    void getUID(byte* uid);
    bool isVirtual();
    void setKey(byte key);

private:
    byte card;               // card presence
  	int key;
    byte uid[8];
    boolean rfcmdsent;

    boolean pinset;
    boolean readcmd; // read request from host flag

};

#endif



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
	byte key;
    byte uid[8];
    boolean rfcmdsent;
    unsigned long timesent;
    short rfSENSOR;             // rfid OUT pin
    HardwareSerial* rfSerial;    // rfid Serial

    boolean pinset;
    boolean readcmd; // read request from host flag

};

#endif



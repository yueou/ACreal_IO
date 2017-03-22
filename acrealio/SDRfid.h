#ifndef SD_RFID
#define SD_RFID

#include "Arduino.h"
#include "RfidModule.h"
#include "SD.h"
#include "SPI.h"

class SDRfid : public RfidModule
{
public:
    SDRfid();
    void setPins(int sensor, HardwareSerial* serialid);
    void read();
    void update();
    byte isCardPresent();
    void getUID(byte* uid);
    bool isVirtual();

private:
    byte card;               // card presence
    byte uid[8];
    int key;
    char* fileName;
    File cardFile;
    boolean rfcmdsent;

    boolean pinset;
    boolean readcmd; // read request from host flag

};

#endif



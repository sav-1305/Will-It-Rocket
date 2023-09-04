#ifndef nrfconfig_h
#define nrfconfig_h

#include <RF24.h>
#include <SPI.h>
#include <nRF24L01.h>

class NRF
{
    public:
        NRF(int CE, int CSN, int state);
        void write(char buffer[]);
        void read();
    private:
        const byte address[6] = {00000};  
        RF24 radio;
};


#endif
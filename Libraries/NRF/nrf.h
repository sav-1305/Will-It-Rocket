#ifndef NRF_H
#define NRF_H

#include <RF24.h>
#include <Arduino.h>

#define CE_PIN 9
#define CSN_PIN 10

class NRF {
    public:
    NRF();
    void init();
    void write(char buffer[32]);
    char* read();
    
    private:
    const byte address[6] = "00000";
    RF24 radio;
};

#endif
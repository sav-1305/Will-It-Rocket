#ifndef NrF_h
#define NrF_h

#include "RF24.h"
class NRF{
    public:
    NRF(int a,int b);
    byte address[2][6]={"00000","00001"};   
    void initialize() ;
    void Write(char p[],int size);
    void ValRead();
    void Read();
    private:
    RF24 radio;
};
#endif
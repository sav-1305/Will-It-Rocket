#include "NrF.h"
#include <FSM.h>
#include <Struct.h>
//look into this
NRF::NRF(int a,int b){
    radio=RF24(a,b);
    } 

void NRF::initialize(){
    radio.begin();
    radio.setPALevel(RF24_PA_LOW);
    radio.openWritingPipe(address[1]);
    radio.openReadingPipe(1,address[0]);
}
 
void NRF::Write(char ab[],int size){
    radio.stopListening();
   // Serial.println("inside write");
    radio.write(ab, size);
}
char text2[32]="";

void NRF::Read(){
    radio.startListening();
   // Serial.println("inside Read");
    if(radio.available()){
    radio.read(text2, sizeof(text2));
    Serial.println(text2);
    radio.stopListening();
    radio.flush_rx();
    }
}
struct data Data;
void NRF::ValRead(){
    radio.startListening();
    if(radio.available()){
    radio.read(&Data, sizeof(Data));
    }
} 
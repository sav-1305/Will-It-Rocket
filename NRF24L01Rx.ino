#include <RF24.h>

RF24 radio(7,8);

//uint8_t address[][6] = { "01010" , "10101" , "00000" } ;

// int radioNum = 0 ;
//bool role = false ;

void setup(){
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(1,01010);
  radio.setPALevel(RF24_PA_LOW);
  radio.startListening();
}

void loop(){
  if(radio.available()){
   /* char mess[32] = "" ;
    radio.read(&mess,sizeof(mess));
    Serial.println(mess);
  }*/
 struct data{
    float alti;
    float pressu;
    float vel;
  }d;
  radio.read(&d,sizeof(d));
  Serial.println(d.alti);
  Serial.println(d.pressu);
  Serial.println(d.vel);
  Serial.println();
  
  }
}

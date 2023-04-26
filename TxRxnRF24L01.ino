#include <RF24.h>

RF24 radio(7,8);

uint8_t address[][6] = { "00000" , "10101" , "01010" } ;

bool role = false ;
int Tx ;

void setup(){
  Serial.begin(9600);
  Serial.println("Default is receiving mode, if you want to transmit press 1: ");
while(Serial.available()){}
  role = Serial.parseInt();
  if(!role){
    Serial.println("Enter 0 or 1 for Tx selection: ");
    while(Serial.available()==0){}
    Tx = address[Serial.parseInt()];
  }
  radio.begin();

  if(!role){
  radio.openReadingPipe(0,Tx);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
  }
  else{
  radio.openWritingPipe(address[2]);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
  }
}

void loop(){
  if(role){
  const char text[32] = "MEOWTHRUSTMITMEOW";
  radio.write(&text, sizeof(text));
  }
 else{
    if (radio.available()) {
    char text[32] = "";
    radio.read(&text, sizeof(text));
    Serial.println(text);
  }
 }
}

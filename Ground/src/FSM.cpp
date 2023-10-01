#include <FSM.h>
#include <Declar.h>
//#include <Arduino.h>
FSM::FSM(){

}
int FSM::initializee(){
   // Serial.println("switch\n");
 switch(Curr){
    case INITIAL:
    key();
    break;
    case KEYON:
    arm();
    break;
    case ARMON:
    launch();
    break;
    default:
    break;
    }
}
void FSM::key(){
    if(digitalRead(KEY_SW)==1){
    Curr=KEYON;
    Serial.println("in key state\n");
    digitalWrite(KEY_LED,1);
    char keysta[]="KEY";
    nrf.Write(keysta,sizeof(keysta));
    delay(1000);
    nrf.Read();
    delay(1000);
    }
}
void FSM::arm(){
    if(digitalRead(ARM_SW)==1){
    Curr=ARMON;
    Serial.println("in arm state\n");
    digitalWrite(ARM_LED,1);
    char armsta[]="ARM0N";
    nrf.Write(armsta,sizeof(armsta));
    delay(1000);
    nrf.Read();
    delay(1000);
    }
}
void FSM::launch(){
    if(digitalRead(LAUNCH_SW)==1){
    Curr=LAUNCHON;
    Serial.println("in launch state\n");
    digitalWrite(LAUNCH_LED,1);
    char launchsta[]="LAUNCH0N";
    nrf.Write(launchsta,sizeof(launchsta));
    delay(1000);
    nrf.Read();
    delay(1000); 
    }
    if(digitalRead(ARM_SW)==0){
    Curr=KEYON;
    Serial.println("in key state\n");
    digitalWrite(ARM_LED,0);
    char keysta[]="KEY";
    nrf.Write(keysta,sizeof(keysta));
    delay(1000);
    nrf.Read();
    delay(1000);
    }
}

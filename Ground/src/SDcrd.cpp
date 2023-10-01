#include <SDcrd.h>
void SDsetup::initialize(){
    SD.begin();
}
void SDsetup::WritetoFile(){
    myFile = SD.open("file.txt",FILE_WRITE);
    if(myFile){
        Serial.println("Writing to file");
        myFile.println("..text..");
        myFile.close();
    }
}
void SDsetup::ReadFile(){
     myFile = SD.open("file.txt",FILE_WRITE);
     if(myFile){
        Serial.println("Reading file");
        while(myFile.available()){
            Serial.write(myFile.read());
        }
        myFile.close();
    }
}
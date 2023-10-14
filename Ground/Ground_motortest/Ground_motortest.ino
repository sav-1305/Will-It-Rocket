/*Backup program on arduino IDE for motor test on ground side.*/

#include <SPI.h>
#include <RF24.h>
#include <nRF24L01.h>
#include <SD.h>

RF24 radio(9, 10);
File myFile;

// LED pins
int KeyLED = 38;
int ArmLED = 37;
int LaunchLED = 35;
int KEY_PIN = 29;
int ARM_PIN = 28;
int LAUNCH_PIN = 33;

// States
typedef enum {
  INITIAL,
  KEY,
  ARM,
  LAUNCH,
  FAILURE,
} States;

States Current_state = INITIAL;

// Structure
struct SensorData {
  float load;
  float strain;
};

void setup() {
  pinMode(KeyLED, OUTPUT);
  pinMode(ArmLED, OUTPUT);
  pinMode(LaunchLED, OUTPUT);
  pinMode(KEY, INPUT_PULLDOWN);
  pinMode(ARM, INPUT_PULLDOWN);
  pinMode(LAUNCH, INPUT_PULLDOWN);

  // NRF
  radio.begin();
  byte address[][6] = { {0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 1} };//  byte address[][6]={00000,00001}; 
  radio.setPALevel(RF24_PA_LOW);
  radio.openWritingPipe(address[1]);
  radio.openReadingPipe(1, address[0]);

  // SD card
  if (!SD.begin(BUILTIN_SDCARD)) {
    Serial.println("SD card not initialized");
  } else {
    SD.remove("myfile.txt");
    myFile = SD.open("myfile.txt", FILE_WRITE);
    Serial.println("INITIALIZED SD");
  }
}

void loop() {
  SensorData Data;
  radio.stopListening();
  char message[32] = "";
  switch (Current_state) {
    case INITIAL:
      if (digitalRead(KEY_PIN) == HIGH) {
        digitalWrite(KeyLED,HIGH);
        Current_state = KEY;
        strcpy(message, "KEY");
        Serial.println("Current state = KEY");
        radio.write(&message, sizeof(message));
      }
      break;

    case KEY:
      if (digitalRead(ARM_PIN) == HIGH) {
        digitalWrite(ArmLED,HIGH);
        Current_state = ARM;
        strcpy(message, "ARM");
        Serial.println("Current state = ARM");
        radio.write(&message, sizeof(message));
      }
      break;

    case ARM:
      if (digitalRead(LAUNCH_PIN) == HIGH) {
        digitalWrite(LaunchLED,HIGH);
        Current_state = LAUNCH;
        strcpy(message, "LAUNCH");
        Serial.println("Current state = LAUNCH");
        radio.write(&message, sizeof(message));
      }

      if (digitalRead(ARM_PIN) == LOW) {
        digitalWrite(ArmLED,LOW);
        Current_state = KEY;
        strcpy(message, "KEY");
        Serial.println("Current state = KEY");
        radio.write(&message, sizeof(message));
      }
      break;

    case LAUNCH:
        radio.startListening();
        if (radio.available()) {
          radio.read(&Data, sizeof(Data));
          Serial.print("->load:");
          Serial.print(Data.load);
          Serial.print("->strain:");
          Serial.print(Data.strain);
          myFile.println(Data.load);
          myFile.print(" ");
          myFile.print(Data.strain);
        } else {
          Serial.println("radio not available");
        }      
      break;
  }
}

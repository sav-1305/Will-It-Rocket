/*
Final ground station code for motor test 2023.
Componenets-
SD card for datalogging.
Teensy 4.1 microcontroller.
Xbee for communication */

//pin definitions
const int KeyLED = 38;
const int ArmLED = 37;
const int LaunchLED = 35;
const int KEY_PIN = 29;
const int ARM_PIN = 28;
const int LAUNCH_PIN = 33;

// States present in the FSM.
typedef enum {
  KEY,
  ARM,
  LAUNCH,
  FAILURE,
} States;

States Current_state = KEY;
char message[7];
byte* mess = (byte*)&message;

void setup(){
  pinMode(KeyLED, OUTPUT);
  pinMode(ArmLED, OUTPUT);
  pinMode(LaunchLED, OUTPUT);
  pinMode(KEY_PIN, INPUT_PULLDOWN);
  pinMode(ARM_PIN, INPUT_PULLDOWN);
  pinMode(LAUNCH_PIN, INPUT_PULLDOWN);

  Serial.begin(9600);
  //Xbee serial communication using Seial1.
  Serial1.begin(9600); 

}

void loop(){
  switch (Current_state) {
    case KEY:
      digitalWrite(KeyLED,HIGH);  //initial state key hence it will remain HIGH
      if (digitalRead(ARM_PIN) == HIGH) {
        digitalWrite(ArmLED,HIGH);
        Current_state = ARM;
        strcpy(message, "ARMON");
        Serial.println("Current state = ARM");
        Serial1.write(mess, sizeof(message));// if not working try message
        delay(1000);
      }
      break;

    case ARM:
      if (digitalRead(LAUNCH_PIN) == HIGH) {
        digitalWrite(LaunchLED,HIGH);
        Current_state = LAUNCH;
        strcpy(message, "LAUNCH");
        Serial.println("Current state = LAUNCH");
        Serial1.write(mess, sizeof(message));
      }

      if (digitalRead(ARM_PIN) == LOW) {
        digitalWrite(ArmLED,LOW);
        Current_state = KEY;
        strcpy(message, "ARMOFF");
        Serial.println("Current state = KEY");
        Serial1.write(mess, sizeof(message));
      }
      delay(1000);
      break;

    case LAUNCH:   
      break;

    default:
      break;
  }
}



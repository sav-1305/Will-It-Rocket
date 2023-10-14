/* MOTOR TEST BACKUP - ARDUINO IDE
    program written as backup for motor-test project - MOTOR SIDE - in arduino IDE due to
    complexities in PlatformIO.
    Designed for Teensy 4.1
    Peripherals - 
                  nRF24L01
                  BF350-Strain Gauge
                  Load Cell
    
    Written for ThrustMIT Avionics 23-24.
*/

/* INCLUDES */

#include <SD.h>
#include <SPI.h>
#include <RF24.h>
#include <nRF24L01.h>
#include <string.h>

/* MACROS */

#define D1      5
#define D2      6
#define CE_PIN  9
#define CSN_PIN 10
#define ANALOG  A5
#define loadSerial Serial5

#define KEY     38
#define ARM     37
#define LAUNCH  35
#define COMMS   36
#define LOAD    34

/* VARIABLES */

const byte address[2][6] = {"00000", "00001"};  //Addresses for nRFs
char receive[32];                               //array buffers for transmission data
char transmit[32];
RF24 radio(CE_PIN, CSN_PIN);
bool isLaunched = false;

//static int logCount = 0;                        //Only for testing purposes
File logFile;

int wheatStone = 0;
float voltage = 0, strain = 0;                  //Strain is final straingauge output

/* MACROS FOR STRAIN CALCULATION:
      Gauge Factor = 2-2.0
      Excitation Voltage = 5V
      Reference max voltage = 3.5V

      analog - digital conversion => voltage = wheatStone (analog reading) * 3.5 / 1023;
      strain = voltage * 0.4
*/

struct SensorData {
  float load;
  float strain;
} Data;

float loadBuffer = 0;
float loadCellOutput = 0;
float strainGaugeOutput = 0;

enum STATE {
  SAFE,
  ARMED,
  LAUNCHED,
  HALTED
};

STATE currentState = SAFE;

/* FUNCTIONS */

float readLoadCell() {
  if (loadSerial.available()) {
    loadBuffer = loadSerial.read();
    Data.load = loadBuffer;
    return loadBuffer;
  }
  return -1;
}

float calculate() {
  wheatStone = analogRead(ANALOG);
  voltage = 3.5 * wheatStone / 1023;
  strain = 0.4 * voltage;
  Data.strain = strain;
  return strain;
}

void logData(float load, float strain) {

  logFile = SD.open("motorTest.csv", FILE_WRITE);

  if (logFile) {
    logFile.print(load);
    logFile.print(",");
    logFile.println(strain);
    logFile.close();
    Serial.println("DATA LOGGED SUCCESSFULLY. ");
  }
}

void checkInput(char buffer[]) {
  if ((strcmp(buffer, "ARM_ON") == 0) && (currentState == SAFE)) {
    currentState = ARMED;
    Serial.println("Current state: ARMED");
    return;
  }
  else if ((strcmp(buffer, "LAUNCH") == 0) && (currentState == ARMED)) {
    currentState = LAUNCHED;
    Serial.println("Current state: LAUNCHED");
    return;
  }
  else if ((strcmp(buffer, "ARM_OFF") == 0) && (currentState == ARMED)) {
    currentState = SAFE;
    Serial.println("Current state: SAFE");
    return;
  }
  else if ((strcmp(buffer, "FAILURE") == 0) && (currentState == ARMED)) {
    currentState = HALTED;
    Serial.println("Current state: HALTED");
    return;
  }
  else if ((strcmp(buffer, "FAILURE") == 0) && (currentState == SAFE)) {
    currentState = HALTED;
    Serial.println("Current state: HALTED");
    return;
  }
  else if ((strcmp(buffer, "FAILURE") == 0) && (currentState == LAUNCHED)) {
    currentState = HALTED;
    Serial.println("Current state: HALTED");
    return;
  }
  else if ((strcmp(buffer, "SAFE") == 0) && (currentState == HALTED)) {
    currentState = SAFE;
    Serial.println("Current state: SAFE");
    return;
  }
  else {
    Serial.println("Invalid Input Provided to Motor System. ");
  }
}

STATE getCurrentState() {
  return currentState;
}

void DataTelemetry(SensorData Data) {

  radio.write(&Data, sizeof(SensorData));

}

void performOperation(STATE s) {
  switch(s) {
    case SAFE:

      digitalWrite(KEY, HIGH);
      delay(1000);
      digitalWrite(KEY, LOW);
      delay(1000);
      break;

    case ARMED:

      digitalWrite(KEY, HIGH);

      strainGaugeOutput = calculate();
      loadCellOutput = readLoadCell();
      logData(loadCellOutput, strainGaugeOutput);

      digitalWrite(ARM, HIGH);
      delay(1000);
      digitalWrite(ARM, LOW);
      delay(1000);
      break;

    case LAUNCHED:

      if (!isLaunched) {
        radio.openWritingPipe(address[1]);
        radio.stopListening();
        isLaunched = true;
      }

      strainGaugeOutput = calculate();
      loadCellOutput = readLoadCell();
      logData(loadCellOutput, strainGaugeOutput);

      DataTelemetry(Data);

      digitalWrite(KEY, HIGH);
      digitalWrite(ARM, HIGH);

      digitalWrite(LAUNCH, HIGH);
      delay(1000);
      digitalWrite(LAUNCH, LOW);
      delay(1000);
      break;

    case HALTED:

      digitalWrite(LAUNCH, HIGH);
      delay(200);
      digitalWrite(LAUNCH, LOW);
      delay(200);
      logFile.close();
      break;

    default:
      break;
  }
}

void setup() {

  Serial.begin(9600);
  Serial.println("1. SERIAL COMMS : INITIALISED");

  pinMode(KEY, OUTPUT);
  pinMode(ARM, OUTPUT);
  pinMode(LAUNCH, OUTPUT);
  pinMode(COMMS, OUTPUT);
  pinMode(LOAD, OUTPUT);
  Serial.println("    NOTE: LEDs configured. ");

  
  if (!radio.begin()) {
    Serial.println("2. NRF COMMS: FAILED");
  }
  else {
    Serial.println("2. NRF COMMS: INITIALISED");
  }
  radio.openReadingPipe(1, address[0]);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();


  if (!SD.begin(BUILTIN_SDCARD)) {
    Serial.println("3. SD CARD: FAILED");
  } 
  else {
    Serial.println("3. SD CARD: INITIALISED");
  }

  if (SD.exists("motorTest.csv")) {
    SD.remove("motorTest.csv");
    Serial.println("  3(a) File refreshed. ");
  }

  logFile = SD.open("motorTest.csv", FILE_WRITE);
  if (logFile) {
    logFile.println("Load,Strain");
    Serial.println("  3(b) File created. ");
    logFile.close();
  }
  else {
    Serial.println("  3(b) unable to setup file. LOGGING FAILED. ");
    logFile.close();
  }

}

void loop() {

  if (radio.available()) {
    radio.read(receive, sizeof(receive));
    Serial.print("Received Data: ");
    Serial.println(receive);

    checkInput(receive);
  }

  performOperation(getCurrentState());

}

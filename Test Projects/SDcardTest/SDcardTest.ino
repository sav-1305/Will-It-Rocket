#include <SD.h>

File logFile;
static int logCount = 0;

void setup() {
  Serial.begin(9600);
  Serial.println("Serial Comm. Initialised. \n");

  if (!SD.begin(BUILTIN_SDCARD)) {
    Serial.println("SD card initialisation failed. \n");
    return;
  }
  
  logFile = SD.open("log.txt", FILE_WRITE);
  if (!logFile) {
    Serial.println("Couldn't open log file");
  } 
  else {
    Serial.println("Logging to SD card...");
  }
  
}

void loop() {
  if (logCount < 10) {
    logFile.println("SD CARD TEST.");
    logCount++;
  }
  else {
    logFile.close();
    Serial.println("Logging Complete. File Closed. ");
  }
}

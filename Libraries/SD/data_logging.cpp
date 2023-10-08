#include <SDlogger.h>

LOGGING::LOGGING() {

}

void LOGGING::init() {

    Serial.println("\nSD CARD DEBUGGING INFO: ");

    if (!SD.begin(BUILTIN_SDCARD)) {
        Serial.println("SD card failed to initialise. ");
    }
    else {
        Serial.println("SD card initialised. ");
    }

    if (SD.exists("straintest.txt")) {
        SD.remove("straintest.txt");
        Serial.println("File refreshed. ");
    }
    else {
        Serial.println("New file created. ");
    }

    logFile = SD.open("straintest.txt", FILE_WRITE);
    if (!logFile) {
        Serial.println("Couldn't open logFile. ");
    }
    else {
        Serial.println("Logging to SD card...");
    }

}

void LOGGING::log(float buffer) {

    logFile.print("Strain reading: ");
    logFile.println(buffer);

}

void LOGGING::close() {
    Serial.println("Closing File. ");
    logFile.close();
}
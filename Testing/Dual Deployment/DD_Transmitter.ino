#include <SPI.h>
#include <RF24.h>
#include <nRF24L01.h>

RF24 radio(7, 8);  // CE, CSN pins
const byte address[] = "00000";
void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openWritingPipe(address);  // Set the receiving address
  radio.setPALevel(RF24_PA_HIGH);       // Set power level (low, medium, high)
  radio.stopListening();
}

void loop() {
  if (Serial.available()) {
    String inputString = Serial.readStringUntil('\n'); // Read input string from Serial Monitor
    // Send the input string over NRF24
    char message[inputString.length() + 1];
    inputString.toCharArray(message, sizeof(message));
    radio.write(&message, sizeof(message));
    
    Serial.println(message);
  }
}

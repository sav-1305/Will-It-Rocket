#include <nrf.h>

NRF::NRF() {
    RF24 radio(CE_PIN, CSN_PIN);
}

void NRF::init() {
    if (!radio.begin()) {
        Serial.println("NRF failed to initialise. ");
    }
    else {
        Serial.println("NRF initialised. ");
    }

    radio.openWritingPipe(address);
    radio.setPALevel(RF24_PA_LOW);

}

void NRF::write(char buffer[32]) {
    radio.stopListening();
    if (radio.write(buffer, sizeof(buffer))) {
        Serial.println("Transmission Successful. ");        
    }
}

char* NRF::read() {
    char temp[32];
    radio.read(temp, sizeof(temp));
    
}
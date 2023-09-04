#include <nrfconfig.h>

NRF::NRF(int CE, int CSN, int state)
    : radio(CE, CSN)
{
    if (!radio.begin())
    {
        Serial.println(F("radio hardware not responding!"));
        while (1) {}
    }
    switch (state)
    {
    case 1:
        radio.openWritingPipe(address);
        radio.setPALevel(RF24_PA_LOW);
        radio.stopListening();
        break;
    case 2:
        radio.openReadingPipe(1, address);
        radio.setPALevel(RF24_PA_LOW);
        radio.startListening();
    default:
        Serial.println("Transmitter/Receiver settings not configured!");
    }

}

void NRF::write(char buffer[])
{
    radio.write(&buffer, sizeof(buffer));
    delay(100);
}

void NRF::read()
{
    if (radio.available())
    {
        char text[32] = "";
        radio.read(&text, sizeof(text));
        Serial.println(text);
    }
}
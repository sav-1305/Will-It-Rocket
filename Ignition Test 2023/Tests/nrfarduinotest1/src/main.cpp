#include <Arduino.h>
#include <nrfconfig.h>
#include <sdlog.h>

#define CE_PIN  9
#define CSN_PIN 10
#define NRFSTATE   1

NRF nrf(CE_PIN, CSN_PIN, NRFSTATE);
SDLog sdlog;


char buffer[] = "buffer";
String buffer = "";


void setup() 
{
  Serial.begin(9600);

}

void loop()
{
  switch (NRFSTATE)
  {
  case 1:
    nrf.write(buffer);
    break;
  case 0:
    nrf.read();
    break;
  default:
    Serial.println("No operations conducted!");
  } 
}

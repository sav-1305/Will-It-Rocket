#include <SPI.h>
#include <RF24.h>
#include <nRF24L01.h>

#define CE_PIN  7
#define CSN_PIN 8
#define D1      3
#define D2      4

RF24 radio(CE_PIN, CSN_PIN);
const byte address[6] = "00000";

void setup()
{
  Serial.begin(9600);
  Serial.println("Program Starting.");

  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);

  radio.begin();
  Serial.println("nRF initialised.");

  radio.openReadingPipe(1, address);
  radio.setPALevel(RF24_PA_LOW);

  Serial.println("Reading Pipe established.");
  radio.startListening();

}

void loop()
{
  if (radio.available())
  {
    char text[32] = "";
    radio.read(text, sizeof(text));
    Serial.println(text);

    if (strcmp(text, "DROGUE") == 0)
    {
      digitalWrite(D1, HIGH);
    }
    else if (strcmp(text, "MAIN") == 0)
    {
      digitalWrite(D2, HIGH);
    }
    else if(strcmp(text, "OFF") == 0)
    {
      digitalWrite(D1, LOW);
      digitalWrite(D2, LOW);
    }
    else
    {
      Serial.println("Invalid Input Provided to Motor System.");
    }
    
  }
}

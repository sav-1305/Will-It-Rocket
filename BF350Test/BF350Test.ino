/*  Program to test the BF350 Strain Gauge module.
      The BF350 consists of a linear strain gauge which is connected to a quarter wheatstone bridge
      of resistance 350ohm, with excitation voltage E = 5V. The Gauge factor of the strain gauge is
      2-2.20. The output received is of the form dV, which is received in analog format & converted
      to strain readings.
    Test Program for ThrustMIT - Avionics 2023-24.
*/

#define GF  2.0       //Gauge Factor
#define E   5         //Excitation Voltage

int Analog = A5;

float strain = 0;
float voltage = 0;
int wheatStone = 0;

void setup() {

  Serial.begin(9600);

}

void loop() {

  wheatStone = analogRead(Analog);                    //Take analog Reading
  voltage    = map(wheatStone, 0, 1023, 0, E);        //Map to 0-5V range
  strain     = voltage * (0.8 / GF);                  //Calculate strain

  Serial.print("Strain Reading: ")
  Serial.println(strain);

}

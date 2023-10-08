#include <bf350.h>

GAUGE::GAUGE() {
    wheatStone = 0;
    voltage = 0;
    strain = 0;
}

float GAUGE::calculate() {
    wheatStone = analogRead(STRAIN_INPUT);
    voltage = 3.5 * wheatStone / 1023;
    strain  = 0.4 * voltage;

    return strain;
}
#include <ThrustMIT.h>

#define STRAIN_INPUT A5

class GAUGE {
    public:
    GAUGE();
    float calculate();

    private:
    int wheatStone;
    float voltage, strain;

};
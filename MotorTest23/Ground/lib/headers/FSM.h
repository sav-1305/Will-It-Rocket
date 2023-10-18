#ifndef FSM_h
#define FSM_h
#include <RF24.h>
typedef enum{
    INITIAL,
    KEYON,
    ARMON,
    LAUNCHON,
} States;
class FSM{
    public:
    FSM();
    int initializee();
    void arm();
    void key();
    void launch();
    private:
    States Curr=INITIAL;
};
#endif
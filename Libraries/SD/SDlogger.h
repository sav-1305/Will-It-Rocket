#include <ThrustMIT.h>

class LOGGING {
    public:
    LOGGING();
    void init();
    void log(float buffer);
    void close();

    private:
    File logFile;

};
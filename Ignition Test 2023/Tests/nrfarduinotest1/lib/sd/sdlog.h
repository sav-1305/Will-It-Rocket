#ifndef sdlog_h
#define sdlog_h

#include <SPI.h>
#include <SD.h>

class SDLog
{
    public:
        SDLog();
        void openfile(char filename[]);
        void logData(String buffer);
    private:
        File log;
};

#endif
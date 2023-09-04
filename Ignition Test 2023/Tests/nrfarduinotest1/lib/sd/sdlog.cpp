#include <sdlog.h>

SDLog::SDLog()
{
    if (!SD.begin())
    {
        while(1);
    }
}

void SDLog::openfile(char filename[])
{
    log = SD.open(filename, FILE_WRITE);
}

void SDLog::logData(String buffer)
{
    if (log)
    {
        log.println(buffer);
        log.close();
    }
}
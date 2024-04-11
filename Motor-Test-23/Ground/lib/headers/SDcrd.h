#include<SD.h>
#ifndef NrF_h
#define NrF_h

class SDsetup{
    public:
       void initialize();
       void WritetoFile(struct data* s);
       void ReadFile();
    private:
       File myFile;
}; 
#endif
#include <stdio.h>
#include <fftw3.h>
#include <sndfile.h>
#include <sndfile.hh>
#include "gilbertanalysis.h"
#include "gilbertsignalutil.h"

class gilbert{

    gilbertdb *gdb = new gilbertdb();
    gilbertclassifier *gc = new gilbertclassifier(*gdb);

    std::vector<double> twoSecBuffer;
    std::string drumname;
    

public:
    gilbert();
    ~gilbert();
    
    std::string audioIn(std::vector<double> buffer);
    //analysing the hit and adding it to the database.
    void registerBuffer(std::string name);

    void deleteLastBuffer();
    void deleteBufferByID(std::string id);

};

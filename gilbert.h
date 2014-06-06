#include <stdio.h>
#include <fftw3.h>
#include <sndfile.h>
#include <sndfile.hh>
#include "gilbertanalysis.h"
#include "gilbertsignalutil.h"

class gilbert{
public:
    gilbert();
    ~gilbert();
    
    std::string registerBuffer(std::string name);
    std::string lookupBuffer();
    void deleteLastBuffer();
    void deleteBufferByID(std::string id);
};

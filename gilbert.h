#include <stdio.h>
#include <fftw3.h>
#include <sndfile.h>
#include <sndfile.hh>
#include "gilbertanalysis.h"
#include "gilbertsignalutil.h"

class gilbert{
	
	gilbertdb *gdb = new gilbertdb();
	gilbertclassifier *gc = new gilbertclassifier(*gdb);

	std::vector<double> currentBuffer;
	void setCurrentBuffer(buffer);
	std::vector<double> getCurrentBuffer();
public:
    gilbert();
    ~gilbert();
    
    std::string audioIn(std::vector<double> buffer);
    //analysing the hit and adding it to the database.
    std::string registerBuffer(std::string name);
    
    void deleteLastBuffer();
    void deleteBufferByID(std::string id);
};

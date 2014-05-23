#include <stdio.h>
#include <fftw3.h>
#include <sndfile.h>
#include <sndfile.hh>
#include "gilbertanalysis.h"
#include "gilbertclassifier.h"

int main( int argc, const char* argv[] ){

    SndfileHandle file;
    double buffer[186369];
    int bufferSize = sizeof(buffer)/sizeof(*buffer);
    const char * fname = "test2.wav";

    file = SndfileHandle(fname);
    file.read(buffer, bufferSize);
    std::vector<double> sampleVec(buffer, buffer + sizeof(buffer)/sizeof(*buffer));
    gilbertanalysis* gilan = new gilbertanalysis();
    // std::vector<double> exact(gilan->getExactHit(sampleVec,0.00000001));
    // std::cout<<exact.size()<<std::endl;

}
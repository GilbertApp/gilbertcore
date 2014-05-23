#include <stdio.h>
#include <fftw3.h>
#include <sndfile.h>
#include <sndfile.hh>
#include "gilbertanalysis.h"
#include "gilbertclassifier.h"
// #include "soundfeatureset.c"

int main( int argc, const char* argv[] ){

    SndfileHandle file;

    //BUFFER SIZE HAS TO BE AN EVEN NUMBER!!!!!
    double buffer[160400];
    int bufferSize = sizeof(buffer)/sizeof(*buffer);
    const char * fname = "test2.wav";

    file = SndfileHandle(fname);
    file.read(buffer, bufferSize);

    std::vector<double> sampleVec(buffer, buffer + sizeof(buffer)/sizeof(*buffer));

    gilbertanalysis* gilan = new gilbertanalysis();
    std::vector<double> exact(gilan->getExactHit(sampleVec, 0.00000001));
    sfs info = gilan->analyseHitBuffer(exact, "nvnv");
    for (int i = 0; i < info.centroid.size(); ++i){
        std::cout << info.centroid.at(i) << std::endl;
    }
    // gilan->writeWAV(exact,exact.size(),info.id,info);

}
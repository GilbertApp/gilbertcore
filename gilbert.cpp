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

    std::cout<<std::endl;
    std::cout << "Spectral Centroid" << std::endl;
    std::cout << "Mean: " << gilan->calcMean(info.centroid) << std::endl;
    std::cout << "Standard Deviation: " << gilan->calcStanDev(info.centroid) << std::endl;
    std::cout << "Min: " << gilan->getMin(info.centroid) << std::endl;
    std::cout << "Max: " << gilan->getMax(info.centroid) << std::endl;
    std::cout<<std::endl;
    std::cout << "RMS" << std::endl;
    std::cout << "Mean: " << gilan->calcMean(info.rms) << std::endl;
    std::cout << "Standard Deviation: " << gilan->calcStanDev(info.rms) << std::endl;
    std::cout << "Min: " << gilan->getMin(info.rms) << std::endl;
    std::cout << "Max: " << gilan->getMax(info.rms) << std::endl;
    // gilan->writeWAV(exact,exact.size(),info.id,info);

}
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
    const char * fname = "test4.wav";

    file = SndfileHandle(fname);
    file.read(buffer, bufferSize);

    std::vector<double> sampleVec(buffer, buffer + sizeof(buffer)/sizeof(*buffer));

    gilbertanalysis* gilan = new gilbertanalysis();
    std::vector<double> exact(gilan->getExactHit(sampleVec, 0.00000001));
    sfs info = gilan->analyseHitBuffer(exact, "nvnv");

    std::cout<<std::endl;
    std::cout << "Spectral Centroid" << std::endl;
    std::cout << "Mean: " << info.sc_mean << std::endl;
    std::cout << "Standard Deviation: " << info.sc_stanDev << std::endl;
    std::cout << "Min: " << info.sc_min << std::endl;
    std::cout << "Max: " << info.sc_max << std::endl;
    std::cout<<std::endl;
    std::cout << "RMS" << std::endl;
    std::cout << "Mean: " << info.rms_mean << std::endl;
    std::cout << "Standard Deviation: " << info.rms_stanDev << std::endl;
    std::cout << "Min: " << info.rms_min << std::endl;
    std::cout << "Max: " << info.rms_max << std::endl;
    // gilan->writeWAV(exact,exact.size(),info.id,info);

}
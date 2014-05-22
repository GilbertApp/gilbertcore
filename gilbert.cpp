#include <stdio.h>
#include <fftw3.h>
#include "gilanalysis.h"
#include "gilclassifier.h"
#include "sndfile.h"
#include "sndfile.hh"

int main( int argc, const char* argv[] ){

    SndfileHandle file ;
    float buffer[88200];
    int bufferSize = sizeof(buffer)/sizeof(*buffer);

    file = SndfileHandle("test.wav") ;
    file.read(buffer, bufferSize) ;
    // std::vector<float> sampleVec(buffer, buffer + sizeof(buffer)/sizeof(*buffer));

    fftwf_complex out[bufferSize];
    fftwf_plan p = fftwf_plan_dft_r2c_1d(bufferSize,buffer, out, FFTW_ESTIMATE);
    fftwf_execute(p);
    fftwf_destroy_plan(p);
    std::cout << "Calculated FFT" <<std::endl;
    
}
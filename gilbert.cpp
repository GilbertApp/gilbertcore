#include <stdio.h>
#include <fftw3.h>
#include "gilanalysis.h"
#include "gilclassifier.h"
#include "sndfile.h"

int main( int argc, const char* argv[] ){
    char *infilename;
    SNDFILE *infile = NULL;
    SF_INFO sfinfo;

    infile = sf_open("test.wav",SFM_READ,&sfinfo);

    float samples[83060];

    sf_read_float(infile, samples, 1);

    std::vector<float> sampleVec(samples, samples + sizeof samples / sizeof samples[0]);

    gilbertAnalysis *gana = new gilbertAnalysis();

    std::vector<float> thing = gana->getExactHit(sampleVec,0.4);

    gana->analyseHitBuffer(thing,"yay");

    printf("this worked");
}
#include <stdio.h>
#include <fftw3.h>
#include <sndfile.h>
#include <sndfile.hh>
#include "gilbertanalysis.h"
#include "gilbertclassifier.h"
// #include "gilbertdb.h"

// #include "soundfeatureset.c"

int main( int argc, const char* argv[] ){

    SndfileHandle file;

    //BUFFER SIZE HAS TO BE AN EVEN NUMBER!!!!!
    double buffer[160400];
    double buffer2[160400];
    int bufferSize = sizeof(buffer)/sizeof(*buffer);
    const char * fname = "test2.wav";
    const char * fname2 = "test4.wav";

    file = SndfileHandle(fname);
    file.read(buffer, bufferSize);
    file = SndfileHandle(fname2);
    file.read(buffer2, bufferSize);

    std::vector<double> sampleVec(buffer, buffer + sizeof(buffer)/sizeof(*buffer));
    std::vector<double> sampleVec2(buffer2, buffer2 + sizeof(buffer2)/sizeof(*buffer2));

    gilbertanalysis* gilan = new gilbertanalysis();
    std::vector<double> exact(gilan->getExactHit(sampleVec, 0.00000001));
    std::vector<double> exact2(gilan->getExactHit(sampleVec2, 0.00000001));
    sfs info = gilan->analyseHitBuffer(exact, "sound1");
    sfs info2 = gilan->analyseHitBuffer(exact2, "sound2");

    std::vector<sfs> features = gilbertdb::getFeatures();;
    for(int i = 0 ; i < features.size(); i++){
        std::cout<<"***********************"<<std::endl;
        std::cout<<features.at(i).id<<std::endl;
        std::cout<<"SC: "<<features.at(i).sc_mean<<std::endl;
        std::cout<<"RMS: "<<features.at(i).rms_mean<<std::endl;
    }
    // gilan->writeWAV(exact,exact.size(),info.id,info);

}
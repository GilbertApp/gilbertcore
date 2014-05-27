#include <stdio.h>
#include <fftw3.h>
#include <sndfile.h>
#include <sndfile.hh>
#include "gilbertanalysis.h"
// #include "gilbertclassifier.h"

int main( int argc, const char* argv[] ){

    SndfileHandle file;

    //BUFFER SIZE HAS TO BE AN EVEN NUMBER!!!!!
    // double buffer[][]
    double buffer[160400];
    double buffer2[160400];
    double buffer3[160400];
    double buffer4[160400];

    int bufferSize = sizeof(buffer)/sizeof(*buffer);

    const char * fname = "test2.wav";
    const char * fname2 = "test3.wav";
    const char * fname3 = "test4.wav";
    const char * fname4 = "realtime1.wav";

    file = SndfileHandle(fname);
    file.read(buffer, bufferSize);
    file = SndfileHandle(fname2);
    file.read(buffer2, bufferSize);
    file = SndfileHandle(fname3);
    file.read(buffer3, bufferSize);
    file = SndfileHandle(fname4);
    file.read(buffer4, bufferSize);

    std::vector<double> sampleVec(buffer, buffer + sizeof(buffer)/sizeof(*buffer));
    std::vector<double> sampleVec2(buffer2, buffer2 + sizeof(buffer2)/sizeof(*buffer2));
    std::vector<double> sampleVec3(buffer3, buffer3 + sizeof(buffer3)/sizeof(*buffer3));
    std::vector<double> sampleVec4(buffer4, buffer4 + sizeof(buffer4)/sizeof(*buffer4));

    gilbertanalysis* gilan = new gilbertanalysis();

    std::vector<double> exact(gilan->getExactHit(sampleVec, 0.00000001));
    std::vector<double> exact2(gilan->getExactHit(sampleVec2, 0.00000001));
    std::vector<double> exact3(gilan->getExactHit(sampleVec3, 0.00000001));
    std::vector<double> exact4(gilan->getExactHit(sampleVec4, 0.00000001));

    gilbertdb::setFeature(gilan->analyseHitBuffer(exact, "sound1"));
    gilbertdb::setFeature(gilan->analyseHitBuffer(exact2, "sound2"));
    gilbertdb::setFeature(gilan->analyseHitBuffer(exact3, "sound3"));
    gilbertclassifier::lookupClosest(gilan->analyseHitBuffer(exact4));

    // gilan->writeWAV(exact,exact.size(),info.id,info);

}
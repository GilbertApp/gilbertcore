#include <iostream>
#include <stdio.h>
#include <vector>
#include <sndfile.h>
#include <math.h>
#include "fft.h"
#include "soundfeatureset.c"

class gilbertAnalysis {
    fft gilfft;
public:
    float calcRMS(std::vector<float>& exactHit);
    float calcSC(std::vector<float>& shortBuffer);
    std::vector<float> getExactHit(std::vector<float>&hitBuffer, float ambientRMS);
    sfs analyseHitBuffer(std::vector<float>& hitBuffer, std::string drum);
    // void writeWAV(std::vector<float>& buffer, int bufferSize, std::string drum, sfs info);
    
};

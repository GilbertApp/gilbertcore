#include <iostream>
#include <stdio.h>
#include <vector>
#include <sndfile.h>
#include <math.h>
#include "fft.h"
#include "soundfeatureset.c"

class gilbertAnalysis {
public:
    float calcRMS(std::vector<float>& exactHit);
    float calcSC(std::vector<float>& buffer);
    std::vector<float> getExactHit(std::vector<float>&hitBuffer, float threshold);
    sfs analyseHitBuffer(std::vector<float>& exactHitBuffer, std::string drum);
    // void writeWAV(std::vector<float>& buffer, int bufferSize, std::string drum, sfs info);
    
};

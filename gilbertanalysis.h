#include <iostream>
#include <stdio.h>
#include <vector>
#include <math.h>
#include <fftw3.h>
#include <sndfile.h>
#include <sndfile.hh>
#include "soundfeatureset.c"

class gilbertanalysis {
public:
    double calcRMS(std::vector<double>& exactHit);
    double calcSC(std::vector<double>& buffer);
    std::vector<double> getExactHit(std::vector<double>&hitBuffer, double threshold);
    sfs analyseHitBuffer(std::vector<double>& exactHitBuffer, std::string drum);
    void writeWAV(std::vector<double>& buffer, int bufferSize, std::string drum, sfs info);   
};

#include "gilanalysis.h"

//--------------------------------------------------------------
float gilbertAnalysis::calcRMS(std::vector<float>& buffer){

    float count = 0;
    for(int i=0; i<buffer.size(); i++){
        count += pow(buffer.at(i),2);
    }
    count = count/buffer.size();
    return sqrt(count);

}

//--------------------------------------------------------------
float gilbertAnalysis::calcSC(std::vector<float>& buffer){

    int bufferSize = buffer.size();
    float sampleRate = 44100;
    float sumMags = 0;
    float sumFreqByMags = 0;
    float centroid = 0;
    float samplerateDividedBySize = (sampleRate/(float)bufferSize);
    float* samples = &buffer[0];

    fftwf_complex out[bufferSize];
    fftwf_plan p = fftwf_plan_dft_r2c_1d(bufferSize,samples, out, FFTW_ESTIMATE);
    fftwf_execute(p);
    fftwf_destroy_plan(p);
    
    for(int i = 0; i < bufferSize; i++){
        sumMags += out[i][0];
        sumFreqByMags += out[i][0]*i*samplerateDividedBySize;
    }
    
    centroid = sumFreqByMags/sumMags;

    //TBD: Check whether we need to divide it by the Nyqist.
    return centroid/sampleRate/2f;

}

//---------------------------------------------------------------
std::vector<float> gilbertAnalysis::getExactHit(std::vector<float> &hitBuffer, float threshold){

    //Every how many samples should the RMS be calculated.
    int resolution = 100;
    //Initialisation of the hightest RMS bin.
    int highestRMSBin = 0;
    //A new vector that will contain the exact hit.
    std::vector<float> exactHit(8192);
    //An array of floats, which each representing the RMS of 100 samples.
    float* rmsInEachBin = new float[hitBuffer.size()/resolution];
    //Setting the threshold.
    float highestRMSValue = threshold;

    for(int i = 0; i<hitBuffer.size()-resolution; i+=resolution){

        //create small arrays, each of length 100 samples.
        std::vector<float>::const_iterator first = hitBuffer.begin() + i;
        std::vector<float>::const_iterator last = hitBuffer.begin() + i + resolution;
        std::vector<float> hitBufferBin(first, last);

        //setting the RMS in a bin.
        rmsInEachBin[i/resolution] = calcRMS(hitBufferBin);
        
        //Checking whether the RMS is greater then the average RMS - if so, detect an onset.
        //Only the highest RMS value is kept, therefore, only the loudest hit is kept.
        if(rmsInEachBin[i/resolution]>highestRMSValue){
            highestRMSValue = rmsInEachBin[i/resolution];
            highestRMSBin = i;
        }

    }
    
    for(int j = 0 ; j < exactHit.size(); j++) {
        //populates a new vector with the values of the exact hit.
        //This would crash with an array out of bounds if the hit was done at the end of the two seconds.
        exactHit[j]=hitBuffer[j+highestRMSBin];
    }
    //returns ~200 milliseconds of the exact hit.
    return exactHit;
}

//---------------------------------------------------------------
sfs gilbertAnalysis::analyseHitBuffer(std::vector<float> &exactHitBuffer, std::string drum){

    int numWindows = 64;
    int windowSize = 128;
    //A vector of spectral centroid values
    std::vector<float> centroidEnvelope;
    //A vector of RMS values
    std::vector<float> rmsEnvelope;

    //Calculating the spectral centroid and RMS for each window.
    for(int i = 0; i < numWindows; i+=windowSize){
        centroidEnvelope.push_back(calcSC(exactHitBuffer[i]));
        rmsEnvelope.push_back(calcRMS(exactHitBuffer[i]));
    }

    //Creating a new sound feature set object.
    sfs hitInfo = {.id=drum, .centroid=centroidEnvelope, .rms=rmsEnvelope};
    
    return hitInfo;
}

//--------------------------------------------------------------
void gilbertAnalysis::writeWAV(std::vector<float>& buffer, int bufferSize, std::string drum, sfs info){
    float* exactHitArray;
    exactHitArray = new float[buffer.size()];
    for(int j = 0; j<buffer.size(); j++){
        exactHitArray[j] = buffer[j];
    }
    // define the desired output format
    SF_INFO sfinfo ;
    sfinfo.channels = 1;
    sfinfo.samplerate = 44100;
    sfinfo.format = SF_FORMAT_WAV | SF_FORMAT_PCM_16;
    
    std::string path = "../../../";
    path+=drum;
    path+=".wav";
    std::cout << path.c_str() << std::endl;
    
    SNDFILE * outfile = sf_open(path.c_str(), SFM_WRITE, &sfinfo);
    char strbuf[50];
    sf_set_string(outfile, SF_STR_COMMENT, strbuf);
    sf_count_t count = sf_write_float(outfile, &exactHitArray[0], bufferSize);
    sf_write_sync(outfile);
    sf_close(outfile);
}

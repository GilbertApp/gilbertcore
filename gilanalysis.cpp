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
    float * exactHitArray = &buffer[0];
    int size = buffer.size();

    float centroid = 0;
    
    float samplerateDividedBySize = (44100.0f/(float)size);
    
    float sumMags = 0;
    float sumFreqByMags = 0;

    float* samples = &buffer[0];

    fftw_complex out[buffer.size()];
    fftw_plan p = fftw_plan_dft_r2c_1d(buffer.size(),samples, out, FFTW_ESTIMATE);

    fftw_execute(p);
    fftw_destroy_plan(p);
    
    for(int i = 0; i < size; i++){
        sumMags += out[i][0];
        sumFreqByMags += out[i][0]*i*samplerateDividedBySize;
    }
    
    centroid = sumFreqByMags/sumMags;

    return centroid/22050.0f;
}

std::vector<float> gilbertAnalysis::getExactHit(std::vector<float> &hitBuffer, float threshold){
    std::vector<float> exactHit(8192);
    float* rmsInEachBin = new float[822];
    int highestRMSBin = 0;
    float highestRMSValue = threshold;
    for(int i = 0; i<hitBuffer.size()-100; i+=100){
        
        //calculate its rms and store it as an array element.
        std::vector<float>::const_iterator first = hitBuffer.begin() + i;
        std::vector<float>::const_iterator last = hitBuffer.begin() + i + 100;
        std::vector<float> hitBufferBin(first, last);
        rmsInEachBin[i/100] = calcRMS(hitBufferBin);
        
        if(rmsInEachBin[i/100]>highestRMSValue){
            highestRMSValue = rmsInEachBin[i/100];
            highestRMSBin = i;
        }
    }
    
    for(int j = 0 ; j < exactHit.size(); j++) {
        exactHit[j]=hitBuffer[j+highestRMSBin];
    }
    return exactHit;
}

//---------------------------------------------------------------
sfs gilbertAnalysis::analyseHitBuffer(std::vector<float> &hitBuffer, std::string drum){
    //array to store rms in each bin

    std::vector<float> centroidEnvelope;
    std::vector<float> rmsEnvelope;

    for(int i = 0; i < 64; i+=128){
        centroidEnvelope.push_back(calcSC(hitBuffer));
        rmsEnvelope.push_back(calcRMS(hitBuffer));
    }

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

#include "gilbertanalysis.h"


//--------------------------------------------------------------
double gilbertanalysis::calcRMS(std::vector<double>& buffer){

    double count = 0;
    for(int i=0; i<buffer.size(); i++){
        count += pow(buffer.at(i),2);
    }
    count = count/buffer.size();
    return sqrt(count);

}

//--------------------------------------------------------------
double gilbertanalysis::calcSC(std::vector<double>& buffer){

    int bufferSize = buffer.size();
    float sampleRate = 44100;
    double sumMags = 0;
    double sumFreqByMags = 0;
    double centroid = 0;
    double samplerateDividedBySize = (sampleRate/(double)bufferSize);
    double* samples = &buffer[0];

    //what should the size of the FFT be?
    fftw_complex out[1024];
    fftw_plan p = fftw_plan_dft_r2c_1d(bufferSize,samples, out, FFTW_ESTIMATE);
    fftw_execute(p);
    fftw_destroy_plan(p);
    
    for(int i = 0; i < bufferSize; i++){
        // std::cout << out[i][0] << std::endl;
        sumMags += out[i][0];
        sumFreqByMags += out[i][0]*i*samplerateDividedBySize;
    }
    // std::cout<<sumFreqByMags<<std::endl;
    centroid = sumFreqByMags/sumMags;

    //TBD: Check whether we need to divide it by the Nyqist.
    return centroid/sampleRate/2;

}

//---------------------------------------------------------------
std::vector<double> gilbertanalysis::getExactHit(std::vector<double> &hitBuffer, double threshold){

    //Every how many samples should the RMS be calculated.
    int resolution = 100;
    //Initialisation of the hightest RMS bin.
    int highestRMSBin = 0;
    //A new vector that will contain the exact hit.
    std::vector<double> exactHit(8192);
    //An array of doubles, which each representing the RMS of 100 samples.
    std::vector<double> rmsInEachBin;
    //Setting the threshold.
    double highestRMSValue = threshold;

    for(int i = 0; i<(hitBuffer.size()-resolution); i+=resolution){
        //create small vectors, each of length 100 samples.
        std::vector<double> hitBufferBin(&hitBuffer[i],&hitBuffer[i+resolution]);

        //Storing RMS of every 100 samples in a vector.
        rmsInEachBin.push_back(calcRMS(hitBufferBin));
    }

    //Checking whether the RMS is greater then the average RMS - if so, detect an onset.
    //Only the highest RMS value is kept, therefore, only the loudest hit is kept.
    for (int i = 0; i < rmsInEachBin.size(); i++){
        std::cout<<rmsInEachBin.at(i)<<std::endl;
        if(rmsInEachBin.at(i)>highestRMSValue){
            std::cout << i<<std::endl;
            highestRMSValue = rmsInEachBin.at(i);
            highestRMSBin = i*resolution;
        }
    }

    for(int j = 0 ; j < exactHit.size(); j++) {
        // populates a new vector with the values of the exact hit.
        //This would crash with an array out of bounds if the hit was done at the end of the two seconds.
        exactHit.at(j)=hitBuffer.at(j+highestRMSBin);
    }

    //returns ~200 milliseconds of the exact hit.
    return exactHit;
}

//---------------------------------------------------------------
sfs gilbertanalysis::analyseHitBuffer(std::vector<double> &exactHitBuffer, std::string drum){

    int numWindows = 64;
    int windowSize = 128;
    //A vector of spectral centroid values
    std::vector<double> centroidEnvelope;
    //A vector of RMS values
    std::vector<double> rmsEnvelope;

    //Calculating the spectral centroid and RMS for each window.
    for(int i = 0; i < exactHitBuffer.size(); i+=windowSize){

        std::vector<double>::const_iterator first = exactHitBuffer.begin() + i;
        std::vector<double>::const_iterator last = exactHitBuffer.begin() + i + windowSize;
        std::vector<double> window(first, last);
        // std::cout<<calcSC(window)<<std::endl;

        centroidEnvelope.push_back(calcSC(window));
        rmsEnvelope.push_back(calcRMS(window));
    }

    //Creating a new sound feature set object.
    sfs hitInfo = {.id=drum, .centroid=centroidEnvelope, .rms=rmsEnvelope};
    
    return hitInfo;
}

//--------------------------------------------------------------
void gilbertanalysis::writeWAV(std::vector<double>& buffer, int bufferSize, std::string drum, sfs info){
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
    
    std::string path = "";
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

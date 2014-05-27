#include "gilbertsignalutil.h"

//---------------------------------------------------------------
std::vector<double> gilbertsignalutil::getExactHit(std::vector<double> &hitBuffer, double threshold){

    //Every how many samples should the RMS be calculated.
    int resolution = 100;
    //Initialisation of the hightest RMS bin.
    int highestRMSBin = 0;
    //A new vector that will contain the exact hit.
    int exactHitLength = 4096;
    std::vector<double> exactHit(exactHitLength);
    //An array of doubles, which each representing the RMS of 100 samples.
    std::vector<double> rmsInEachBin;
    //Setting the threshold.
    double highestRMSValue = threshold;

    for(int i = 0; i<hitBuffer.size(); i+=resolution){
        //create small vectors, each of length 100 samples.
        std::vector<double> hitBufferBin(&hitBuffer[i],&hitBuffer[i+resolution]);

        //Storing RMS of every 100 samples in a vector.
        rmsInEachBin.push_back(calcRMS(hitBufferBin));
    }

    //Checking whether the RMS is greater then the average RMS - if so, detect an onset.
    //Only the highest RMS value is kept, therefore, only the loudest hit is kept.
    for (int i = 0; i < rmsInEachBin.size(); i++){
        // std::cout<<rmsInEachBin.at(i)<<std::endl;
        if(rmsInEachBin.at(i)>highestRMSValue){
            // std::cout << i<<std::endl;
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

//--------------------------------------------------------------
void gilbertsignalutil::writeWAV(std::vector<double>& buffer, std::string drum, sfs info){
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
    sf_count_t count = sf_write_float(outfile, &exactHitArray[0], buffer.size());
    sf_write_sync(outfile);
    sf_close(outfile);
}
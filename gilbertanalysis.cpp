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
    //TODO: Normalize centroid. Dividing by nyquist is not good as most of the centroid values will be < 5000,
    //so we'll lose half of the range.

    int bufferSize = buffer.size();
    float sampleRate = 44100;
    double sumMags = 0;
    double sumFreqByMags = 0;
    double centroid = 0;
    double samplerateDividedBySize = (sampleRate/(double)bufferSize);
    double* samples = &buffer[0];

    //what should the size of the FFT be?
    //In any case (for 128 samples long signal) it returns 64 bins.. some of them negative :/.
    fftw_complex out[2048];
    fftw_plan p = fftw_plan_dft_r2c_1d(bufferSize,samples, out, FFTW_ESTIMATE);
    fftw_execute(p);
    fftw_destroy_plan(p);
    
    for(int i = 0; i < bufferSize; i++){
        float mag = sqrt(pow(out[i][0],2) + pow(out[i][1],2));
        sumMags += mag;
        sumFreqByMags += mag*i*samplerateDividedBySize;
    }
    centroid = sumFreqByMags/sumMags;

    return centroid;

}

//---------------------------------------------------------------
sfs gilbertanalysis::analyseExactHitBuffer(std::vector<double> &exactHitBuffer, std::string drum){
    sfs hitInfo = analyseExactHitBuffer(exactHitBuffer);

    hitInfo.id = drum;
    
    return hitInfo;
}

//---------------------------------------------------------------
sfs gilbertanalysis::analyseExactHitBuffer(std::vector<double> &exactHitBuffer){

    int windowSize = 128;
    //A vector of spectral centroid values
    std::vector<double> centroidEnvelope;
    //A vector of RMS values
    std::vector<double> rmsEnvelope;

    //Calculating the spectral centroid and RMS for each window.
    for(int i = 0; i < exactHitBuffer.size(); i+=windowSize){
        std::vector<double> window(&exactHitBuffer[i],&exactHitBuffer[i+windowSize]);
        centroidEnvelope.push_back(calcSC(window));
        rmsEnvelope.push_back(calcRMS(window));
    }

    //Creating a new sound feature set object.
    sfs hitInfo = createSFS(centroidEnvelope, rmsEnvelope);
    
    return hitInfo;
}

//---------------------------------------------------------------
sfs gilbertanalysis::createSFS(std::vector<double> centroids, std::vector<double> rmss){
    std::string realTimeId = "realtime";
    sfs hitInfo = {.id = realTimeId,
                   .sc_mean = calcMean(centroids), .sc_stanDev = calcStanDev(centroids), .sc_min = getMin(centroids), .sc_max = getMax(centroids),
                   .rms_mean = calcMean(rmss), .rms_stanDev = calcStanDev(rmss), .rms_min = getMin(rmss), .rms_max = getMax(rmss)
                };

    return hitInfo;

}

/****************************FEATURE EXTRACTORS****************************/

//---------------------------------------------------------------
double gilbertanalysis::calcMean(std::vector<double> v){
    double mean = 0,
            sum = 0;
    int vectorSize = v.size();

    for (int i = 0; i < vectorSize; i++){
        sum += v.at(i);
    }
    mean = sum/vectorSize;

    return mean;
}

//---------------------------------------------------------------
double gilbertanalysis::calcStanDev(std::vector<double> v){
    double mean = calcMean(v);
    double sqDiffSum = 0;
    int vectorSize = v.size();

    for (int i = 0; i < vectorSize; i++){
        double sqDiff = v.at(i) - mean;
        sqDiff = pow(sqDiff,2);
        sqDiffSum += sqDiff;
    }

    double variance = sqDiffSum/vectorSize;
    double sd = sqrt(variance);
    return sd;
}

//---------------------------------------------------------------
double gilbertanalysis::getMin(std::vector<double> v){
    double min = *std::min_element(v.begin(), v.end());
    return min;
}

//---------------------------------------------------------------
double gilbertanalysis::getMax(std::vector<double> v){
    double max = *std::max_element(v.begin(), v.end());
    return max;
}

/******************************************************************************/

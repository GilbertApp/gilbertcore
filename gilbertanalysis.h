//! A class for analysis of signal buffers

//! GilbertAnalysis provides an api for extracting 'high level' features from audio signals, such as RMS and Spectral Centroid, and 
//! extracting meta-features from those features, grouping these features into a struct of type Sound Feature Set. It also provides
//! other related utilities, such as extracting a short impulse from a longer signal based on peak detection.

#include <iostream>
#include <stdio.h>
#include <vector>
#include <math.h>
#include <algorithm> 
#include <fftw3.h>
#include <sndfile.h>
#include <sndfile.hh>
#include "gilbertclassifier.h"

class gilbertanalysis {
public:
    //! Calculates the Root Mean Square of an input signal in vector format
    double calcRMS(std::vector<double>& exactHit);
    //! Calculates the Spectral Centroid of an input signal in vector format
    double calcSC(std::vector<double>& buffer);
    //! Extracts an 'exact hit' signal buffer from a longer buffer based on peak detection
    std::vector<double> getExactHit(std::vector<double>&hitBuffer, double threshold);
    //! Returns a Sound Feature Set struct representative of the signal input
    sfs analyseHitBuffer(std::vector<double>& exactHitBuffer);
    //! Returns a Sound Feature Set struct representative of the signal input with an ID
    sfs analyseHitBuffer(std::vector<double>& exactHitBuffer, std::string drum);
    //! Returns a Sound Feature Set struct based on sets of centroid and rms values
    sfs createSFS(std::vector<double> centroids, std::vector<double> rmss, std::string drum);
    //! Calculates the mean value of a vector
    double calcMean(std::vector<double> v);
    //! Calculates the standard deviation of a vector
    double calcStanDev(std::vector<double> v);
    //! Finds the minimum value in a vector
    double getMin(std::vector<double> v);
    //! Finds the maximum value in a vector
    double getMax(std::vector<double> v);
    //! Returns a vector of features
    std::vector<double> extractFeatures(std::vector<double> v);
    //! Uses libsndfile to write a buffer to an audio file
    void writeWAV(std::vector<double>& buffer, int bufferSize, std::string drum, sfs info);   
};

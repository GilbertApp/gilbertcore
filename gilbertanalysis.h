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
    //! @param buffer the temporal domain signal to be analysed
    //! @return the RMS value of the signal
    //! @see calcSC
    double calcRMS(std::vector<double>& buffer);
    //! Calculates the Spectral Centroid of an input signal in vector format
    //! @param buffer the temporal domain signal to be analysed
    //! @return the RMS value of the signal
    //! @see calcSC
    double calcSC(std::vector<double>& buffer);
    //! Extracts an 'exact hit' signal buffer from a longer buffer based on peak detection
    //! @param hitBuffer containing the hit and surrounding sound
    //! @param threshold a minimum threshold to find a peak
    //! @return buffer containing only the hit
    std::vector<double> getExactHit(std::vector<double>&hitBuffer, double threshold);
    //! Returns a Sound Feature Set struct representative of the signal input
    //! @param exactHitBuffer a buffer containing the precise, trimmed hit
    //! @return a sound feature set representing the buffer
    //! @see analyseHitBuffer
    //! @see createSFS
    sfs analyseHitBuffer(std::vector<double>& exactHitBuffer);
    //! Returns a Sound Feature Set struct representative of the signal input with an ID
    //! @param exactHitBuffer a buffer containing the precise, trimmed hit
    //! @param drum the id of the sound
    //! @return a sound feature set representing the buffer
    //! @see analyseHitBuffer
    //! @see createSFS
    sfs analyseHitBuffer(std::vector<double>& exactHitBuffer, std::string drum);
    //! Returns a Sound Feature Set struct based on sets of centroid and rms values with an ID
    //! @param centroids a buffer containing the centroids of a hit
    //! @param rmss a buffer containing the rmss of a hit
    //! @param drum the id of the sound
    //! @return a sound feature set representing the buffer
    //! @see analyseHitBuffer
    //! @see createSFS
    sfs createSFS(std::vector<double> centroids, std::vector<double> rmss, std::string drum);
    //! creates a sound feature set struct based on sets of centroid and rms values
    //! @param centroids a buffer containing the centroids of a hit
    //! @param rmss a buffer containing the rmss of a hit
    //! @return a sound feature set representing the buffer
    //! @see analyseHitBuffer
    //! @see createSFS
    sfs createSFS(std::vector<double> centroids, std::vector<double> rmss);
    //! Calculates the mean value of a vector
    //! @param v vector of values
    //! @return the mean of the values in v
    //! @see calcStanDev()
    //! @see getMin()
    //! @see getMax()
    //! @see extractFeatures()
    double calcMean(std::vector<double> v);
    //! Calculates the standard deviation of a vector
    //! @param v vector of values
    //! @return the standard deviation of the values in v
    //! @see calcMean()
    //! @see getMin()
    //! @see getMax()
    //! @see extractFeatures()
    double calcStanDev(std::vector<double> v);
    //! Finds the minimum value in a vector
    //! @param v vector of values
    //! @return the smallest of the values in v
    //! @see calcMean()
    //! @see calcStanDev()
    //! @see getMax()
    //! @see extractFeatures()
    double getMin(std::vector<double> v);
    //! Finds the maximum value in a vector
    //! @param v vector of values
    //! @return the largest of the values in v
    //! @see calcMean()
    //! @see calcStanDev()
    //! @see getMin()
    //! @see extractFeatures()
    double getMax(std::vector<double> v);
    //! Uses libsndfile to write a buffer to an audio file
    //! @param buffer an audio buffer to write to a file
    //! @param drum the id of the audio
    //! @param info a sound feature set representing the sound
    void writeWAV(std::vector<double>& buffer, std::string drum, sfs info);   
};

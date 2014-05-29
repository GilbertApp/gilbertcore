//! A struct to contain feature sets for specific sounds

//! This struct is the core data structure for the analysis output on an audio signal. It's used in representing signals for the classification engine
//! to look up the closest match of.

#include <iostream>
#include <stdio.h>
#ifndef SOUNDFEATURESET_C
#define SOUNDFEATURESET_C

typedef struct soundfeatureset{
    //! A unique identifier for the soundfeatureset instance
    std::string id;
    //! The mean value of the spectral centroid buffer
    double sc_mean;
    //! The standard deviation of the spectral centroid buffer
    double sc_stanDev;
    //! The minimum value of the spectral centroid buffer
    double sc_min;
    //! The maximum value of the spectral centroid buffer
    double sc_max;
    //! The mean value of the RMS buffer
    double rms_mean;
    //! The standard deviation of the RMS buffer
    double rms_stanDev;
    //! The minimum value of the RMS buffer
    double rms_min;
    //! The maximum value of the RMS buffer
    double rms_max;
} sfs;

#endif
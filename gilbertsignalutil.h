//! A utility class for manipulating signals.

//! Contains utilities to extract the onset from a buffer and to write a signal to a wav file.

#include <iostream>
#include <vector>
#include <math.h>
#include <algorithm>
#include <sndfile.h>
#include "soundfeatureset.cpp"
#include "gilbertanalysis.h"
#ifndef GILBERTSIGNALUTIL_H
#define GILBERTSIGNALUTIL_H

class gilbertsignalutil{

    //! Extracts the index of the loudest onset in a buffer
    //! @param hitBuffer a buffer containing the hit and surrounding sound
    //! @param threshold a minimum threshold to find a peak
    //! @return the index of the onset
    static int getOnsetIndex(std::vector<double> &hitBuffer, double threshold);

public:
    //! Extracts an 'exact hit' signal buffer from a longer buffer based on peak detection
    //! @param hitBuffer a buffer containing the hit and surrounding sound
    //! @param threshold a minimum threshold to find a peak
    //! @return buffer containing only the hit
    static std::vector<double> getExactHitBuffer(std::vector<double>&hitBuffer, double threshold);
    //! Uses libsndfile to write a buffer to an audio file
    //! @param buffer an audio buffer to write to a file
    //! @param drum the id of the audio
    //! @param info a sound feature set representing the sound
    static void writeWAV(std::vector<double>& buffer, std::string drum, sfs info);
};

#endif

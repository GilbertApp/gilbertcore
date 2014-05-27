//! Provides a database of classified sounds to the learning system

//! gilbertdb handles instances of the Sound Feature Set struct, facilitating addition and removal to and from
//! the database.

#include <iostream>
#include <stdio.h>
#include <vector>
#include <math.h>
#include <algorithm>
#include "soundfeatureset.c"

class gilbertdb {
public:
    //! Adds a feature to the database
    //! @param feature An input sound feature set
    //! @see lookupClosest()
    //! @see soundfeatureset
    static void setFeature(sfs feature);
    //! retrieves a specific feature as requested by id string
    //! @param _id A string identifying a specific class
    //! @return A sound feature set of class feature
    //! @see getFeature()
    //! @see removeFeature()
    //! @see getFeatures()
    //! @see soundfeatureset
    static sfs *getFeature(std::string _id);
    //! retrieves a vector of all of the features in the database
    //! @return A vector of all of the features in the database
    //! @see setFeature()
    //! @see removeFeature()
    //! @see getFeature()
    //! @see soundfeatureset
    static std::vector<sfs> getFeatures();
    //! removes a specific feature from the database by id
    //! @param _id A string identifying a specific class
    //! @see setFeature()
    //! @see getFeature()
    //! @see getFeatures()
    //! @see soundfeatureset
    static void removeFeature(std::string _id);
};

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
    //! adds a feature to the database
    static void setFeature(sfs feature);
    //! retrieves a specific feature as requested by id string
    static sfs *getFeature(std::string _id);
    //! retrieves all of the features in the database
    static std::vector<sfs> getFeatures();
    //! removes a specific feature from the database by id
    static void removeFeature(std::string _id);
};

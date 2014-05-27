//! A classifier for unidentified input sound feature sets

//! Analyses an input SFS and uses a kNN algorithm to find the hopefully most likely similar existing sound in a database of SFS structs.

#include <iostream>
#include <vector>
#include <math.h>
#include <algorithm> 
#include "gilbertdb.h"

class gilbertclassifier {
public:
    //! returns the classification of an input sound feature set
    std::string lookupClosest(sfs realTimeHit);
    //! calculates the euclidean distance between two sound feature sets
    double calcDistance(sfs a, sfs b);
};

//! A classifier for unidentified input sound feature sets

//! Analyses an input SFS and uses a kNN algorithm to find the hopefully most likely similar existing sound in a database of SFS structs.

#include <iostream>
#include <vector>
#include <math.h>
#include <algorithm> 
#include "gilbertdb.h"
#ifndef GILBERTCLASSIFIER_H
#define GILBERTCLASSIFIER_H

class gilbertclassifier {
    //! calculates the euclidean distance between two sound feature sets
    //! @param a First sound feature set
    //! @param b Second sound feature set
    //! @return A double representing the distance between the two input feature sets
    //! @see lookupClosest()
    double calcDistance(sfs a, sfs b);
    //! searches the most frequent string in a string vector
    //! @param v The vector that will be scanned
    //! @return A string representing the most frequent string
    //! @see lookupClosest
    std::string findMostFrequentId(std::vector<std::string> closestIds, std::vector<sfs> dbFeatures);
public:
	gilbertdb db;
	//! a constructor for gilbertclassifier
	//! @param db The database object.
	//! @see gilbertdb
	gilbertclassifier(gilbertdb db){
		this->db = db;
	}
    //! returns the classification of an input sound feature set
    //! @param realTimeHit An input sound feature set
    //! @return A string representing the classification of the input set
    //! @see lookupClosest()
    //! @see soundfeatureset
    std::string lookupClosest(sfs realTimeHit);
};

#endif
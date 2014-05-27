#include <iostream>
#include <vector>
#include <math.h>
#include <algorithm> 
#include "gilbertdb.h"

class gilbertclassifier {
public:
    std::string lookupClosest(sfs realTimeHit);
    double calcDistance(sfs a, sfs b);
};

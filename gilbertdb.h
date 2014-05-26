#include <iostream>
#include <stdio.h>
#include <vector>
#include <math.h>
#include <algorithm>
#include "soundfeatureset.c"

class gilbertdb {
public:
    static void setFeature(sfs feature);
    static sfs *getFeature(std::string _id);
    static std::vector<sfs> getFeatures();
};

#include "gilbertclassifier.h"


std::string gilbertclassifier::lookupClosest(sfs realTimeHit){
    int k = 5;
    int indices[k];
    bool swapped = false;
    std::vector<sfs> db = gilbertdb::getFeatures();
    for (int i = 0; i < db.size(); i++){
        double d = calcDistance(db.at(i), realTimeHit);
        for (int j = 0; j < k; j++){
            if(d < indices[j]){
                for (int m = k-1; m > j; m--){
                    indices[m] = indices[m-1];
                }
                indices[j] = d;
                break;
            }
        }
    }

    return "";
}

double gilbertclassifier::calcDistance(sfs a, sfs b){

    double distance = 0;

    distance += pow((a.sc_mean - b.sc_mean), 2);
    distance += pow((a.sc_stanDev - b.sc_stanDev), 2);
    distance += pow((a.sc_min - b.sc_min), 2);
    distance += pow((a.sc_max - b.sc_max), 2);
    distance += pow((a.rms_mean - b.rms_mean), 2);
    distance += pow((a.rms_stanDev - b.rms_stanDev), 2);
    distance += pow((a.rms_min - b.rms_min), 2);
    distance += pow((a.rms_max - b.rms_max), 2);
    distance = sqrt(distance);

    return distance;
}
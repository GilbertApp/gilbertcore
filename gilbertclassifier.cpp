#include "gilbertclassifier.h"


void gilbertclassifier::lookupClosest(sfs realTimeHit){
    int k = 3;
    
    std::vector<double> closest_d(k, 100000);
    std::vector<int> indices(k, 1000);

    std::vector<sfs> db = gilbertdb::getFeatures();
    for (int i = 0; i < db.size(); i++){
        double d = calcDistance(db.at(i), realTimeHit);
        for (int j = 0; j < k; j++){
            if(d < closest_d.at(j)){
                for (int m = k-1; m > j; m--){
                    closest_d.at(m) = closest_d.at(m-1);
                    indices.at(m) = indices.at(m-1); 
                }
                closest_d.at(j) = d;
                indices.at(j) = i;
                break;
            }
        }
    }

    for (int i = 0; i < k; i++){
        std::cout<<db.at(indices[i]).id<<std::endl;
        std::cout<<closest_d.at(i)<<std::endl;
    }
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
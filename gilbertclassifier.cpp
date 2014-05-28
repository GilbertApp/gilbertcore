#include "gilbertclassifier.h"


std::string gilbertclassifier::lookupClosest(sfs realTimeHit){
    int k = 3;

    std::vector<double> closest_d(k, 100000);
    std::vector<int> indices(k, 1000);

    std::vector<sfs> dbFeatures = db.getFeatures();
    for (int i = 0; i < dbFeatures.size(); i++){
        double d = calcDistance(dbFeatures.at(i), realTimeHit);
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
    std::vector<std::string> ids(k);
    for (int i = 0; i < indices.size(); i++){
        ids.at(i) = dbFeatures.at(indices.at(i)).id;
    }
    /*for testing purposes!!*/
        ids.push_back("sound1");
    /************************/
    std::string classification= findMostFrequentId(ids, dbFeatures);

    return classification;
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

std::string gilbertclassifier::findMostFrequentId(std::vector<std::string> closestIds, std::vector<sfs> dbFeatures){

    std::vector<int> counters(dbFeatures.size(), 0);
    std::sort(closestIds.begin(), closestIds.end());
    for (int i = 0; i < dbFeatures.size(); i++){
        for (int j = 0; j < closestIds.size(); j++){
            if(dbFeatures.at(i).id == closestIds.at(j)){
                counters.at(i)++;
            }
        }
    }

    int matchedIndex = std::distance(counters.begin(), max_element(counters.begin(),counters.end()));
    std::string matchedId = dbFeatures.at(matchedIndex).id;

    return matchedId;

}
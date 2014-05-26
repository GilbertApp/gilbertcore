#include "gilbertdb.h"

std::vector<sfs> features;

void gilbertdb::setFeature(sfs feature){
	features.push_back(feature);
}

sfs *gilbertdb::getFeature(std::string _id){
	for(int i = 0; i<features.size(); i++){
		if(features.at(i).id == _id){
			return &features.at(i);
		}
	}
	return NULL;
}

std::vector<sfs> gilbertdb::getFeatures(){
	return features;
}
#include "gilbert.h"


std::vector<double> gilbert::audioIn(std::vector<double> buffer){

	setCurrentBuffer(buffer);

}


std::string gilbert::registerBuffer(std::vector<double> buffer, std::string name){
	
	sfs hit = gilbertanalysis::analyseExactHitBuffer(gilbertsignalutil::getExactHitBuffer(buffer, getThreshold()), name);
	gilbertdb::putFeature(hit);

}

void gilbert::setCurrentBuffer(buffer){
	currentBuffer = buffer;
}

std::vector<double> gilbert::getCurrentBuffer(){
	return currentBuffer;
}

void gilbert::setThreshold(double _threshold){
	threshold = _threshold;
}

double gilbert::getThreshold(){
	return threshold;
}
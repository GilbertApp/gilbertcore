#include "gilbert.h"



std::vector<double> gilbert::audioIn(std::vector<double> buffer){

	setCurrentBuffer(buffer);
	
}


std::string gilbert::registerBuffer(std::vector<double> buffer, std::string name){
	
	sfs hit = gilbertanalysis::analyseExactHitBuffer(gilbertsignalutil::getExactHitBuffer(buffer, 0.000000001), name);
	gilbertdb::putFeature(hit);

}

void gilbert::setCurrentBuffer(buffer){
	currentBuffer = buffer;
}

std::vector<double> gilbert::getCurrentBuffer(){
	return currentBuffer;
}
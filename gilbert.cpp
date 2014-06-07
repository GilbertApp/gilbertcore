#include "gilbert.h"


std::vector<double> gilbert::audioIn(std::vector<double> buffer){
    setCurrentBuffer(buffer);
    if(self.drumname !== ''){
        //take the current buffer, analyse it, and add it to the database
        //do some concatenation stuff if necessary.
        self.drumname = '';
    }
}


std::string gilbert::registerBuffer(std::string name){
    self.drumname = name;
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
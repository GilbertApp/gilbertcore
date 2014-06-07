#include "gilbert.h"


std::vector<double> gilbert::audioIn(std::vector<double> buffer){
    std::vector<double> longBuffer;
    int sr = 44050;
    int twoSeconds = sr*2;
    if(self.drumname !== ''){
        if(longBuffer.size() < twoSeconds){
            longBuffer.push_back(buffer);
        }
        else{
            std::vector<double> exactHit = gilbertsignalutil::getExactHitBuffer(longBuffer, 0.0000001);
            sfs hitInfo = gilbertanalysis::analyseExactHitBuffer(exactHit, self.drumname);
            gdb->putFeature(hitInfo);
            longBuffer.clear();
            self.drumname = '';
        }
    }
}


std::string gilbert::registerBuffer(std::string name){
    self.drumname = name;
}

void gilbert::setThreshold(double _threshold){
    threshold = _threshold;
}

double gilbert::getThreshold(){
    return threshold;
}
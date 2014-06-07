#include "gilbert.h"


std::string *gilbert::audioIn(std::vector<double> buffer){
    int sr = 44050;
    int twoSeconds = sr*2;
    if(self.drumname !== ''){
        if(twoSecBuffer.size() < twoSeconds){
            twoSecBuffer.push_back(buffer);
        }
        else{
            std::vector<double> exactHit = gilbertsignalutil::getExactHitBuffer(twoSecBuffer, 0.0000001);
            sfs hitInfo = gilbertanalysis::analyseExactHitBuffer(exactHit, self.drumname);
            gdb->putFeature(hitInfo);
            twoSecBuffer.clear();
            self.drumname = '';
        }
        return NULL;
    }
    else{
        std::vector<double> exactHit = gilbertsignalutil::getExactHitBuffer(buffer, 0.0000001);
        sfs hitInfo = gilbertanalysis::analyseExactHitBuffer(exactHit);
        std::string classification = gc->lookupClosest(hitInfo);
        return classification;
    }
}

void gilbert::registerBuffer(std::string name){
    self.drumname = name;
}

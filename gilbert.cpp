#include "gilbert.h"

gilbert::gilbert(){
    
}

std::string gilbert::audioIn(std::vector<double> buffer){
    int sr = 44100;
    int twoSeconds = sr*2;
    if(this->drumname != ""){
        if(twoSecBuffer.size() < twoSeconds){
            twoSecBuffer.insert(twoSecBuffer.end(), buffer.begin(), buffer.end());
        }
        else{
            std::vector<double> exactHit = gilbertsignalutil::getExactHitBuffer(twoSecBuffer, 0.0000001);
            sfs hitInfo = gilbertanalysis::analyseExactHitBuffer(exactHit, this->drumname);
            gdb->putFeature(hitInfo);
            twoSecBuffer.clear();
            this->drumname = "";
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
    this->drumname = name;
}

std::string gilbert::test(){
    return "gilbert is loaded";
}
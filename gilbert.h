//! An interface to the gilbert core

//! Provides high level gilbert functionality to a platform specific wrapper.
#include <stdio.h>
#include <fftw3.h>
#include <sndfile.h>
#include <sndfile.hh>
#include "gilbertanalysis.h"
#include "gilbertsignalutil.h"

class gilbert{

    gilbertdb *gdb = new gilbertdb();
    gilbertclassifier *gc = new gilbertclassifier(*gdb);

    std::vector<double> twoSecBuffer;
    std::string drumname;
    

public:
    //! Constructor
    gilbert();
    //! Destructor
    ~gilbert();
    
    //! provides the audio to gilbert core
    //! @param buffer an audio buffer
    //! @return a string representing the looked up drum
    std::string audioIn(std::vector<double> buffer);
    //! sets a flag for the 'current' buffer to be added to the database under the name
    //! @param name the name of the drum
    void registerBuffer(std::string name);
    //! deletes the last buffer that was saved into the database
    void deleteLastBuffer();
    //! deletes a specific sfs in the database by id
    //! the id of the sfs to be deleted
    void deleteBufferByID(std::string id);

    std::string test();
};

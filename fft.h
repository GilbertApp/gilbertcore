#ifndef _FFT
#define _FFT

#ifndef M_PI
#define M_PI        3.14159265358979323846  /* pi */
#endif

//! Fast Fourier Transform analysis of audio signals

//! This class is responsible for calculating the frequency content of any signal that features must be extracted from. It is taken from the Audacity
//! source code. Please note that it does *not* provide any windowing or zero padding functionality.

class fft {
    
    public:
    
    //! constructor
    fft();
    //! deconstructor
    ~fft(); 
    
    //! Calculates the power spectrum of an audio signal
    void powerSpectrum(int start, int half, float *data, int windowSize,float *magnitude,float *phase, float *power, float *avg_power);

    //! Calculates the inverse fast fourier transform of a power spectrum
    void inversePowerSpectrum(int start, int half, int windowSize, float *finalOut,float *magnitude,float *phase);  
};


#endif  

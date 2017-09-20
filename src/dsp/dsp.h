#ifndef RIPL_DSP_H
#define RIPL_DSP_H

#include "waveform.h"

typedef struct RiplDSP {
    RiplDSPWaveTable waveTables[RIPL_DSP_N_WAVEFORMS];
} RiplDSP;

int RiplDSPInit(RiplDSP *dsp, int waveTableSize);
int RiplDSPCleanup(RiplDSP *dsp);

#endif

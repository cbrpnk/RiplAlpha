#ifndef RIPL_STATE_H
#define RIPL_STATE_H

#include "backends/jack.h"
#include "mixer.h"
#include "dsp/dsp.h"

typedef struct RiplState {
    // Contains the number of frame processed
    unsigned long playHead;
    unsigned int bufferSize;
    unsigned int samplingRate;
    float bpm;
    // Bool
    int playing;
    RiplJackBackend *jackBackend;
    RiplMixer *mixer;
    RiplDSP *dsp;
} RiplState;

#endif

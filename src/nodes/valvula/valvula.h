#ifndef RIPL_VALVULA_H
#define RIPL_VALVULA_H

#include <stdint.h>
#include "../../mixer.h"
#include "../../dsp/dsp.h"
#include "../../dsp/waveform.h"
#include "../../dsp/envelope.h"
#include "../../audio_buffer.h"
#include "../../midi_buffer.h"
#include "operator.h"
#include "voice_bank.h"

typedef struct RiplValvula {
    int bufferSize;
    int samplingRate;
    RiplDSP *dsp;
    float level;
    float pan;
    RiplAudioBuffer buffer;
    RiplValvulaOpParams ops[RIPL_VALVULA_N_OP];
    RiplValvulaVoiceBank voiceBank;
} RiplValvula;


int RiplValvulaInit(RiplState *s, RiplValvula *v);
int RiplValvulaCleanup(RiplValvula *v);
int RiplValvulaProcess(RiplAudioBuffer *output, RiplMidiBuffer *midi,
                       void *params);
int RiplValvulaModAmp(RiplValvula *v, RiplValvulaOpName target,
                      RiplValvulaOpName source, float amount);
int RiplValvulaModPhase(RiplValvula *v, RiplValvulaOpName target,
                        RiplValvulaOpName source, float amount);
#endif

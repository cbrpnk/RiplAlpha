#ifndef RIPL_VALVULA_VOICE_H
#define RIPL_VALVULA_VOICE_H

#include "operator.h"

#define RIPL_VALVULA_N_VOICES 10

// A voice, contains the state of every operator
typedef struct RiplValvulaVoice {
    float freq;
    float velocity;
    RiplValvulaOpParams *opParams[RIPL_VALVULA_N_OP];
    RiplValvulaOpState opStates[RIPL_VALVULA_N_OP];
} RiplValvulaVoice;

int RiplValvulaVoiceInit(RiplValvula *v, RiplValvulaVoice *vo);
int RiplValvulaVoiceCleanup(RiplValvulaVoice *vo);

#endif

#ifndef VALVULA_OPERATOR_H
#define VALVULA_OPERATOR_H

#include "../../audio_buffer.h"
#include "../../dsp/dsp.h"
#include "../../dsp/envelope.h"

typedef struct RiplState RiplState;
typedef struct RiplValvula RiplValvula;
typedef struct RiplValvulaVoice RiplValvulaVoice;

typedef enum RiplValvulaOpName {
    RIPL_VALVULA_A = 0,
    RIPL_VALVULA_B,
    RIPL_VALVULA_C,
    RIPL_VALVULA_D,
    RIPL_VALVULA_E,
    RIPL_VALVULA_F,
    RIPL_VALVULA_N_OP
} RiplValvulaOpName;


// Define the tunable parameters of an operator
typedef struct RiplValvulaOpParams {
    int on;
    RiplDSPWaveTable *waveTable;
    // This is the general level of the operator
    float level;
    // The is the amount that goes to the output
    float outputLevel;
    float pan;
    // TODO: Replace this by a ratio/offset(Hz) system
    float freq;
    // Bool
    int ampModOn;
    int phaseModOn;
    // Amount of modulation contribution from other operators or itself
    float ampMod[RIPL_VALVULA_N_OP];
    float phaseMod[RIPL_VALVULA_N_OP];
    RiplDSPEnvParams env;
} RiplValvulaOpParams;


// Defines the internal state of an operator
typedef struct RiplValvulaOpState {
    int phase;
    RiplDSPEnvState env;
    RiplAudioBuffer buffer;
} RiplValvulaOpState;

int RiplValvulaOpParamsInit(RiplValvula *v, RiplValvulaOpParams *p);
int RiplValvulaOpStateInit(RiplValvula *v, RiplValvulaOpState *opState);
int RiplValvulaOpStateCleanup(RiplValvulaOpState *state);
int RiplValvulaOpProcess(RiplValvula *v, RiplValvulaVoice *voice, 
                         RiplValvulaOpName opName);

#endif

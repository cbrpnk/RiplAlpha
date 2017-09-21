#include <math.h>
#include <string.h>
#include "../../audio_buffer.h"
#include "../../state.h"
#include "valvula.h"
#include "operator.h"

int RiplValvulaOpParamsInit(RiplValvula *v, RiplValvulaOpParams *p)
{
    p->on = 0;
    p->waveTable = &(v->dsp->waveTables[RIPL_DSP_SIN]);
    p->level = 1.0f;
    p->outputLevel = 0.0f;
    p->pan = 0.0f;
    p->freq = 120.0f;
    p->ampModOn = 0;
    p->phaseModOn = 0;
    memset(p->ampMod, 0, sizeof(float) * RIPL_VALVULA_N_OP);
    memset(p->phaseMod, 0, sizeof(float) * RIPL_VALVULA_N_OP);
    RiplDSPEnvParamsInit(&(p->env), v->samplingRate);
    return 0;
}

int RiplValvulaOpStateInit(RiplValvula *v, RiplValvulaOpState *opState)
{
    opState->phase = 0;
    RiplDSPEnvStateInit(&(opState->env));
    RiplAudioBufferInit(&(opState->buffer), v->bufferSize,
                        RIPL_AUDIO_BUFFER_MONO);
    return 0;
}

int RiplValvulaOpStateCleanup(RiplValvulaOpState *state)
{
    RiplAudioBufferCleanup(&(state->buffer));
    return 0;
}

int RiplValvulaOpProcess(RiplValvula *v, RiplValvulaVoice *voice, 
                         RiplValvulaOpName opName)
{
    RiplValvulaOpParams *params = voice->opParams[opName];
    RiplValvulaOpState *state = &(voice->opStates[opName]);
    
    RiplAudioBufferClear(&(state->buffer));
    
    for(int i=0; i<v->buffer.size; ++i) {
        
        // Calculate Amplitude modulation contribution
        float amp = 1.0f;
        if(params->ampModOn) {
            amp = 0.0f;
            for(int j=0; j<RIPL_VALVULA_N_OP; ++j) {
                amp += params->ampMod[j] * voice->opStates[j].buffer.left[i];
            }
        }
        
        // Calculate Phase modulation contribution
        int phase = state->phase;
        if(params->phaseModOn) {
            for(int j=0; j<RIPL_VALVULA_N_OP; ++j) {
                phase += params->phaseMod[j] *
                         voice->opStates[j].buffer.left[i] *
                         v->samplingRate;
                while(phase < 0) {
                    phase += v->samplingRate;
                }
                phase %= v->samplingRate;
            }
        }
        
        // Calculate the operator buffer. Used for output and modulation
        state->buffer.left[i] = amp * params->waveTable->table[phase]
                                * params->level;
        if(params->env.on) {
            RiplDSPEnvProcess(&(params->env), &(state->env));
            state->buffer.left[i] *= state->env.value;
        }
        
        // Operator output
        if(params->outputLevel > 0.0f) {
            float left = params->outputLevel * RIPL_PAN_LEFT(params->pan);
            float right = params->outputLevel * RIPL_PAN_RIGHT(params->pan);
            v->buffer.left[i] += left * state->buffer.left[i];
            v->buffer.right[i] += right * state->buffer.left[i];
        }
        
        // Update operator state
        state->phase = (state->phase + (int) round(voice->freq))
                    % v->samplingRate;
    }
    return 0;
}

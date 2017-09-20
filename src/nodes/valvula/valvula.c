#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "valvula.h"
#include "../../audio_buffer.h"
#include "../../midi_buffer.h"
#include "../../state.h"


int RiplValvulaInit(RiplState *s, RiplValvula *v)
{
    v->bufferSize = s->bufferSize;
    v->samplingRate = s->samplingRate;
    v->dsp = s->dsp;
    
    // Global parameters
    v->level = 1.0f;
    v->pan = 0.0f;
    RiplAudioBufferInit(&(v->buffer), s->bufferSize, RIPL_AUDIO_BUFFER_STEREO);
    
    // Operator paramters
    RiplValvulaOpParams *op;
    for(int i=0; i<RIPL_VALVULA_N_OP; ++i) {
        RiplValvulaOpParamsInit(v, (v->ops)+i);
    }
    RiplValvulaVoiceBankInit(v, &(v->voiceBank));
    return 0;
}


int RiplValvulaCleanup(RiplValvula *v)
{
    RiplAudioBufferCleanup(&(v->buffer));
    for(int i=0; i<RIPL_VALVULA_N_VOICES; ++i) {
        RiplValvulaVoiceCleanup(&(v->voiceBank.voices[i]));
    }
    return 0;
}


int RiplValvulaProcess(RiplAudioBuffer *output, RiplMidiBuffer *midi,
                       void *params)
{
    RiplValvula *v = (RiplValvula *) params;
    RiplAudioBufferClear(&(v->buffer));
    
    RiplValvulaVoiceBankAssignMidi(&(v->voiceBank), midi);
    RiplValvulaVoiceBankProcess(v, &(v->voiceBank));
    
    // Output our buffer to mixer channel
    for(int i=0; i<v->buffer.size; ++i) {
        output->left[i] = v->level * RIPL_PAN_LEFT(v->pan) *
                                   v->buffer.left[i];
        output->right[i] = v->level * RIPL_PAN_RIGHT(v->pan) *
                                    v->buffer.right[i];
    }
    
    return 0;
}


int RiplValvulaModAmp(RiplValvula *v, RiplValvulaOpName target,
                      RiplValvulaOpName source, float amount)
{
    v->ops[target].ampModOn = 1;
    v->ops[target].ampMod[source] = amount;
    return 0;
}


int RiplValvulaModPhase(RiplValvula *v, RiplValvulaOpName target,
                        RiplValvulaOpName source, float amount)
{
    v->ops[target].phaseModOn = 1;
    v->ops[target].phaseMod[source] = amount;
    return 0;
}

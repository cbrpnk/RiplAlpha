#include <stdlib.h>
#include <string.h>

#include "mixer.h"
#include "nodes/valvula/valvula.h"
#include "state.h"

int RiplMixerInit(RiplState *state)
{
    for(int i=0; i<RIPL_MIXER_N_CHANNELS; ++i) {
        RiplMixerChannel *ch = (state->mixer->channels)+i;
        ch->on = 0;
        ch->level = 1.0f;
        ch->pan = 0.0f;
        ch->nNodes = 0;
        ch->nodes = NULL;
        ch->audioBuffer = malloc(sizeof(RiplAudioBuffer));
        RiplAudioBufferInit(ch->audioBuffer, state->bufferSize,
                            RIPL_AUDIO_BUFFER_STEREO);
        ch->midiBuffer = malloc(sizeof(RiplMidiBuffer));
        RiplMidiBufferInit(ch->midiBuffer, RIPL_MIXER_MIDI_BUFFER_SIZE);
    }
    return 0;
}

int RiplMixerCleanup(RiplState *state)
{
    for(int i=0; i<RIPL_MIXER_N_CHANNELS; ++i) {
        RiplMixerChannel *ch = (state->mixer->channels)+i;
        for(int j=0; j<ch->nNodes; ++j) {
            RiplNode *n = (ch->nodes)+j;
            switch(n->type) {
                case RIPL_NODE_VALVULA:
                    RiplValvulaCleanup((RiplValvula *) n->params);
                    break;
            }
            free(n->params);
        }
        free(ch->nodes);
        RiplAudioBufferCleanup(ch->audioBuffer);
        free(ch->audioBuffer);
        RiplMidiBufferCleanup(ch->midiBuffer);
        free(ch->midiBuffer);
    }
    return 0;
}

int RiplMixerAddNode(RiplState *state, RiplMixerChannelName channel,
                     RiplNodeType nodeType, RiplNode **node)
{
    if(channel < 0 || channel >= RIPL_MIXER_N_CHANNELS) return 1;
    if(nodeType < 0 || nodeType >= RIPL_NODE_N_TYPES) return 1;
    
    RiplMixerChannel *ch = &(state->mixer->channels[channel]);
    ch->on = 1;
    (ch->nNodes)++;
    ch->nodes = realloc(ch->nodes, (ch->nNodes)*sizeof(RiplNode));
    *node = (ch->nodes)+(ch->nNodes-1);
    (*node)->type = nodeType;
    (*node)->bypass = 0;
    
    switch(nodeType) {
    case RIPL_NODE_VALVULA:
        (*node)->params = malloc(sizeof(RiplValvula));
        RiplValvulaInit(state, (RiplValvula *) (*node)->params);
        (*node)->process = RiplValvulaProcess;
        break;
    default:
        return 1;
    }
    
    return 0;
}

int RiplMixerCallback(RiplState *state, RiplAudioBuffer *output)
{
    RiplMixerChannel *masterCh = &(state->mixer->channels[RIPL_MIXER_MASTER]);
    
    if(state->playing) {
        // Process channels
        for(int i=RIPL_MIXER_0; i<RIPL_MIXER_0 + RIPL_MIXER_N_NORMAL_CHANNELS;
            ++i){
            RiplMixerChannel *ch = (state->mixer->channels)+i;
            if(ch->on) {
                for(int j=0; j<ch->nNodes; ++j) {
                    RiplNode *node = (ch->nodes)+j;
                    if(!(node->bypass)) {
                        node->process(ch->audioBuffer, ch->midiBuffer,
                                      node->params);
                    }
                }
                RiplAudioBufferSum(masterCh->audioBuffer, ch->audioBuffer);
                // TODO: Try to get away with not resetting buffers
                RiplAudioBufferClear(ch->audioBuffer);
                RiplMidiBufferClear(ch->midiBuffer);
            }
        }
        
        // Process master channel
        for(int i=0; i<masterCh->nNodes; ++i) {
            RiplNode *node = (masterCh->nodes)+i;
            if(!(node->bypass)) {
                node->process(masterCh->audioBuffer,
                              masterCh->midiBuffer,  node->params);
            }
        }
    }

    // Copy master buffer to soundcard output
    memcpy(output->left, masterCh->audioBuffer->left,
           masterCh->audioBuffer->size * sizeof(float));
    memcpy(output->right, masterCh->audioBuffer->right,
           masterCh->audioBuffer->size * sizeof(float));
    // TODO: Try to get away with not resetting buffer
    RiplAudioBufferClear(masterCh->audioBuffer);
    
    return 0;
}

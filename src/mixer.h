#ifndef RIPL_MIXER_H
#define RIPL_MIXER_H

#include "audio_buffer.h"
#include "midi_buffer.h"

// Forward declarations
typedef struct RiplState RiplState;
typedef struct RiplMixerChannel RiplMixerChannel;

typedef enum RiplNodeType {
    RIPL_NODE_VALVULA,       // Synth
    RIPL_NODE_MIDI_PLAYER,
    RIPL_NODE_SAMPLER,
    RIPL_NODE_EQ,
    RIPL_NODE_REVERBE,
    RIPL_NODE_COMPRESSOR,
    RIPL_NODE_DISTO,
    RIPL_NODE_DELAY,
    RIPL_NODE_LIMITER,
    RIPL_NODE_N_TYPES
} RiplNodeType;

// Represent an element in a MixerChannel signal chain
typedef struct RiplNode {
    RiplNodeType type;
    // Bool
    int bypass;
    // Pointer to a struct with specific data that defines the node
    // will be passed along with each call to the process function pointer
    // below.
    void *params;
    // We have a function pointer to the function that should process the 
    // signal for this type of nodes. It is part of the the Node stuct becuase
    // we don't want to have a code that runs in the audio loop in order to 
    // discriminate the correct function for the NodeType. In this case the
    // the function is set once at creation time.
    int (*process)(RiplAudioBuffer *output, RiplMidiBuffer *midi, void *params);
} RiplNode;

typedef enum RiplMixerChannelName {
    #define RIPL_MIXER_N_NORMAL_CHANNELS 32
    RIPL_MIXER_MASTER,
    RIPL_MIXER_0, RIPL_MIXER_1, RIPL_MIXER_2, RIPL_MIXER_3, RIPL_MIXER_4,
    RIPL_MIXER_5, RIPL_MIXER_6, RIPL_MIXER_7, RIPL_MIXER_8, RIPL_MIXER_9,
    RIPL_MIXER_10, RIPL_MIXER_11, RIPL_MIXER_12, RIPL_MIXER_13, RIPL_MIXER_14,
    RIPL_MIXER_15, RIPL_MIXER_16, RIPL_MIXER_17, RIPL_MIXER_18, RIPL_MIXER_19,
    RIPL_MIXER_20, RIPL_MIXER_21, RIPL_MIXER_22, RIPL_MIXER_23, RIPL_MIXER_24,
    RIPL_MIXER_25, RIPL_MIXER_26, RIPL_MIXER_27, RIPL_MIXER_28, RIPL_MIXER_29,
    RIPL_MIXER_30, RIPL_MIXER_31,
    RIPL_MIXER_N_CHANNELS
} RiplMixerChannelName;

typedef struct RiplMixerChannel {
    // Bool
    int on;
    // TODO: Make this dB such that 0 is 0dB
    float level;
    // From -1 = left, 1 = right
    float pan;
    // Signal chain nodes, nodes are processed in the order they appear
    unsigned int nNodes;
    RiplNode *nodes;
    // The Nodes in this channel act on those audioBuffer/midiBuffer.
    RiplAudioBuffer *audioBuffer;
    #define RIPL_MIXER_MIDI_BUFFER_SIZE 100
    RiplMidiBuffer *midiBuffer;
} RiplMixerChannel;

typedef struct RiplMixer {
    RiplMixerChannel channels[RIPL_MIXER_N_CHANNELS];
} RiplMixer;

int RiplMixerInit(RiplState *state);
int RiplMixerCleanup(RiplState *state);
int RiplMixerAddNode(RiplState *state, RiplMixerChannelName channel,
                     RiplNodeType nodeType, RiplNode **node);
// Called by the audio backend
int RiplMixerCallback(RiplState *state, RiplAudioBuffer *output);

#endif

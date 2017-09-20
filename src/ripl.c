#include <string.h>
#include <stdlib.h>
#include "ripl.h"

int RiplInit(RiplState *state)
{
    // TODO: Set those dynamically
    state->mixer = malloc(sizeof(RiplMixer));
    state->jackBackend = malloc(sizeof(RiplJackBackend));
    state->dsp = malloc(sizeof(RiplDSP));
    state->bufferSize = 1024;
    state->playing = 0;
    strncpy(state->jackBackend->name, "Headroom",
            sizeof(state->jackBackend->name));
    RiplMixerInit(state);
    RiplJackInit(state);
    RiplDSPInit(state->dsp, state->samplingRate);
    return 0;
}

int RiplCleanup(RiplState *state)
{
    RiplJackShutdown(state);
    RiplMixerCleanup(state);
    RiplDSPCleanup(state->dsp);
    free(state->dsp);
    free(state->mixer);
    free(state->jackBackend);
    return 0;
}

int RiplPlay(RiplState *state)
{
    state->playing = 1;
    return 0;
}

int RiplPause(RiplState *state)
{
    state->playing = 0;
    return 0;
}

int RiplStop(RiplState *state)
{
    state->playing = 0;
    // TODO: Reset time here
    return 0;
}

#ifndef RIPL_JACK_H
#define RIPL_JACK_H

#include "jack/jack.h"

typedef struct RiplState RiplState;

typedef struct RiplJackBackend {
    char name[255];
    jack_port_t *leftOut;
    jack_port_t *rightOut;
    jack_client_t *client;
} RiplJackBackend;

int   RiplJackInit(RiplState *state);
float RiplJackGetCPULoad();
int   RiplJackAudioCallback(const jack_nframes_t nFrames, void *args);
void  RiplJackShutdownCallback(void *args);
void  RiplJackShutdown(RiplState *state);

#endif

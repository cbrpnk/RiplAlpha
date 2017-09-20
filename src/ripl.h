#ifdef __cplusplus
extern "C" {
#endif
#ifndef RIPL_H
#define RIPL_H

#include "mixer.h"
#include "state.h"
#include "nodes/valvula/valvula.h"


int RiplInit(RiplState *state);
int RiplCleanup(RiplState *state);

int RiplPlay(RiplState *state);
int RiplPause(RiplState *state);
int RiplStop(RiplState *state);


#endif
#ifdef __cplusplus
}
#endif

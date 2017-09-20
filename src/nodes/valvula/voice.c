#include "valvula.h"
#include "voice.h"
#include "operator.h"


int RiplValvulaVoiceInit(RiplValvula *v, RiplValvulaVoice *vo)
{
    vo->freq = 0.0f;
    vo->velocity = 0.0f;
    for(int i=0; i<RIPL_VALVULA_N_OP; ++i) {
        vo->opParams[i] = v->ops + i;
        RiplValvulaOpStateInit(v, vo->opStates + i);
    }
    return 0;
}


int RiplValvulaVoiceCleanup(RiplValvulaVoice *vo)
{
    for(int i=0; i<RIPL_VALVULA_N_OP; ++i) {
        RiplValvulaOpStateCleanup(&(vo->opStates[i]));
    }
    return 0;
}

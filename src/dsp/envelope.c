#include "envelope.h"


int RiplDSPEnvParamsInit(RiplDSPEnvParams *p, unsigned int samplingRate)
{
    p->on = 1;
    p->loop = 0;
    p->samplingRate = samplingRate;
    p->attackTime = 200.0f;
    p->attackValue = 1.0f;
    p->decayTime = 100.0f;
    p->sustainValue = 0.7f;
    p->releaseTime = 10.0f;
    return 0;
}
    

int RiplDSPEnvStateInit(RiplDSPEnvState *s)
{
    s->currentFrame = 0;
    s->stage = RIPL_VALVULA_ENV_ATTACK;
    s->value = 0.0f;
    s->delta = 0.0f;
    return 0;
}


int RiplDSPEnvAttack(RiplDSPEnvParams *p, RiplDSPEnvState *s)
{
    if(p->on) {
        s->value = 0.0f;
        s->currentFrame = 0;
        // Adding epsilon to prevents division by 0
        s->stage = RIPL_VALVULA_ENV_ATTACK;
        // We add a small amount the prevent devision by 0
        s->delta = p->attackValue / (p->attackTime * 0.001 * 
                   ((float) p->samplingRate) + 0.00001);
    }
    return 0;
}


int RiplDSPEnvRelease(RiplDSPEnvParams *p, RiplDSPEnvState *s)
{
    if(p->on) {
        s->stage = RIPL_VALVULA_ENV_RELEASE;
        s->delta = 0.0f; // TODO
    }
    return 0;
}


int RiplDSPEnvProcess(RiplDSPEnvParams *p, RiplDSPEnvState *s)
{
    // Exit early
    if(s->stage == RIPL_VALVULA_ENV_ENDED || !(p->on)) {
        return 0;
    }
    
    // In milliseconds
    float time = ((float) s->currentFrame / p->samplingRate) * 1000.0f;
    
    // Set state
    if(s->stage == RIPL_VALVULA_ENV_ATTACK && (time >= p->attackTime)) {
        s->stage = RIPL_VALVULA_ENV_DECAY;
        // We add a small amount to prevent division by 0
        s->delta = (p->sustainValue - p->attackValue)
                     / (p->decayTime * 0.001 * p->samplingRate + 0.00001);
    } else if(s->stage == RIPL_VALVULA_ENV_DECAY
              && time >= (p->attackTime + p->decayTime)) {
        if(p->loop) {
            RiplDSPEnvAttack(p , s);
        } else {
            s->stage = RIPL_VALVULA_ENV_SUSTAIN;
            s->delta = 0.0f;
        }
    } else if(s->stage == RIPL_VALVULA_ENV_RELEASE && time >= 0.0f) {
        // TODO condition
        s->stage = RIPL_VALVULA_ENV_ENDED;
        s->value = 0.0f;
    }
    
    s->value += s->delta;
    ++(s->currentFrame);
    return 0;
}

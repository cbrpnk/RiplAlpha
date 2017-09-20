#ifndef RIPL_DSP_ENVELOPE
#define RIPL_DSP_ENVELOPE

typedef enum RiplDSPEnvStage {
    RIPL_VALVULA_ENV_ATTACK,
    RIPL_VALVULA_ENV_DECAY,
    RIPL_VALVULA_ENV_SUSTAIN,
    RIPL_VALVULA_ENV_RELEASE,
    RIPL_VALVULA_ENV_ENDED,
} RiplDSPEnvStage;


// Envelope tunable parameters
typedef struct RiplDSPEnvParams {
    // Bool
    int on;
    // Bool
    int loop;
    int samplingRate;
    // Times are in milliseconds
    float attackTime;
    float attackValue;
    float decayTime;
    float sustainValue;
    float releaseTime;
} RiplDSPEnvParams;


// Envelope internal state
typedef struct RiplDSPEnvState {
    // This is incremented each time Process is called in order to keep
    // track of time
    int currentFrame;
    RiplDSPEnvStage stage;
    // Current output value of the evelope
    float value;
    // By how much the value should change on each call to Process
    float delta;
} RiplDSPEnvState;


int RiplDSPEnvParamsInit(RiplDSPEnvParams *p, unsigned int samplingRate);
int RiplDSPEnvStateInit(RiplDSPEnvState *s);
// Call this on key press
int RiplDSPEnvAttack(RiplDSPEnvParams *p, RiplDSPEnvState *s);
// Call This on key release
int RiplDSPEnvRelease(RiplDSPEnvParams *p, RiplDSPEnvState *s);
// Call this to update the current value of the envelope
int RiplDSPEnvProcess(RiplDSPEnvParams *p, RiplDSPEnvState *s);

#endif

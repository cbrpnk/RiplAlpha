#ifndef RIPL_AUDIO_BUFFER_H
#define RIPL_AUDIO_BUFFER_H

// Tranforms a pan value[-1, 1] into a scalar multiplier
#define RIPL_PAN_RIGHT(pan) (1.0f-(pan*-1.0f*(pan<0.0f)))
#define RIPL_PAN_LEFT(pan) (1.0f-(pan*(pan>0.0f)))

typedef enum RiplAudioBufferType {
    RIPL_AUDIO_BUFFER_MONO,
    RIPL_AUDIO_BUFFER_STEREO
} RiplAudioBufferType;

typedef struct RiplAudioBufferTag {
    RiplAudioBufferType type;
    unsigned int size;
    // If the type is RIPL_AUDIO_BUFFER_MONO, both pointers reference
    // the same memory location
    float *left;
    float *right;
} RiplAudioBuffer;

int RiplAudioBufferInit(RiplAudioBuffer *buff, unsigned int size,
                        RiplAudioBufferType type);
int RiplAudioBufferCleanup(RiplAudioBuffer *buff);
int RiplAudioBufferClear(RiplAudioBuffer *buff);
int RiplAudioBufferSum(RiplAudioBuffer *target, RiplAudioBuffer *source);

#endif

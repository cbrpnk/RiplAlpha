#include <stdlib.h>
#include <string.h>
#include "audio_buffer.h"

int RiplAudioBufferInit(RiplAudioBuffer *buff, unsigned int size,
                        RiplAudioBufferType type)
{
    buff->type = type;
    buff->size = size;
    buff->left = calloc(sizeof(float), size);
    if(buff->type == RIPL_AUDIO_BUFFER_STEREO) {
        buff->right = calloc(sizeof(float), size);
    } else {
        buff->right = buff->left;
    }
    RiplAudioBufferClear(buff);
    return 0;
}

int RiplAudioBufferCleanup(RiplAudioBuffer *buff)
{
    free(buff->left);
    if(buff->type == RIPL_AUDIO_BUFFER_STEREO) {
        free(buff->right);
    }
    return 0;
}

int RiplAudioBufferClear(RiplAudioBuffer *buff)
{
    memset(buff->left, 0, buff->size * sizeof(float));
    if(buff->type == RIPL_AUDIO_BUFFER_STEREO) {
        memset(buff->right, 0, buff->size * sizeof(float));
    }
    return 0;
}

int RiplAudioBufferSum(RiplAudioBuffer *target, RiplAudioBuffer *source)
{
    if(target->type != source->type) return 1;
    
    for(int i=0; i<target->size && i<source->size; ++i) {
        target->left[i] += source->left[i];
        if(target->type == RIPL_AUDIO_BUFFER_STEREO) {
            target->right[i] += source->right[i];
        }
    }
    return 0;
}

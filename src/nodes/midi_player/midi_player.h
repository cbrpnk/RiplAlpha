#ifndef RIPL_MIDI_PLAYER_H
#define RIPL_MIDI_PLAYER_H

#include "../../mixer.h"
#include "../../audio_buffer.h"
#include "../../midi_buffer.h"

typedef struct RiplMidiPlayer {
    int nMidiBuffs;
    RiplMidiBuffer *midiBuffer[];
} RiplMidiPlayer;

int RiplMidiPlayerInit(RiplState *s, RiplMidiPlayer *mp);
int RiplMidiPlayerCleanup(RiplMidiPlayer *mp);
int RiplMidiPlyaerProcess(RiplAudioBuffer *output, RiplMidiBuffer *midi,
                          void *params);

#endif

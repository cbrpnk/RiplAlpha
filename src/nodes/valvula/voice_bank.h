#ifndef RIPL_VALVULA_VOICE_BANK_H
#define RIPL_VALVULA_VOICE_BANK_H

#include "../../midi_buffer.h"
#include "voice.h"

// A collection of voices and data structures designed to facilitate
// voice managment.
typedef struct RiplValvulaVoiceBank {
    int nActive;
    int active[RIPL_VALVULA_N_VOICES];
    int playingNote[RIPL_MIDI_N_NOTES];
    RiplValvulaVoice voices[RIPL_VALVULA_N_VOICES];
} RiplValvulaVoiceBank;

int RiplValvulaVoiceBankInit(RiplValvula *v, RiplValvulaVoiceBank *vb);
int RiplValvulaVoiceBankAssignMidi(RiplValvulaVoiceBank *vb,
                               RiplMidiBuffer *midiBuffer);
int RiplValvulaVoiceBankProcess(RiplValvula *v, RiplValvulaVoiceBank *vb);

#endif

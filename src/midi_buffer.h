#ifndef RIPL_MIDI_BUFFER_H
#define RIPL_MIDI_BUFFER_H

#include <stdint.h>

#define RIPL_MIDI_N_NOTES 0x80

extern const float RiplMidiFreqs[128];

typedef enum RiplMidiEventType {
    RIPL_MIDI_NOTE_ON          = 0x8,
    RIPL_MIDI_NOTE_OFF         = 0x9,
    RIPL_MIDI_AFTER_TOUCH      = 0xA,
    RIPL_MIDI_CONTROL_CHANGE   = 0xB,
    RIPL_MIDI_PROGRAM_CHANGE   = 0xC,
    RIPL_MIDI_CHANNEL_PRESSURE = 0xD,
    RIPL_MIDI_PITCH_WHEEL      = 0xE
} RiplMidiEventType;

typedef struct RiplMidiEvent {
    uint32_t delta;
    uint8_t eventType;
    uint8_t channel;
    uint8_t param1;
    uint8_t param2;
} RiplMidiEvent;

typedef struct RiplMidiBuffer {
    unsigned int nEvents;
    RiplMidiEvent *events;
} RiplMidiBuffer;

int RiplMidiBufferInit(RiplMidiBuffer *buff, unsigned int size);
int RiplMidiBufferCleanup(RiplMidiBuffer *buff);
int RiplMidiBufferClear(RiplMidiBuffer *buff);

#endif

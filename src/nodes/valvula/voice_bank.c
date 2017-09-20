#include "valvula.h"
#include "voice_bank.h"

int RiplValvulaVoiceBankInit(RiplValvula *v, RiplValvulaVoiceBank *vb)
{
    // Voice bank
    vb->nActive = 0;
    for(int i=0; i<RIPL_VALVULA_N_VOICES; ++i) {
        vb->active[i] = 0;
    }
    for(int i=0; i<128; ++i) {
        vb->playingNote[i] = 0;
    }
    
    // Voices
    for(int i=0; i<RIPL_VALVULA_N_VOICES; ++i) {
        RiplValvulaVoiceInit(v, vb->voices + i);
    }
    return 0;
}

int RiplValvulaVoiceBankAssignMidi(RiplValvulaVoiceBank *vb,
                                   RiplMidiBuffer *midiBuffer)
{
    RiplValvulaVoice *vo;
    RiplMidiEvent *midiE;
    for(int i=0; i<midiBuffer->nEvents; ++i) {
        midiE = (midiBuffer->events)+i;
        switch(midiE->eventType) {
        case RIPL_MIDI_NOTE_ON:
            for(int j=0; j<RIPL_VALVULA_N_VOICES; ++j) {
                if(vb->active[j] == 0) {
                    vb->active[j] = 1;
                    vb->playingNote[midiE->param1] = j;
                    vo = vb->voices + j;
                    vo->freq = RiplMidiFreqs[midiE->param1];
                    vo->velocity = midiE->param2;
                    // TODO: Maybe have a function to do the following
                    // Like BankSetAttack() or something
                    for(int k=0; k<RIPL_VALVULA_N_OP; ++k) {
                        RiplDSPEnvAttack(&(vo->opParams[k]->env),
                                         &(vo->opStates[k].env));
                    }
                    break;
                }
            }
            break;
        case RIPL_MIDI_NOTE_OFF:
            // TODO: envRelease for voice and operators
            break;
        }
    }
    return 0;
}


int RiplValvulaVoiceBankProcess(RiplValvula *v, RiplValvulaVoiceBank *vb)
{
    for(int i=0; i<RIPL_VALVULA_N_VOICES; ++i) {
        if(v->voiceBank.active[i]) {
            for(int j=0; j<RIPL_VALVULA_N_OP; ++j) {
                if((v->ops+j)->on) {
                    RiplValvulaOpProcess(v, v->voiceBank.voices + i, j);
                }
            }
        }
    }
    return 0;
}

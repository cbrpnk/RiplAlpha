#include <stdlib.h>
#include <string.h>
#include "../state.h"
#include "dsp.h"

int RiplDSPInit(RiplDSP *dsp, int waveTableSize)
{
    // The size of the tables is the sampling rate so that we can store
    // 1 second of a wave in a table
    
    RiplDSPWaveTable *wt = &(dsp->waveTables[RIPL_DSP_SIN]);
    wt->waveform = RIPL_DSP_SIN;
    wt->size = waveTableSize;
    wt->table = malloc(waveTableSize * sizeof(float));
    RiplDSPGenSinTable(wt);
    
    wt = &(dsp->waveTables[RIPL_DSP_SQUARE]);
    wt->waveform = RIPL_DSP_SQUARE;
    wt->size = waveTableSize;
    wt->table = malloc(waveTableSize * sizeof(float));
    RiplDSPGenSquareTable(wt);
    
    wt = &(dsp->waveTables[RIPL_DSP_SAW]);
    wt->waveform = RIPL_DSP_SAW;
    wt->size = waveTableSize;
    wt->table = malloc(waveTableSize * sizeof(float));
    RiplDSPGenSawTable(wt);
    
    wt = &(dsp->waveTables[RIPL_DSP_TRI]);
    wt->waveform = RIPL_DSP_TRI;
    wt->size = waveTableSize;
    wt->table = malloc(waveTableSize * sizeof(float));
    RiplDSPGenTriTable(wt);
    
    return 0;
}

int RiplDSPCleanup(RiplDSP *dsp)
{
    free(dsp->waveTables[RIPL_DSP_SIN].table);
    free(dsp->waveTables[RIPL_DSP_SQUARE].table);
    free(dsp->waveTables[RIPL_DSP_SAW].table);
    free(dsp->waveTables[RIPL_DSP_TRI].table);
    return 0;
}


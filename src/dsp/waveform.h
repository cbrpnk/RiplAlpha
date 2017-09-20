#ifndef RIPL_DSP_WAVEFORM_H
#define RIPL_DSP_WAVEFORM_H

typedef enum RiplDSPWaveform {
    RIPL_DSP_SIN = 0,
    RIPL_DSP_SQUARE,
    RIPL_DSP_SAW,
    RIPL_DSP_TRI,
    RIPL_DSP_N_WAVEFORMS
} RiplDSPWaveform;

typedef struct RiplDSPWaveTable {
    RiplDSPWaveform waveform;
    int size;
    float *table;
} RiplDSPWaveTable;

int RiplDSPGenSinTable(RiplDSPWaveTable *wt);
int RiplDSPGenSquareTable(RiplDSPWaveTable *wt);
int RiplDSPGenSawTable(RiplDSPWaveTable *wt);
int RiplDSPGenTriTable(RiplDSPWaveTable *wt);

#endif

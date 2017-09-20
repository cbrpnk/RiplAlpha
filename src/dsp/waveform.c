#include <math.h>
#include "waveform.h"

int RiplDSPGenSinTable(RiplDSPWaveTable *wt)
{
    float period = 1.0f / wt->size;
    for(int i=0; i<wt->size; ++i) {
        wt->table[i] = sin(2.0f * M_PI * i * period);
    }
    return 0;
}

// TODO: Generate waveforms as sum of sines
// TODO: Generate Tx waveforms + noise waveforms
int RiplDSPGenSquareTable(RiplDSPWaveTable *wt)
{
    return 0;
}

int RiplDSPGenSawTable(RiplDSPWaveTable *wt)
{
    return 0;
}

int RiplDSPGenTriTable(RiplDSPWaveTable *wt)
{
    return 0;
}

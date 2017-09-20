#include <stdio.h>
#include "jack.h"
#include "../state.h"
#include "../mixer.h"
#include "../audio_buffer.h"

int RiplJackInit(RiplState *state)
{
    RiplJackBackend *jack = state->jackBackend;
    
	jack_status_t status;
    // TODO: Set client name dynamically
	jack->client = jack_client_open(jack->name, JackNullOption, &status, NULL);
    
    jack_set_buffer_size(jack->client, state->bufferSize);
	state->samplingRate = jack_get_sample_rate(jack->client);
	
	if(jack->client == NULL) {
		printf("jack_client_open Failed\n");
		if(status & JackServerFailed) {
			printf("JACK server failed.\n");
		}
	}
		
	if(status & JackServerStarted) {
		printf("JACK server started\n");
	}
	
	if(status & JackNameNotUnique) {
		printf("Jack name not unique\n");
	}
	
	jack_set_process_callback(jack->client, RiplJackAudioCallback, state);
	jack_on_shutdown(jack->client, RiplJackShutdownCallback, state);
	
	jack->leftOut = jack_port_register(jack->client, "leftOut",
                                       JACK_DEFAULT_AUDIO_TYPE,
                                       JackPortIsOutput, 0);
	jack->rightOut = jack_port_register(jack->client, "rightOut",
                                        JACK_DEFAULT_AUDIO_TYPE,
                                        JackPortIsOutput, 0);
	
	if(jack->leftOut == NULL || jack->rightOut == NULL) {
		printf("No more ports available\n");
	}
	
	if(jack_activate(jack->client)) {
		printf("Could not activate client\n");
	}
	
	const char **ports = jack_get_ports(jack->client, NULL, NULL,
                                        JackPortIsPhysical | JackPortIsInput);
	
	if(jack_connect(jack->client, jack_port_name(jack->leftOut), ports[0])) {
		printf("cannot connect to output port\n");
	}
	
	if(jack_connect(jack->client, jack_port_name(jack->rightOut), ports[1])) {
		printf("cannot connect to output port\n");
	}
}

int RiplJackAudioCallback(const jack_nframes_t nFrames, void *args)
{
    RiplState *state = (RiplState *) args;
    
    RiplAudioBuffer buffer;
    buffer.size = nFrames;
    buffer.left = (float *) jack_port_get_buffer(state->jackBackend->leftOut, 
                                                 nFrames);
	buffer.right = (float *) jack_port_get_buffer(state->jackBackend->rightOut, 
                                                  nFrames);
    
    RiplMixerCallback(state, &buffer);
    return 0;
}

void RiplJackShutdownCallback(void *args)
{
    printf("Jack Server Shutdown\n");
}

float RiplJackGetCPULoad(RiplState *state)
{
    return jack_cpu_load(state->jackBackend->client);
}


void RiplJackShutdown(RiplState *state)
{
    jack_client_close(state->jackBackend->client);
}

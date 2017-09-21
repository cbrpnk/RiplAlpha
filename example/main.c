#include <time.h>
#include <unistd.h>
#include "../src/ripl.h"

/*
int main(int argc, char **argv)
{
    RiplState riplState;
    RiplInit(&riplState);
    
    RiplNode *valvulaNode;
    RiplMixerAddNode(&riplState, RIPL_MIXER_0, RIPL_NODE_VALVULA, &valvulaNode);
    RiplValvula *valvula = (RiplValvula *) valvulaNode->params;
    
    valvula->ops[RIPL_VALVULA_A].on = 1;
    valvula->ops[RIPL_VALVULA_A].freq = 200.0f;
    valvula->ops[RIPL_VALVULA_A].outputLevel = .5f;
    
    // TODO: Remove me start
    // Temporarly set midi buffer here
    RiplMidiEvent *midiMess =
                  riplState.mixer->channels[RIPL_MIXER_0].midiBuffer->events;
    
    riplState.mixer->channels[RIPL_MIXER_0].midiBuffer->nEvents = 2;
    midiMess->delta = 0;
    midiMess->eventType = RIPL_MIDI_NOTE_ON;
    midiMess->channel = 0;
    midiMess->param1 = 30;
    midiMess->param2 = 64;
    
    midiMess = (riplState.mixer->channels[RIPL_MIXER_0].midiBuffer->events)+1;
    midiMess->delta = 0;
    midiMess->eventType = RIPL_MIDI_NOTE_ON;
    midiMess->channel = 0;
    midiMess->param1 = 70;
    midiMess->param2 = 64;
    // TODO: Remove me end
    
    RiplPlay(&riplState);
    for(;;) {
        // TODO: Thread message passing here
        // Interpret messages and change the Ripl state
        sleep(1); // Seconds
    }
    
    RiplCleanup(&riplState);
    return 0;
}
*/


int main(int argc, char **argv)
{
    RiplState riplState;
    RiplInit(&riplState);
    
    RiplNode *valvulaNode;
    RiplMixerAddNode(&riplState, RIPL_MIXER_0, RIPL_NODE_VALVULA, &valvulaNode);
    RiplValvula *valvula = (RiplValvula *) valvulaNode->params;
    
    valvula->ops[RIPL_VALVULA_A].on = 1;
    // TODO: The frequency is set by the midi buffer
    // there should be an option to lock to a specific freq +
    // an offset option
    valvula->ops[RIPL_VALVULA_A].freq = 1400.0f;
    valvula->ops[RIPL_VALVULA_A].outputLevel = .8f;
    RiplValvulaModPhase(valvula, RIPL_VALVULA_B, RIPL_VALVULA_A, 0.05f);
    RiplValvulaModPhase(valvula, RIPL_VALVULA_D, RIPL_VALVULA_A, 0.4f);
    RiplValvulaModPhase(valvula, RIPL_VALVULA_E, RIPL_VALVULA_A, 0.4f);
    
    valvula->ops[RIPL_VALVULA_B].on = 1;
    valvula->ops[RIPL_VALVULA_B].freq = 300.0f;
    valvula->ops[RIPL_VALVULA_B].level = .9f;
    RiplValvulaModPhase(valvula, RIPL_VALVULA_A, RIPL_VALVULA_B, .9f);
    
    valvula->ops[RIPL_VALVULA_C].on = 0;
    valvula->ops[RIPL_VALVULA_C].freq = 1.0f;
    RiplValvulaModPhase(valvula, RIPL_VALVULA_A, RIPL_VALVULA_C, 0.2f);
    RiplValvulaModPhase(valvula, RIPL_VALVULA_B, RIPL_VALVULA_C, 0.5f);
    RiplValvulaModPhase(valvula, RIPL_VALVULA_D, RIPL_VALVULA_C, 0.5f);
    RiplValvulaModPhase(valvula, RIPL_VALVULA_E, RIPL_VALVULA_C, 0.5f);
    
    valvula->ops[RIPL_VALVULA_D].on = 0;
    valvula->ops[RIPL_VALVULA_D].freq = 360.0f;
    valvula->ops[RIPL_VALVULA_D].outputLevel = .6f;
    RiplValvulaModPhase(valvula, RIPL_VALVULA_D, RIPL_VALVULA_D, 0.1f);
    RiplValvulaModPhase(valvula, RIPL_VALVULA_A, RIPL_VALVULA_D, 0.03f);
    RiplValvulaModPhase(valvula, RIPL_VALVULA_B, RIPL_VALVULA_D, 0.01f);
    RiplValvulaModPhase(valvula, RIPL_VALVULA_E, RIPL_VALVULA_D, 0.03f);
    
    valvula->ops[RIPL_VALVULA_E].on = 0;
    valvula->ops[RIPL_VALVULA_E].freq = 1200.0f;
    valvula->ops[RIPL_VALVULA_E].outputLevel = .5f;
    RiplValvulaModAmp(valvula, RIPL_VALVULA_B, RIPL_VALVULA_E, 0.05f);

    // TODO: Remove me start
    // Temporarly set midi buffer here
    RiplMidiEvent *midiMess =
                  riplState.mixer->channels[RIPL_MIXER_0].midiBuffer->events;
    
    riplState.mixer->channels[RIPL_MIXER_0].midiBuffer->nEvents = 2;
    midiMess->delta = 0;
    midiMess->eventType = RIPL_MIDI_NOTE_ON;
    midiMess->channel = 0;
    midiMess->param1 = 40;
    midiMess->param2 = 64;
    
    /*
    midiMess = (riplState.mixer->channels[RIPL_MIXER_0].midiBuffer->events)+1;
    midiMess->delta = 0;
    midiMess->eventType = RIPL_MIDI_NOTE_ON;
    midiMess->channel = 0;
    midiMess->param1 = 70;
    midiMess->param2 = 64;
    */
    // TODO: Remove me end
    
    RiplPlay(&riplState);
    for(;;) {
        // TODO: Thread message passing here
        // Interpret messages and change the Ripl state
        sleep(1); // Seconds
    }
    
    RiplCleanup(&riplState);
    return 0;
}


/*
#define BUFFER_SIZE 1024
int AudioThread()
{
    Ripl ripl(BUFFER_SIZE);
    Graph* graph0 = ripl.AddGraph();
    Master* master = static_cast<Master*>(graph0->AddNode(Node::Type::Master));
    
    Osc* osc0 = static_cast<Osc*>(graph0->AddNode(Node::Type::Osc));
    graph0->ConnectNode(osc0, Osc::Output::Main, master, Master::Input::LeftIn);
    graph0->ConnectNode(osc0, Osc::Output::Main, master, Master::Input::RightIn);
    osc0->SetFrequency(40.0f);
    osc0->SetPhaseModRange(1.0f);
    
    Osc* osc1 = static_cast<Osc*>(graph0->AddNode(Node::Type::Osc));
    graph0->ConnectNode(osc1, Osc::Output::Main, osc0, Osc::Input::Phase);
    osc1->SetWave1(Osc::Wave::Tri);
    osc1->SetFrequency(80.0f);
    osc1->SetVolume(1.0f);
    
    Osc* osc2 = static_cast<Osc*>(graph0->AddNode(Node::Type::Osc));
    graph0->ConnectNode(osc2, Osc::Output::Main, osc1, Osc::Input::Phase);
    osc2->SetFrequency(1280.0f);
    osc2->SetWave1(Osc::Wave::Tri);
    
    Osc* osc3 = static_cast<Osc*>(graph0->AddNode(Node::Type::Osc));
    graph0->ConnectNode(osc3, Osc::Output::Main, osc1, Osc::Input::Amplitude);
    graph0->ConnectNode(osc3, Osc::Output::Main, osc2, Osc::Input::Amplitude);
    graph0->ConnectNode(osc3, Osc::Output::Main, osc1, Osc::Input::Phase);
    osc3->SetFrequency(1.0f);
    
    //graph0->RemoveNode(osc3);
    
    // TODO: Make frequency float and not int
    
    ripl.Play();
    
    // Don't end thread
	for(;;) {
		sleep(1);
	}
    return 0;
}
*/

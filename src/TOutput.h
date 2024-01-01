//
//TOutput.h
//
#ifndef TOUTPUT_H
#define TOUTPUT_H

#include <stdio.h>
#include <Beep.h>
#include <Looper.h>
#include <MidiSynth.h>
#include <MidiProducer.h>
#include <MidiConsumer.h>
#include <Synth.h>
#include <View.h>

class BLooper;
class BMidiSynth;


class TOutput : public BLooper
{ 
public: 
            TOutput(BView* view,const char* name); 
    void    MessageReceived(BMessage* message);
    void	SetTarget(BLooper* looper);
    void	HandleData(int	CH, int number, int data);
    bool	QuitRequested();
    
    
    char* mididistname;
    BMidiConsumer* mididistination;
	BMidiLocalProducer* midiout;
	BMidiSynth song;
	int statusofctrl[3];
	int status[8];
	int	outputstatus[4];//	type of output device; 1: Bsynth
	bool playing;					//	-10:percussion of Bsynth (CH10)
						//	-126:midi1
						//  -127:midi2
	
	
private:
	BLooper* targetlooper;
	int	voldata[8][16];
	int playingdata[8];
	BView*	target;
	
	int velosity[8];
	
	
	int	ctrldata[3];
	float velfactor[3];
	
	
}; 

#endif

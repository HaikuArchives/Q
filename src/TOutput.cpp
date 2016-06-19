//
//TOutput.cpp
//



#include "TOutput.h"
#include <Message.h>
#include <Application.h>
#include <AppFileInfo.h>
#include <Bitmap.h>
#include <File.h>
#include <Roster.h>
#include <MidiRoster.h>
//#include <iostream.h>

TOutput :: TOutput(BView* view, const char* name)
    		 : BLooper(NULL, B_REAL_TIME_PRIORITY)
{ 
	playing=false;
	target=view;
	Run();
	playingdata[0]=-1;
   	//preparing midi
   	BBitmap* largeIcon = new BBitmap(BRect(0,0,31,31), B_CMAP8);
	BBitmap* miniIcon = new BBitmap(BRect(0,0,15,15), B_CMAP8);
	
	BString midioutname;
   	midioutname << name << " output";
   	midiout = new BMidiLocalProducer(midioutname.String());
   	if (midiout) midiout->Register();
	
   	app_info appinfo;
	status_t err;
	BMessage msg;
	
	err = be_app->GetAppInfo(&appinfo);
	if (err == B_OK) {
		BFile file(&(appinfo.ref), B_READ_ONLY);
		err = file.InitCheck();
		if (err == B_OK) {
			BAppFileInfo appfileinfo(&file);
			err = appfileinfo.InitCheck();
			if (err == B_OK) {
				appfileinfo.GetIcon(largeIcon, B_LARGE_ICON);
				appfileinfo.GetIcon(miniIcon, B_MINI_ICON);
			}
		}
	}

	
	if (midiout && midiout->GetProperties(&msg) == B_OK)
	{
		(&msg)->AddData("be:large_icon", 'ICON', largeIcon->Bits(),
		largeIcon->BitsLength());
		(&msg)->AddData("be:mini_icon", 'MICN', miniIcon->Bits(),
		miniIcon->BitsLength());
		midiout->SetProperties(&msg);
	} 
	
	mididistination=NULL;
	mididistname="none";
   	status[1] = B_SQUARE_WAVE; 
	status[2]  = B_SAWTOOTH_WAVE; 
	status[3]  = B_STEEL_DRUMS; 
	// GM instrument 
	
	statusofctrl[1]=2;
	statusofctrl[2]=2;
	statusofctrl[3]=4;
	velfactor[1]=1;
	velfactor[2]=1;
	outputstatus[1]=0;
	outputstatus[2]=0;
	outputstatus[3]=0;

  	song.EnableInput(true, true); 
   	for (int i=1;i<9;i++)velosity[i]=127;
   	song.ProgramChange(1, status[1]);
	song.ProgramChange(2, status[2]);
	song.ProgramChange(3, status[3]); 
	//end of preparing midi  
	
}

void	TOutput::SetTarget(BLooper* looper)
{
	targetlooper=looper;
}

void    TOutput::MessageReceived(BMessage* message)
{
	int i;
	BMessage* msg;
	
	switch(message->what)
	{
	
		case 'volm':
						HandleData(message->FindInt16("CH"),message->FindInt16("No."),message->FindInt32("data"));
//						cout << "\n Channel = " << message->FindInt16("CH");
//						cout << "\n No.     = " << message->FindInt16("No.");
//						cout << "\n Ndata   = " << message->FindInt32("data");
//						cout << "\n " ;
//						cout << flush;			

					break;
	
		case 'non0':int dataofC;
					playingdata[3]=voldata[3][message->FindInt16("No.")];
					if(playingdata[3]>=0)dataofC=playingdata[3];
					else dataofC=0;
					if(status[3]==-7){//Clock
						msg=new BMessage('tem2');
						msg->AddInt32("data",voldata[3][message->FindInt16("No.")]);
						targetlooper->PostMessage(msg);
						delete msg;
					}else if(status[3]==-10){//percussion
						if(!(playingdata[3]==-1)){
							song.NoteOn(10,playingdata[3], 127);
							outputstatus[3]=10;
						} 
					}else if(status[3]==-1){//Velosity of A
						velosity[1]=dataofC;
						velosity[2]=127;
					}else if(status[3]==-2){//Velosity of B
						velosity[1]=127;
						velosity[2]=dataofC;
					}else if(status[3]==-3){//Velosity of A, B
						velosity[1]=dataofC;
						velosity[2]=dataofC;
					}else if(status[3]==-127){
						midiout->SprayNoteOn(3-1,playingdata[3], 127);
						outputstatus[3]=-127;
					}else if(!(playingdata[3]==-1)){
						song.NoteOn(3,playingdata[3], 127);
						outputstatus[3]=1;
					}
				 	int v;
					
					for(i=1;i<=2;i++)
					{
						playingdata[i]=voldata[i][message->FindInt16("No.")];
						if(!(playingdata[i]==-1))
						{
							if(status[3]<0 && status[3]>=-3)
							{
								if (statusofctrl[i]==1) v=velosity[i]*ctrldata[i]/127;
								else v=velosity[i];
								if( status[i] == -10)
								{
									song.NoteOn(10,playingdata[i], v);
									outputstatus[i]=-10;
								}
								else if(status[i]==-127)
								{
									midiout->SprayNoteOn(i-1,playingdata[i], v);
									outputstatus[i]=-127; 
								}
								else
								{
									 song.NoteOn(i,playingdata[i], v);
									 outputstatus[i]=1;
								}
							}
							else
							{
								// Note wird gespielt   
								if (statusofctrl[i]==1) v=127*ctrldata[i]/127;
								else v=127;
								if(status[i]==-10)
								{
									song.NoteOn(10,playingdata[i], v);
									outputstatus[i]=-10;
								}
								else if(status[i]==-127)
								{
									midiout->SprayNoteOn(i-1,playingdata[i], v);
									outputstatus[i]=-127; 
//									midiout->SprayNoteOn(i,playingdata[i], v);
									// Hier wird Note gespielt                                             ****************************
//									cout << "\n Channel  = " << i;
//									cout << "\n data     = " << playingdata[i];
//									cout << "\n velocity = " << v;
//									cout << "\n " ;
//									cout << flush;			
								}
								else
								{
									song.NoteOn(i,playingdata[i], v);
									outputstatus[i]=1;
								}
							}
						}
					}
					break;
   		
		case 'nof0':for(i=1;i<=3;i++)
		{
						if(!(playingdata[i]==-1))
						{
										if 	(outputstatus[i] ==    1) 	song.NoteOff( i,playingdata[i], 127);
							else 	if	(outputstatus[i] ==  -10) 	song.NoteOff(10,playingdata[i], 127); 
							else 	if	(outputstatus[i] == -127)
							{
									midiout->SprayNoteOff(i-1,playingdata[i], 127);
//									midiout->SprayNoteOff(i,playingdata[i], 127);
									// Hier wird Note ausgeschaltet                                          *************************
							}
						}
						outputstatus[i]=0;
					}
				 	break;
	
		case 'strt':playing=true;
					break;
	
		case 'stop':playing=false;
					msg=new BMessage('tem2');
					msg->AddInt32("data",0);
					targetlooper->PostMessage(msg);
					delete msg;
					break;
	
		case 'msup':if(!playing)
		{
						for(i=1;i<=3;i++)
						{
							if(!(playingdata[0]==-1))
							{
											if(outputstatus[i]	==	   1)		song.NoteOff( i,playingdata[0], 127);
								else 	if(outputstatus[i]	==	 -10)		song.NoteOff(10,playingdata[0], 127); 
								else 	if(outputstatus[i]	==	-127)
								{
									midiout->SprayNoteOff(i-1,playingdata[0], 127);
								}
							  outputstatus[i]=0;
							}
							
						}
					}
					;break;
		
		case 'inst':if (message->FindInt16("CH")==3)
		{
						if(status[3]==-7)
						{
							msg=new BMessage('tem2');
							msg->AddInt32("data",0);
							targetlooper->PostMessage(msg);
							delete msg;
						}
					}
					status[message->FindInt16("CH")]=message->FindInt16("inst");
					if (message->FindInt16("inst")>=0) song.ProgramChange(message->FindInt16("CH"), message->FindInt16("inst"));
					break;
	
		case 'ctrl':i=message->FindInt16("CH");
					statusofctrl[i]=message->FindInt16("data");
					if(statusofctrl[i]==2)
					{
						if(status[i]==-127)
						{
								midiout->SprayPitchBend(i-1,0,ctrldata[i]);
						}
						else song.PitchBend(i,0,ctrldata[i]);
					}
					else
					{
						if(status[i]==-127)
						{
								midiout->SprayPitchBend(i-1,0,0x40);
						}
						else song.PitchBend(i,0,0x40);
					}
					break;
					
		case 'rvrb':
					statusofctrl[3]=message->FindInt16("Reverb");
					be_synth->SetReverb((reverb_mode)statusofctrl[3]);
					break;
	
		case 'ctra': //Message from Ctrl A knob
					ctrldata[1]=message->FindInt32("data");
					if(ctrldata[1]<0) ctrldata[1]=0;
					if(statusofctrl[1]==2){
						if (status[2]==-127){
							midiout->SprayPitchBend(1-1,0,ctrldata[1]);
						}
						else song.PitchBend(1,0,ctrldata[1]);
					}
					break;
		
		case 'ctrb': //Message from Ctrl B knob
					ctrldata[2]=message->FindInt32("data");
					if(ctrldata[2]<0) ctrldata[2]=0;
					if(statusofctrl[2]==2){
						if (status[2]==-127){
							midiout->SprayPitchBend(2-1,0,ctrldata[2]);
						}
						song.PitchBend(2,0,ctrldata[2]);
					}
					break;
		
		case 'mout':const char* name;
					message->FindString("name",&name);
					if (! strcmp("none", name))
					{					
						if(mididistination)
						{
							midiout->Disconnect(mididistination);
							mididistination->Release();
							mididistination=NULL;
						}
						break;
					}
					
					BMidiRoster* roster = BMidiRoster::MidiRoster();
					if (! roster) 
					{
					printf(("Can't find MIDI roster\n"));
					break;
					}
					
					int32 id=0;
					BMidiConsumer* consumer = roster->NextConsumer(&id);
					
					while (consumer) 
					{
						if (! strcmp(consumer->Name(), name))
						break;
						consumer->Release();
						consumer = roster->NextConsumer(&id);
					}
					
					if (mididistination){
						midiout->Disconnect(mididistination);
						mididistination->Release();
					}
					
					mididistination=consumer;
					status_t err = midiout->Connect(mididistination);
					if (err != B_OK) {
						fprintf(stderr, "Couldn't connect input: %s\n", strerror(err));
					}
					break;
		
		
	}
}

void	TOutput::HandleData(int	CH, int number, int data)
{
	// Channel A,B,C Knöpfe werden betätigt
	if(!playing)
	{
		if(playingdata[0]>=0)
		{
			outputstatus[CH]=status[CH];
			if(status[CH]==-10)song.NoteOff(10,playingdata[0], 127);
			else if(status[CH]==-127)
			{
					midiout->SprayNoteOff(CH-1,playingdata[0], 127);
			}
			else 
			{
				song.NoteOff(CH,playingdata[0],127);
				outputstatus[CH]=1;
			}
		}
		if(data>=0) 
		{
				playingdata[0]=data;
				if(status[CH]==-10)song.NoteOn(10,playingdata[0], 127);
				else if(status[CH]==-127)
				{
					midiout->SprayNoteOn(CH-1,playingdata[0], 127);
				}
				else song.NoteOn(CH,playingdata[0], 127);
		}
	}
	voldata[CH][number]=data;
}

bool TOutput::QuitRequested()
{
	for(int i=1;i<=3;i++)
	{
		if(!(playingdata[i]==-1))
		{
		
			if(outputstatus[i]==1)song.NoteOff(i,playingdata[i], 127);
			else if(outputstatus[i]==-10)song.NoteOff(10,playingdata[i], 127); 
			else if(outputstatus[i]==-127){
				midiout->SprayNoteOff(i-1,playingdata[i], 127);
			}
		}
		outputstatus[i]=0;
	}
	
	if (midiout)
	{ 
		if(mididistination)
		{
							midiout->Disconnect(mididistination);
							mididistination->Release();
							mididistination=NULL;
		}
		midiout->Unregister();
	}
	midiout->Release();
	midiout=NULL;
	return true;
}







//
//TTimer.cpp
//

#include "TTimer.h"
#include <Window.h>
#include <View.h>
#include <Message.h>
#include <Messenger.h>

const int64 INTERVAL = 10000;

TTimer::TTimer(BView* view,BLooper* looper,int tempo0, int tick0, int duty0)
    :BLooper(NULL, B_REAL_TIME_PRIORITY)
{ 
	targetlooper=looper;
	target=view;
	tempo=tempo0;
	tempo1=tempo0;
	tempo2=0;
	tick=15*1000000/((2*tempo+4)*INTERVAL);
	half=tick/2;
	tickcounter=0;
	duty=duty0;
	noteoffpoint=tick*duty/127;
	notecounter=0;
	Run();
	noteon=false;
	iscontinue=true;
	isplaying=false;
	isstopping=false;
	isslave=false;
	time2sleep=system_time()+INTERVAL*10;
	endofnote=15;
	stopnote=15;
	strigtarget=0;
	etrigtarget=0;
	clocktarget=0;
}

void    TTimer::MessageReceived(BMessage* message){
	BMessage* msg;
	
	
	switch ( message->what ) 
    { 
                case 'str0': 
                		if(iscontinue)Timer();
                		break;
                case 'duty': 
                        Changeduty(message->FindInt32("data"));
                        break;
                case 'temp': 
                       if(!isslave){
                       		tempo1=message->FindInt32("data");
                       		Changetempo(tempo1+tempo2);
                       } 
                       if(clocktarget!=0){
								BMessenger* messenger = new BMessenger("application/x-vnd.tani-Q", clocktarget);
								BMessage* msg2=new BMessage('eclk');
								msg2->AddInt32("data",tempo);
								msg2->AddInt32("tick",tickcounter);
								messenger->SendMessage(msg2);
						} 
                        break; 
                case 'tem2': 
                        if(!isslave){
                        		tempo2=message->FindInt32("data");
                        		Changetempo(tempo1+tempo2); 
                        } 
                       if(clocktarget!=0){
								BMessenger* messenger = new BMessenger("application/x-vnd.tani-Q", clocktarget);
								BMessage* msg2=new BMessage('eclk');
								msg2->AddInt32("data",tempo);
								msg2->AddInt32("tick",tickcounter);
								messenger->SendMessage(msg2);
						} 
                        break; 
                case 'strt':
                		if(!(mode==0)){
                			if(!isplaying){
                						isstopping=false; 	
                						Start();
                						msg= new BMessage('strt');
                						targetlooper->PostMessage(msg);
                						delete msg; 
                			}
                			else{		isstopping=true;
                						stopnote=notecounter;
                			}
                		}
                		break;
                		
                case 'str2':
                		if(!(mode==0)){
                			isstopping=false; 	
                			Start();
                			msg= new BMessage('strt');
                			targetlooper->PostMessage(msg);
                			delete msg; 
                			
                		}
                		break;		
                case 'end0':if(etrigtarget!= 0){
								BMessenger* messenger;
								BMessage* msg2;
								messenger = new BMessenger("application/x-vnd.tani-Q", etrigtarget);
								msg2=new BMessage('str2');
								messenger->SendMessage(msg2);
							}
                			if((mode==2)&&(!isstopping)) Start();
                			else{ 
                					isplaying=false;
                					msg=new BMessage('stop');
                					targetlooper->PostMessage(msg);
                					delete msg;
                			}
                			break;
                case 'slct':			mode=message->FindInt32("data");
                						msg = new BMessage('loff');
										target->Window()->PostMessage(msg,target);
										delete msg;
                						stepcounter=endofnote;
                						break;
                case 'shot':
                			if(mode==0) StartStep();break;
                			
                case 'btup':if(mode==0) StopStep();break;
                case 'lamp':endofnote=message->FindInt16("No.");
                			stopnote=endofnote;
                			break;
                case 'lamc':endofnote=message->FindInt16("No.");
                			stopnote=endofnote;
                			break;
                case 'strg':strigtarget=message->FindInt32("team");break;
				case 'etrg':etrigtarget=message->FindInt32("team");break;
				case 'ctrg':BMessenger* messenger;
							BMessage* msg2;
							if(clocktarget!=0){
								messenger = new BMessenger("application/x-vnd.tani-Q", clocktarget);
								msg2=new BMessage('iclk');
								messenger->SendMessage(msg2);
							}
							clocktarget=message->FindInt32("team");
							if(clocktarget!=0){
								messenger = new BMessenger("application/x-vnd.tani-Q", clocktarget);
								msg2=new BMessage('eclk');
								msg2->AddInt32("data",tempo);
								msg2->AddInt32("tick",tickcounter);
								messenger->SendMessage(msg2);
							}
                			;break;
				case 'eclk':isslave=true;
							tempo1=message->FindInt32("data");
							tickcounter=message->FindInt32("tick");
                       		Changetempo(tempo1); 
                       		if(clocktarget!=0){
								messenger = new BMessenger("application/x-vnd.tani-Q", clocktarget);
								messenger->SendMessage(message);
							}
							break;
				case 'iclk':msg=new BMessage('setv');
							target->Window()->PostMessage(msg,target);
							isslave=false;
							break;
	
                						 
                
    } 



}

void 	TTimer::Timer(){
	
	BMessage* msg;
	time2sleep+=INTERVAL;
	snooze_until(time2sleep,B_SYSTEM_TIMEBASE);
	
	if(!(noteoffpoint==0)){ 
		if(isplaying){
			if(tickcounter==0){
				msg=new BMessage('non0');
				msg->AddInt16("No.",notecounter);
				noteon = true;
				targetlooper->PostMessage(msg);
				delete msg;
			}else if((tickcounter>=noteoffpoint)&&noteon){
				msg=new BMessage('nof0');
				noteon= false;
				targetlooper->PostMessage(msg);
				delete msg;
			}
		}
	}
	if(tickcounter==0){
		msg =new BMessage('puls');
		target->Window()->PostMessage(msg,target);
		delete msg;
		if(isplaying){
			msg = new BMessage('lpon');
			msg->AddInt16("No.",notecounter);
			target->Window()->PostMessage(msg,target);
			delete msg; 
		}
		
	}
	if(tickcounter==half){
		msg=new BMessage('half');
		target->Window()->PostMessage(msg,target);
		delete msg;
	}
	if(tickcounter>=tick){
		tickcounter=0;
		if(isplaying){
			msg = new BMessage('loff');
			target->Window()->PostMessage(msg,target); 
			delete msg;
			if(notecounter>=stopnote){
			msg=new BMessage('end0');
			PostMessage(msg);
			delete msg;
			}
			notecounter++;
		}
	}else tickcounter++;
	
	msg=new BMessage('str0');
	PostMessage(msg);
	delete msg;
}

void 	TTimer::Changeduty(int newduty){
	duty=newduty;
	noteoffpoint=tick*(duty+2)/128;
	if (noteoffpoint==0)noteoffpoint=1;
}

void 	TTimer::Changetempo(int32 newtempo){
	tempo=newtempo;
	tick=15*1000000/((2*tempo+4)*INTERVAL);
	noteoffpoint=tick*(duty+2)/128;
	if (noteoffpoint==0)noteoffpoint=1;
	half=tick/2;
}

void 	TTimer::Start(){
	isplaying=true;
    tickcounter=0;
    notecounter=0;
    stopnote=endofnote;
    
    if(strigtarget!= 0){
		BMessenger* messenger = new BMessenger("application/x-vnd.tani-Q", strigtarget);
		BMessage* msg2=new BMessage('str2');
		messenger->SendMessage(msg2);
	}
}

void 	TTimer::Stop(){

}
bool TTimer::QuitRequested(){
	if(clocktarget!=0){
		BMessenger* messenger = new BMessenger("application/x-vnd.tani-Q", clocktarget);
		BMessage* msg2=new BMessage('iclk');
		messenger->SendMessage(msg2);
	}
	iscontinue=false;
	snooze(300);
	return true;
}

void	TTimer::StartStep(){
	BMessage* msg;
	if (stepcounter>=endofnote) stepcounter=0;
	else stepcounter++;
			
	msg = new BMessage('loff');
	target->Window()->PostMessage(msg,target);
	delete msg;
	msg=new BMessage('non0');
	msg->AddInt16("No.",stepcounter);
	targetlooper->PostMessage(msg,targetlooper);
	delete msg;
	msg = new BMessage('lpon');
	msg->AddInt16("No.",stepcounter);
	target->Window()->PostMessage(msg,target); 
	delete msg;
}

void	TTimer::StopStep(){
	BMessage* msg;
	msg=new BMessage('nof0');
	targetlooper->PostMessage(msg,targetlooper);
	delete msg;
}




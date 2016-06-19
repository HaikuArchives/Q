// 
// ASQApp.h 
// 
#ifndef ASQAPP_H
#define ASQAPP_H
#include "ASQWindow.h"
#include <Application.h> 
#include <Messenger.h>
#include <FilePanel.h>

const char *MY_SIG = "application/x-vnd.tani-Q";
class BApplication;

class ASQApp : public BApplication 
{ 
public: 
        ASQApp(); 

	void	MessageReceived(BMessage *Msg);
	void AboutRequested(void);
	void RefsReceived(BMessage *message);
	void RefRequested(void);
	BFilePanel* openpanel;
	BMessage* refmsg;

	ASQWindow* window;
	BMessenger* messenger;
	int32	number;

}; 

#endif
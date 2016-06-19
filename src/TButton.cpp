//
//TButton.cpp
//

#include "TButton.h"

TButton :: TButton(BRect frame,const char *name,const char *label, BMessage *message)
		     : BButton(frame,name,label,message)
{
	messagetopost = message;
	messagetopost2 = NULL;
}

TButton :: TButton(BRect frame,const char *name,const char *label, BMessage *message,BMessage *message2)
		     : BButton(frame,name,label,message)
{
	messagetopost  = message;
	messagetopost2 = message2;
}

void TButton ::MouseDown(BPoint where)
{				
	MakeFocus();
	BMessage msg;
	msg= *messagetopost;
	Invoke(&msg);
	SetValue(true);
}

void TButton ::MouseUp(BPoint where)
{
	SetValue(false);
	if(!(messagetopost2==NULL))
	{
 		BMessage msg;
 		msg = *messagetopost2;
    Invoke(&msg);
  }
}
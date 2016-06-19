//
//TButton.h
//
#ifndef TBUTTON_H
#define TBUTTON_H
#include <Button.h>


class BButton;

class TButton : public BButton 
{

public:
			TButton(BRect frame,
					const char *name,
					const char *label, 
					BMessage *message); 
			TButton(BRect frame,const char *name,const char *label, BMessage *message,
					BMessage *message2);
void		MouseDown(BPoint where);
void		MouseUp(BPoint pt);
BMessage*	messagetopost;
BMessage*	messagetopost2;

};

#endif
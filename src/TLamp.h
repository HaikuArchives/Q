//
//TLamp.h
//

#ifndef TLAMP_H
#define TLAMP_H
#include <Control.h>

class BControl;

class TLamp : public BControl 
{ 
public: 
            TLamp(BRect frame, const char *name, 
         				const char *label); 
         	TLamp(BRect frame, const char *name, 
         				const char *label,BMessage* msg,BHandler* handler); 
    void    AttachedToWindow();
    void SetValue(int32 value);
    void    Draw( BRect rect );
    void	Update();
    void MouseDown(BPoint point); 
private:
	BHandler* target;
	int32	lvalue;
	BRect	rect;
	BMessage* messagetopost;
}; 

#endif
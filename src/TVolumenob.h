//
//TVolumenob.h
//

#ifndef TVOLUMENOB_H
#define TVOLUMENOB_H
#include <Control.h>
#include "Tparrot.h"

class BControl;


class TVolumenob : public BControl 
{ 
public: 
			TVolumenob(BRect frame, const char *name,const char *label, BMessage* message,BHandler* target); 
         	TVolumenob(BRect frame, const char *name,const char *label);  
    void    AttachedToWindow();
    void 	SetValue(int32 value);
    void    Draw( BRect rect );
    void	Update();
    void 	MouseDown(BPoint point);
	void 	HandleMouse();
    void 	MessageReceived(BMessage* message);
    void	PostValue(); 
    virtual float	Gettheta(int32 v);
    virtual int32	GetValue(float t);

	BMessage* messagetopost;
	BPoint	nbcenter;
	BRect 	rect;
	BPoint	nbpoint;
	float	theta;
	float	r;
	Tparrot	*parrot;
	
}; 

#endif

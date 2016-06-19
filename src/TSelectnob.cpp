//
//TSelectnob.cpp
//
#include "Tparrot.h"
#include "TSelectnob.h"

TSelectnob :: TSelectnob(BRect frame, const char *name, const char *label, BMessage* message,BHandler* target) 
            : TVolumenob(frame, name,label,message,target) 
{ 
	
}   
TSelectnob :: TSelectnob(BRect frame, const char *name, const char *label) 
            : TVolumenob(frame, name, label) 
{ 
}

float	TSelectnob::Gettheta(int32 v)
{		
		float t;
		t=150-60*v;
    return t;
}


int32	TSelectnob::GetValue(float t)
{
		int32 v;
    if (t>120)t=150;
    else if (t<60)t=30;
    else t=90;
    v=(int32)((150-t)/60);
		return v;
}	

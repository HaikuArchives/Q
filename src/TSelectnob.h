//
//TSelectnob.h
//

#ifndef TSELECTNOB_H
#define TSELECTNOB_H
#include <Control.h>

#include "Tparrot.h"
#include "TVolumenob.h"

class TSelectnob : public TVolumenob 
{ 
public: 
			TSelectnob(BRect frame, const char *name,const char *label, BMessage* message,BHandler* target); 
      TSelectnob(BRect frame, const char *name,const char *label); 
	
	float	Gettheta(int32 v);
	int32	GetValue(float t); 
    //void 	SetValue(int32 value);
 
}; 

#endif
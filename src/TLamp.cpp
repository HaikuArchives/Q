//
//TLamp.cpp
//
#include "TLamp.h"

TLamp::TLamp(BRect frame, const char *name,const char *label) 
    :BControl(frame, name,label,NULL,B_FOLLOW_NONE, B_WILL_DRAW)
{ 
		messagetopost=NULL;
}
TLamp::TLamp(BRect frame, const char *name,const char *label,BMessage* msg, BHandler* handler) 
    :BControl(frame, name,label,NULL,B_FOLLOW_NONE, B_WILL_DRAW)
{ 
		messagetopost=msg;
		target=handler;
		SetTarget(target);
}

void  TLamp::AttachedToWindow(){
	rect=Bounds();
	lvalue=0;
    rgb_color color = {128, 128, 128};
//	  rgb_color viewcolor = {60, 60, 60}; 
	  rgb_color viewcolor = {60, 60, 250}; 
    rgb_color lowcolor = { 255, 255, 255 }; 
	
    SetViewColor( viewcolor ); 
    SetHighColor( color ); 
    SetLowColor( lowcolor );
}

void  TLamp::SetValue(int32 value){
		lvalue=value;
		Update();
}

void  TLamp::Draw( BRect rect ){
		Update();
}
void  TLamp::Update(){

	rgb_color color1= {255, 0, 50};
	rgb_color color2= {180, 0, 0}; 
	rgb_color color3= {150, 0, 50};
	rgb_color color4= {100, 0, 0}; 
	rgb_color color5= {50, 255, 0};
	rgb_color color6= {0, 180, 0};
	BPoint	point1(8,9);
	BPoint  point2(9,9);
	BPoint	point3(10,8);
	BPoint	point4(9,8);
	BPoint center(10,10);
	
	if (lvalue==1){
	SetHighColor( color2 ); 
	FillEllipse(center,5.5,5.5,B_SOLID_HIGH);
	SetHighColor( color1 ); 
	FillEllipse(center,3.5,3.5,B_SOLID_HIGH);
	}else if(lvalue==2){
	SetHighColor( color6 ); 
	FillEllipse(center,5.5,5.5,B_SOLID_HIGH);
	SetHighColor( color5 ); 
	FillEllipse(center,3.5,3.5,B_SOLID_HIGH);
	}else{
	SetHighColor( color4 ); 
	FillEllipse(center,5.5,5.5,B_SOLID_HIGH);
	SetHighColor( color3 ); 
	FillEllipse(center,3.5,3.5,B_SOLID_HIGH);
	}
	StrokeLine(point1,point2,B_SOLID_LOW);
	StrokeLine(point3,point4,B_SOLID_LOW);
	
	
	
	
}
void  TLamp::MouseDown(BPoint point){
		BMessage msg;
		if(!(messagetopost==NULL)){
			msg= *messagetopost;
			Invoke(&msg);
		
 		uint32 buttons = 1; 
   	    while ( buttons ) { 
           snooze(20 * 1000); 
           GetMouse(&point, &buttons, true); 
           lvalue=2;
           Update();
       } 
        lvalue=0;
        Update();
		}
}

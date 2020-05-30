//
//TVolumenob.cpp
//
#include "Tparrot.h"
#include "TVolumenob.h"
#include <Window.h>

TVolumenob::TVolumenob(BRect frame, const char *name, 
         				const char *label, BMessage* message,BHandler* target) 
    :BControl(frame, name,label, message,B_FOLLOW_NONE, B_WILL_DRAW)
{ 
	SetTarget(target);
    messagetopost=message;
    parrot=new Tparrot(this);
    

}   
TVolumenob::TVolumenob(BRect frame, const char *name, 
         				const char *label) 
    :BControl(frame, name,label, NULL,B_FOLLOW_NONE, B_WILL_DRAW)
{ 
    parrot=new Tparrot(this);
    messagetopost=NULL;

}


void  TVolumenob::AttachedToWindow(){
	
	rgb_color color = {128, 128, 128};
//	rgb_color viewcolor = {60, 60, 60}; 
	rgb_color viewcolor = {60, 60, 250}; 
    rgb_color lowcolor = { 255, 255, 255 }; 
	
    SetViewColor( viewcolor ); 
    SetHighColor( color ); 
    SetLowColor( lowcolor );
	
	rect=Bounds();
    r=(rect.right-rect.left)/2;
	nbcenter.Set(rect.left+r,rect.top+r);
	r-=1;
	SetValue(-1);
    
}

void  TVolumenob::SetValue(int32 value){

	float Pie=3.14;
	theta= Gettheta(value);
	if (theta>218)theta=218;
    else if (theta<-38)theta=-38;
           					      					
	nbpoint.Set(nbcenter.x+r*cos(theta/180*Pie),nbcenter.y-r*sin(theta/180*Pie));
	Update();
	BControl::SetValue(value);
    PostValue();
}

void  TVolumenob::Draw( BRect rect ){
	Update();
}

void  TVolumenob::Update(){
	rgb_color color = {128, 128, 128};
	rgb_color color2= {100, 100, 100}; 
	rgb_color color3= {150, 150, 150};
	SetHighColor( color );
	FillEllipse(nbcenter,r+1,r+1,B_SOLID_HIGH);
	SetHighColor( color2 );
	FillArc(nbcenter,r+1,r+1,225,180,B_SOLID_HIGH);
	SetHighColor( color3 );
	FillEllipse(nbcenter,r-3,r-3,B_SOLID_HIGH);
	SetPenSize(3);
	StrokeLine(nbcenter,nbpoint,B_SOLID_LOW);
	SetPenSize(1);
}
void  TVolumenob::MouseDown(BPoint point){
	HandleMouse();
}

void TVolumenob::HandleMouse(){

			float	x,y;
			float Pie=3.14;
      		uint32	buttons = 1; 
			BPoint	point;
			int32		v;
       		BMessage* msg;
       		
       		GetMouse(&point, &buttons, true);
       		if(buttons){
   	    					
          					x=point.x-nbcenter.x;
           					y=point.y-nbcenter.y;
           					if(x==0){
           								if(y<=0)theta=90;
           								else theta=270;
           			
           					}else if(x>0)theta=atan(-y/x)*180/Pie;
           		 			else theta=-atan(y/x)*180/Pie+180;
           					v=GetValue(theta);
           					if(!(Value()==v)) SetValue( v );
           					msg= new BMessage('mada');
           					parrot->PostMessage(msg);
           					delete msg;
 			}else{
 							msg= new BMessage('msup');
           					Invoke(msg);
           					msg= new BMessage('dirt');
           					this->Window()->PostMessage(msg);
           					delete msg;
           	}

}

void    TVolumenob::MessageReceived(BMessage* message){

	switch ( message->what ) 
    { 
                case 'mada': 
                        HandleMouse();
                        break;

		default:
			BControl::MessageReceived(message);
     } 


}
void	TVolumenob::PostValue(){

		if(!(messagetopost==NULL)){
           	BMessage msg= *messagetopost;
           	(&msg)->AddInt32("data",Value());
           	Invoke(&msg);
        }
}

float	TVolumenob::Gettheta(int32 v){
		float t=218-2*(v+1);
		return t;

}

int32	TVolumenob::GetValue(float t){
		int32 v;
		if (t>218)t=218;
        else if (t<-38)t=-38;
		v=(int32)((218-t)/2-1);
		return v;
		
}

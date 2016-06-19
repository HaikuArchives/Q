//
//Tparrot.cpp
//

#include "Tparrot.h"
#include <Window.h>
#include <View.h>

Tparrot::Tparrot(BView* view)
    :BLooper()
{ 
	target=view;
	
	Run();
}

void    Tparrot::MessageReceived(BMessage* message){

	snooze(20000);
	target->Window()->PostMessage(message,target);
}










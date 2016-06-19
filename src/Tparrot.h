//
//Tparrot.h
//
#ifndef TPARROT_H
#define TPARROT_H
#include <Looper.h>
class BLooper;

class Tparrot : public BLooper
{ 
public: 
            Tparrot(BView* view); 
    void    MessageReceived(BMessage* message);
    
private:
	BView*	target;
	BLooper* targetlooper;

}; 

#endif
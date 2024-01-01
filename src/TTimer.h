//
//TTimer.h
//
#ifndef TTIMER_H
#define TTIMER_H

#include <Looper.h>
#include <View.h>

class BLooper;

class TTimer : public BLooper
{ 
public: 
            TTimer(BView* view,BLooper* looper,int tempo0, int tick0, int duty0); 
    void    MessageReceived(BMessage* message);
    bool	QuitRequested();
    void 	Timer();
    void 	Changeduty(int newduty);
    void	Changetempo(int32 newtempo);
    BLooper* targetlooper;
    void	Start();
    void	Stop();
    void	StartStep();
    void	StopStep();
private:
	BView*	target;
	int		tempo;
	int		tempo1;
	int		tempo2;
	int		tick;
	int		half;
	int		duty;
	int		tickcounter;
    int		notecounter;
    int		stepcounter;
    int		noteoffpoint;
    int		endofnote;
    int		stopnote;
    bool	noteon;
    bool	isplaying;
    bool	isstopping;
    bool	iscontinue;
    bool    isslave;
    bigtime_t	time2sleep;
    int		mode;
    
    team_id	strigtarget;
    team_id	etrigtarget;
    team_id	clocktarget;
}; 

#endif

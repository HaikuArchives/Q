// 
// ASQView.h 
// 
#ifndef ASQVIEW_H
#define ASQVIEW_H

#include <Beep.h>
#include <View.h>

#include "TVolumenob.h"
#include "TSelectnob.h"
#include "TLamp.h"
#include "TTimer.h"
#include "TOutput.h"
#include "TOutputMenuField.h"

#define START_BUTTON_PRESSED 'strt'
#define SHOT_BUTTON_PRESSED 'shot'

class BView;


class ASQView : public BView 
{ 
	public: 
          ASQView( BRect frame, const char* name ); 
  
    virtual void  AttachedToWindow();
    virtual void	MessageReceived(BMessage* message); 
    virtual void  Draw( BRect rect ); 
		virtual	void 	MouseMoved(BPoint point, uint32 state, const BMessage *message);
		virtual	void	MouseUp(BPoint);
    
    void	SaveData(BMessage *message);
    void	SaveSMFData(BMessage *message);
    void	LoadData(BMessage *message);
   
	TTimer*		timer;
	TOutput*	output;
	
	entry_ref* savedataref;
	BString* savedatafilename;

	private:
		TVolumenob*	temponob;
		TSelectnob*	togulnob;
		TVolumenob*	volA[64];
		TVolumenob*	volB[64];
		TVolumenob*	volC[64];
		TVolumenob*	volD[64];
		TVolumenob*	portamentA;
		TVolumenob*	portamentB;
		TVolumenob*	duty;
		TLamp*		tempolamp;
		TLamp*		lamp[64];
		int			noofon;
	
		TOutputMenuField* outmenu[4];
		BMenuField* ctrlmenu[4];
	
	
		int		endofnote;
		int		now;
		bool	running;
		bool	stepping;
		bool	nowstepping;
		bool  hasref;
		
		bool 	drag_file_ok;
		const BMessage *message_from_tracker;
		entry_ref	ref;
		BString	 	fDropName;
}; 

#endif

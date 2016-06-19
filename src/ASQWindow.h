//
// ASQWindow.h
//
#ifndef ASQWINDOW_H
#define ASQWINDOW_H
#include <Window.h>
#include <FilePanel.h>
#include "ASQView.h"

#define OPEN_FILE_PANEL						'ofpl'

class BWindow;

class ASQWindow : public BWindow
{
public:
                ASQWindow( BRect frame ,const char* n);
    bool        QuitRequested();
    void		MessageReceived(BMessage* message);
    void		SaveData(BMessage *message);
    ASQView*		view;
    BFilePanel* savepanel;
    BFilePanel* openpanel;
    BFilePanel* savesmfpanel;
    BMenuItem* saveitem;
    char* 		name;

};

class MyOpenFilter : public BRefFilter
{
			virtual bool Filter(const entry_ref* ref,BNode* node,
												  struct stat_beos* st,const char* filetype);
};


#endif

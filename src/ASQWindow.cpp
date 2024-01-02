// ASQWindow.cpp
//
#include <Application.h>
#include <Catalog.h>
#include <InterfaceKit.h>
#include <LayoutBuilder.h>
#include <Roster.h>
#include <StorageKit.h>

#include "ASQWindow.h"

#undef B_TRANSLATION_CONTEXT
#define B_TRANSLATION_CONTEXT "ASQWindow"

ASQWindow::ASQWindow( BRect frame , const char* n)
    :
	BWindow( frame, n, B_TITLED_WINDOW, B_NOT_RESIZABLE|B_NOT_ZOOMABLE )
{
	BMenuBar *menubar;
	BMessage* msg;

	BRect viewFrame = Bounds();
	viewFrame.OffsetBy(0,20);

	// Preparing drag & drop frame
	float height = viewFrame.Height();
	float width = viewFrame.Width();

	BPoint rigthbottom(width, height);
	viewFrame.SetRightBottom(rigthbottom);
	
	BMenu* file;
	//BMenu* edit;
	//BMenu* prefs;
	BMenuItem* item;
	file = new BMenu(B_TRANSLATE("File"));

	item = new BMenuItem(B_TRANSLATE("Open..."),new BMessage('open'),'O');
	file->AddItem(item);

	saveitem = new BMenuItem(B_TRANSLATE("Save"),new BMessage('save'),'S');
	file->AddItem(saveitem);
	saveitem->SetEnabled(false);

	item = new BMenuItem(B_TRANSLATE("Save as..."),new BMessage('sset'),'S',B_SHIFT_KEY);
	file->AddItem(item);

	item = new BMenuItem(B_TRANSLATE("Save as SMF..."),new BMessage('ssmf'),'M',B_SHIFT_KEY);
	file->AddItem(item);

	file->AddSeparatorItem();

	item = new BMenuItem(B_TRANSLATE("About..."),new BMessage(B_ABOUT_REQUESTED));
	file->AddItem(item);

	file->AddSeparatorItem();

	item = new BMenuItem(B_TRANSLATE("Close"),new BMessage(B_QUIT_REQUESTED),'W');
	file->AddItem(item);

	item = new BMenuItem(B_TRANSLATE("Quit"),new BMessage(B_QUIT_REQUESTED),'Q');
	file->AddItem(item);

	//edit = new BMenu("Edit");
	//prefs = new BMenu("Prefs");
	menubar = new BMenuBar("menubar");
	menubar->AddItem(file);
	//menubar->AddItem(edit);
	//menubar->AddItem(prefs);
    view = new ASQView( viewFrame, n );

	BLayoutBuilder::Group<>(this, B_VERTICAL, 0)
	.Add(menubar)
	.Add(view)
	.End();
	
    BMessenger *target;
    target = new BMessenger(this);
    savepanel = new BFilePanel(B_SAVE_PANEL,target);
    savepanel->SetSaveText("untitled.Q");

  	//look in CWD
	app_info info;
  	BPath path;
  	be_app->GetAppInfo(&info);
  	BEntry entry(&info.ref);
  	entry.GetPath(&path);
  	path.GetParent(&path);
	savepanel -> SetPanelDirectory(path.Path());


    target = new BMessenger(this);
    msg = new BMessage('smfr');
    savesmfpanel = new BFilePanel(B_SAVE_PANEL,target,NULL,0,false,msg);
    savesmfpanel-> SetSaveText("untitled.SMF");
		savesmfpanel -> SetPanelDirectory(path.Path());

		openpanel = new BFilePanel(B_OPEN_PANEL, new BMessenger(this), NULL, 0, false,
															new BMessage(OPEN_FILE_PANEL),new MyOpenFilter(), false, true);
		openpanel -> SetPanelDirectory(path.Path());						// CWD



}

bool
ASQWindow::QuitRequested()
{
	view->timer->PostMessage( B_QUIT_REQUESTED );
 	snooze(20000);
 	view->output->PostMessage( B_QUIT_REQUESTED );
 	snooze(20000);
 	be_app->PostMessage( B_QUIT_REQUESTED );
    return true;
}

void
ASQWindow::MessageReceived(BMessage* message)
{

	switch(message->what)
	{
	case START_BUTTON_PRESSED:view->timer->PostMessage(message);break;

	case SHOT_BUTTON_PRESSED:view->timer->PostMessage(message); break;

	case B_ABOUT_REQUESTED:be_app->PostMessage(message); break;

	//case 'open':be_app->PostMessage(message); break;

	case 'sset':savepanel->Show();break;

	case 'save':view->SaveData(NULL);break;

	case 'smfr':view->SaveSMFData(message);break;

	case 'btup':view->timer->PostMessage(message);break;

	case 'inst':view->output->PostMessage(message);
			saveitem->SetEnabled(true);
			break;

	case 'ctrl':view->output->PostMessage(message);
			saveitem->SetEnabled(true);
			break;

	case 'rvrb':view->output->PostMessage(message);
			saveitem->SetEnabled(true);
			break;

	case 'strg':view->timer->PostMessage(message);break;

	case 'etrg':view->timer->PostMessage(message);break;

	case 'ctrg':view->timer->PostMessage(message);break;

	case 'mout':view->output->PostMessage(message); break;

	case B_SAVE_REQUESTED:view->SaveData(message);break;

	case OPEN_FILE_PANEL:
	case B_SIMPLE_DATA:
	case B_REFS_RECEIVED:
				view->LoadData(message);
	break;

		case 'open':
				openpanel->Show();

			break;


	case 'ssmf':savesmfpanel->Show();break;

	case 'dirt':saveitem->SetEnabled(true);break;

	case 'clea':saveitem->SetEnabled(false);
		BString* name = new BString();
			message->FindString("name",name);
			char filename[50];
			sprintf(filename,"%s # %ld",name->String(),be_app->Team());
			SetTitle(filename);
		break;
	}


}




bool
MyOpenFilter::Filter(const entry_ref* ref,BNode* node,
														struct stat_beos* st,const char* filetype)
{
	// hier wird eine Filterfunktion implementiert
	const char *filterMaske = "text/x-vnd.tani-Q-data";
	bool admitIt = false;
	char type[256];
	const BString 	mask(filterMaske);	// auch dies funktioniert- supertype/subtype
	class BNodeInfo nodeInfo(node);			// Konstruktor wird mit node initialisiert

	if (node->IsDirectory()) 						//Abfrage ob Ordner (File oder Symbolic Link
	{																		// in BStatable deklariert, abgeleitete Klassen sind
		admitIt = true;										// BNode und BEntry
	}																		// Ordner auf jeden Fall anzeigen
	else
	{
		nodeInfo.GetType(type);						// liefert file type als MIME-string, type wird zurückgeliefert
																			// allow all files with supertype "text"
		admitIt = (mask.Compare(type,mask.CountChars()) == 0);
																			// mask.CountChars ermittelt Anzahl der chars von "text"
																			// mask.Compare vergleicht den ermittelten type mit "text"
																			// CountChars() Länge des strings in characters,
																			// Klassenfunktion von class BString
	}

	return (admitIt);
}



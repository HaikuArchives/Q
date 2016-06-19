//
//TMenuField.cpp
//

#include "TMenuField.h"
#include	<Message.h>
#include	<MenuItem.h>
#include <Application.h>
#include <Roster.h>
#include <List.h>
#include <stdio.h>


TMenuField :: TMenuField(BRect frame, const char *name, const char *label, BMenu *menu, uint32 command)
: BMenuField(frame, name,label,menu)
{ 
	cmd = command;
	BMessage* m;
	m=new BMessage(cmd);
	m->AddInt32("team",0);
	BMenuItem* item = new BMenuItem("off",m);
	item->SetMarked(true);
    Menu()->AddItem(item);
}  
void	TMenuField :: MouseDown(BPoint point) 
{
	BList applist;
	int32 appcount;
	int32 i,j;
	BMenuItem* removingitem;
	BMenuItem* item;
	BMessage* m;
	char name[50];
	team_id team;
	
	
	
	be_roster->GetAppList("application/x-vnd.tani-Q", &applist);
	appcount=applist.CountItems();
	j=Menu()->CountItems();
	for (i=j-1;i>0;i--){
		removingitem=Menu()->RemoveItem(i);
	}
	for(i=0;i<appcount;i++){
	
		team = (team_id) applist.ItemAt(i);
        if(team != be_app->Team()){
			m=new BMessage(cmd);
			m->AddInt32("team",(int32)team);
			sprintf(name,"# %ld",team);
			item = new BMenuItem(name,m);
			Menu()->AddItem(item);
		}
	
	}
	
		BMenuField::MouseDown(point) ;


}
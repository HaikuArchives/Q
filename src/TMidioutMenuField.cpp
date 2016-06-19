//
//TMidioutMenuField.cpp
//

#include "TMidioutMenuField.h"
#include <Message.h>
#include <MenuItem.h>
#include <stdio.h>
#include <MidiRoster.h>
#include <MidiConsumer.h>

TMidioutMenuField :: TMidioutMenuField(BRect frame, const char *name, const char *label, BMenu *menu, uint32 command)
: BMenuField(frame, name,label,menu)
{ 
	cmd = command;
	BMessage* m;
	m=new BMessage(cmd);
	m->AddString("name","none");
	BMenuItem* item = new BMenuItem("none",m);
	item->SetMarked(true);
    Menu()->AddItem(item);
}  
void	TMidioutMenuField :: MouseDown(BPoint point) 
{
	int32 i,j;
	BMenuItem* removingitem;
	BMenuItem* item;
	BMessage* m;
	
	BMidiRoster* roster = BMidiRoster :: MidiRoster();
	if (! roster) {
		printf(("Can't find MIDI roster\n"));
		return;
	}
			
	j=Menu()->CountItems();
	
	for (i=j-1;i>0;i--)
	{
		removingitem=Menu()->RemoveItem(i);
	}
	
	int32 id=0;
	BMidiConsumer* consumer = roster->NextConsumer(&id);
	
	while (consumer) 
	{
		m=new BMessage(cmd);
		m->AddString("name",consumer->Name());
		item = new BMenuItem(consumer->Name(),m);
		Menu()->AddItem(item);
		consumer->Release();
		consumer = roster->NextConsumer(&id);
	}
	
	BMenuField::MouseDown(point) ;


}



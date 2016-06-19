// 
// ASQView.cpp 
// 
#include "Bitmaps.h"
#include "ASQView.h"
#include "TVolumenob.h"
#include "TSelectnob.h"
#include "TLamp.h"
#include "TTimer.h" 
#include "TOutput.h"
#include "TButton.h"
#include "TMenuField.h"
#include "TMidioutMenuField.h"
#include "TOutputMenuField.h"
#include <Alert.h>
#include <Box.h>
#include <PopUpMenu.h>
#include <Menu.h>
#include <MenuItem.h>
#include <MenuField.h>
#include <Rect.h>
#include <Message.h>
#include <MidiDefs.h>
#include <TextControl.h>
#include <StorageKit.h>

ASQView::ASQView( BRect frame, const char* name ) 
    :BView( frame, "sampleview", B_FOLLOW_ALL, B_WILL_DRAW ) 
{ 
	message_from_tracker 	= NULL;																				// Initialisierung
	drag_file_ok 					= false;																			// kein File gedraggt

	SetFont( be_plain_font ); 
	SetFontSize( 8 );
    rgb_color color = {255, 255, 255}; 
//    rgb_color viewcolor = {60, 60, 60}; 
    rgb_color viewcolor = {60, 60, 250}; 
    SetViewColor( viewcolor ); 
    SetLowColor(viewcolor);
    SetHighColor( color ); 
    running = FALSE;
    stepping = FALSE;
    nowstepping= FALSE;
    now = 11;
    noofon=0;
		
		output=new TOutput(this, name);
	
} 

void ASQView::AttachedToWindow() 
{ 
	
	int i;
	BMessage* msg;
    rgb_color color = {255, 255, 255};
  	TButton* startButton;
    TButton* shotButton;
    
    timer=new TTimer(this,output,28,64,64);
    output->SetTarget(timer);
    BRect buttonFrame( 10, 20, 35, 45 );
    startButton = new TButton( buttonFrame, "startbutton", "", new BMessage( START_BUTTON_PRESSED )); 
    AddChild( startButton );
    
    buttonFrame.OffsetBy(0, 50);
    shotButton = new TButton( buttonFrame, "shotbutton", "", new BMessage( SHOT_BUTTON_PRESSED ),new BMessage( 'btup' )); 
    AddChild( shotButton );
   
    buttonFrame.OffsetBy(50, -50);
    BRect volumeFrame(60,20,90,50);
    temponob= new TVolumenob(volumeFrame, "volume", "",new BMessage('temp'),timer);
		volumeFrame.OffsetBy(0, 50);
		AddChild(temponob);
		temponob->SetValue(28);
		togulnob= new TSelectnob(volumeFrame, "togul", "",new BMessage('slct'),timer);
		AddChild(togulnob);
    togulnob->SetValue(2);
    buttonFrame.OffsetBy(30, 5);
    tempolamp= new TLamp(buttonFrame, "tempo", "");
    AddChild(tempolamp);
  
    BRect LampFrame(139,5,159,25);
    
    BRect volAFrame(140,40,160,60);
    BRect volBFrame(140,75,160,95);
    BRect volCFrame(140,110,160,130);
    
    
    for(i=0;i<16;i++)
    {
    	msg= new BMessage('lamp');
    	msg->AddInt16("No.",i);
    	lamp[i]= new TLamp(LampFrame, "lamp", "",msg,this);
    	AddChild(lamp[i]);
    	
    	
    	
    	msg= new BMessage('volm');
    	msg->AddInt16("CH",1);				// Midi-Channel 1
    	msg->AddInt16("No.",i);
    	volA[i]= new TVolumenob(volAFrame, "vola", "",msg,output);
    	
    	msg= new BMessage('volm');
    	msg->AddInt16("CH",2);
    	msg->AddInt16("No.",i);
    	volB[i]= new TVolumenob(volBFrame, "volb", "",msg,output);
    	
    	msg= new BMessage('volm');
    	msg->AddInt16("CH",3);
    	msg->AddInt16("No.",i);
    	volC[i]= new TVolumenob(volCFrame, "volc", "",msg,output);
    	
    	AddChild(volA[i]);
    	AddChild(volB[i]);
    	AddChild(volC[i]);
    	
    	LampFrame.OffsetBy(31,0);
    	
    	volAFrame.OffsetBy(31,0);
    	volBFrame.OffsetBy(31,0);
    	volCFrame.OffsetBy(31,0);
    }
    
    BRect volFrame(10,120,30,140);
    msg= new BMessage('ctra');
    msg->AddInt16("CH",1);
    portamentA= new TVolumenob(volFrame, "porA", "",msg,output);
    AddChild(portamentA);
    portamentA->SetValue(64);
    volFrame.OffsetBy(40,0);
    msg= new BMessage('ctrb');
    msg->AddInt16("CH",2);
    portamentB= new TVolumenob(volFrame, "porB", "",msg,output);
    AddChild(portamentB);
    portamentB->SetValue(64);
    volFrame.OffsetBy(40,0);
    duty= new TVolumenob(volFrame,"duty", "",new BMessage('duty'),timer);
    AddChild(duty);
    duty->SetValue(64);
    
    BPopUpMenu* menu;
    BMenuItem* item;
   	BRect fieldFrame( 5, 15, 190, 180 );
   	
   	BRect boxFrame(5,160,200,245);
    BBox* box;
    box= new BBox(boxFrame,"Output");
    box->SetLabel("Output");
    box->SetHighColor(color);
    box->SetLowColor(color);
    box->SetViewColor(color);
    AddChild(box);
   
   	char* strings[4];
    strings[1]="A";
    strings[2]="B";
    strings[3]="C";
    
    TMidioutMenuField* midiout;
    
    
    for(i=1;i<4;i++){
    
    	menu = new BPopUpMenu("BSynth");
    	outmenu[i] = new TOutputMenuField(fieldFrame,strings[i], strings[i],menu, i);
    	outmenu[i]->SetHighColor( color );
    	outmenu[i]->SetDivider(15);
    	box->AddChild(outmenu[i]);
    	fieldFrame.OffsetBy(0,22);
   
    } 
    
    boxFrame.Set(205,160,365,245);
    box= new BBox(boxFrame,"midi connection");
    box->SetLabel("Midi Connection");
    box->SetHighColor(color);
    box->SetLowColor(color);
    box->SetViewColor(color);
    AddChild(box);
    
    fieldFrame.Set(5,15,155,180);
    menu = new BPopUpMenu("midiout");
	midiout = new TMidioutMenuField(fieldFrame, "midiout", "midiout", menu, 'mout');
	midiout->SetHighColor(color);
	midiout->SetDivider(40);
	box->AddChild(midiout);
	
	
	fieldFrame.Set( 5, 15, 115, 180 );
    strings[1]="Ctrl A";
    strings[2]="Ctrl B";
    boxFrame.Set(370,160,490,245);
    box= new BBox(boxFrame,"Controls");
    box->SetLabel("Controls");
    box->SetHighColor(color);
    box->SetLowColor(color);
    box->SetViewColor(color);
    AddChild(box);  

    for(i=1;i<3;i++){
    	menu = new BPopUpMenu("ctrl");
    	msg = new BMessage('ctrl');
    	msg->AddInt16("CH",i);
    	msg->AddInt16("data", 1);
    	item = new BMenuItem("Velosity",msg);
    	menu->AddItem(item);
    	msg = new BMessage('ctrl');
    	msg->AddInt16("CH",i);
    	msg->AddInt16("data",2);
    	item = new BMenuItem("Pitchbend",msg);
    	item->SetMarked(true);
    	menu->AddItem(item);
    	msg = new BMessage('ctrl');
    	msg->AddInt16("CH",i);
    	msg->AddInt16("data",3);
    	item = new BMenuItem("None",msg);
    	menu->AddItem(item);
    	msg = new BMessage('ctrl');
    	msg->AddInt16("CH",i);
    	msg->AddInt16("data",4);
    	
    	ctrlmenu[i] = new BMenuField(fieldFrame,strings[i], strings[i],menu);
    	ctrlmenu[i]->SetHighColor( color );
    	ctrlmenu[i]->SetDivider(40);
    	box->AddChild(ctrlmenu[i]);
    	fieldFrame.OffsetBy(0,22);
   	}   
   	
   		menu = new BPopUpMenu("reverb");
    	msg = new BMessage('rvrb');
    	msg->AddInt16("Reverb",B_REVERB_NONE);
    	item = new BMenuItem("None",msg);
    	menu->AddItem(item);
    	msg = new BMessage('rvrb');
    	msg->AddInt16("Reverb",B_REVERB_CLOSET);
    	item = new BMenuItem("Closet",msg);
    	menu->AddItem(item);
    	msg = new BMessage('rvrb');
    	msg->AddInt16("Reverb",B_REVERB_GARAGE);
    	item = new BMenuItem("Garage",msg);
    	menu->AddItem(item);
    	msg = new BMessage('rvrb');
    	msg->AddInt16("Reverb",B_REVERB_BALLROOM);
    	item = new BMenuItem("Ballroom",msg);
    	item->SetMarked(true);
    	menu->AddItem(item);
    	msg = new BMessage('rvrb');
    	msg->AddInt16("Reverb",B_REVERB_CAVERN);
    	item = new BMenuItem("Cavern",msg);
    	menu->AddItem(item);
    	msg = new BMessage('rvrb');
    	msg->AddInt16("Reverb",B_REVERB_DUNGEON);
    	item = new BMenuItem("Dungeon",msg);
    	menu->AddItem(item);
    	ctrlmenu[3] = new BMenuField(fieldFrame,"Reverb", "Reverb",menu);
    	ctrlmenu[3]->SetHighColor( color );
    	ctrlmenu[3]->SetDivider(40);
    	box->AddChild(ctrlmenu[3]);
    	
   		
   		boxFrame.Set(495,160,625,245);
    	box= new BBox(boxFrame,"Trigger Out");
    	box->SetLabel("Trigger Out");
    	box->SetHighColor(color);
    	box->SetLowColor(color);
    	box->SetViewColor(color);
    	AddChild(box); 
    	
    	fieldFrame.Set( 5, 15, 125, 180 );
    	msg =new BMessage('strg');
    	BPopUpMenu* trigmenu= new BPopUpMenu("Start Trigger");
    	TMenuField* starttrig= new TMenuField(fieldFrame,"Start Trigger", "Start Trig",trigmenu,'strg');
    	starttrig->SetHighColor( color );
    	starttrig->SetDivider(55);
    	box->AddChild(starttrig);
    	fieldFrame.OffsetBy(0,22);
    	msg =new BMessage('etrg');
    	trigmenu= new BPopUpMenu("End Trigger");
    	TMenuField* endtrig= new TMenuField(fieldFrame,"End Trigger", "End Trig",trigmenu,'etrg');
    	endtrig->SetHighColor( color );
    	endtrig->SetDivider(55);
    	box->AddChild(endtrig);
    	fieldFrame.OffsetBy(0,22);
    	msg =new BMessage('ctrg');
    	trigmenu= new BPopUpMenu("Clock Out");
    	TMenuField* clockout= new TMenuField(fieldFrame,"Clock Out", "Clock Out",trigmenu,'ctrg');
    	clockout->SetHighColor( color );
    	clockout->SetDivider(55);
    	box->AddChild(clockout);
    	
   	
    msg =new BMessage(('str0'));
    timer->PostMessage(msg);
    delete msg;
    endofnote=15;
    lamp[endofnote]->SetValue(2);
    savedataref = new entry_ref();
    savedatafilename = new BString();
    hasref=false;
    be_app->PostMessage('refs');
} 

void ASQView::MessageReceived(BMessage* message) 
{ 
   switch(message->what)
   {
   		case 'puls':	tempolamp->SetValue(1);
   						break;
   		case 'half':	tempolamp->SetValue(0);
   						break;
   		case 'lpon':	if(noofon==endofnote) lamp[noofon]->SetValue(2);
   						else lamp[noofon]->SetValue(0);
   						noofon=message->FindInt16("No.");
   						lamp[noofon]->SetValue(1);
   						break;
   		case 'loff':	if(noofon==endofnote) lamp[noofon]->SetValue(2);
   						else lamp[noofon]->SetValue(0);
   						break;
   		case 'lamp':	lamp[endofnote]->SetValue(0);
   						endofnote=message->FindInt16("No.");
   						lamp[endofnote]->SetValue(2);
   						timer->PostMessage(message);
   						Window()->PostMessage('dirt');
   						break;
   		case 'lamc':	lamp[endofnote]->SetValue(0);
   						endofnote=message->FindInt16("No.");
   						lamp[endofnote]->SetValue(2);
   						timer->PostMessage(message);   						
   					break;
   	
   		case 'setv':	
   						int32 v;
   						v=temponob->Value();
   						temponob->SetValue(v);
   					break;
   					
   		default:BView::MessageReceived(message);break;
   }
   
} 

void ASQView::Draw( BRect rect ) 
{ 
    SetFontSize(9);
    MovePenTo( 3, 15 ); 
    DrawString( "Start/Stop" ); 
    MovePenTo( 62, 15 ); 
    DrawString( "Clock" ); 
    MovePenTo( 13, 65 ); 
    DrawString( "Step" );
    MovePenTo( 40, 75 ); 
    SetFontSize(8);
    DrawString( "Step" );
    MovePenTo( 61, 65 ); 
    
    DrawString( "Single" );
    MovePenTo( 92, 75 ); 
    DrawString( "Repeat" );
    MovePenTo( 90, 115 ); 
    DrawString( "Duty" );
    MovePenTo( 7, 115 ); 
    DrawString( "Ctrl A" );
    MovePenTo( 47, 115 ); 
    DrawString( "Ctrl B" );
   
    MovePenTo( 127, 52 ); 
    SetFontSize(10);
    DrawString( "A" );
    MovePenTo( 127, 87 ); 
    DrawString( "B" );
    MovePenTo( 127, 122 ); 
    DrawString( "C" );
    
    SetFontSize(11);				// LED-Beschriftung 1...16
		
		for (int i=1; i<10;i++)
		{
			MovePenTo(116+i*31,35);
			char string[3];
			sprintf(string,"%d",i);						// Int in String 
    	DrawString( string );
    }
    
		for (int i=10; i<17;i++)
		{
			MovePenTo(112+i*31,35);
			char string[3];
			sprintf(string,"%d",i);						// Int in String 
    	DrawString( string );
    }
    
    SetFontSize(9);

		if (!drag_file_ok) 
		{
			SetHighColor(60, 60, 250);	// Rahmen blau
			BRect bounds = Bounds();		
			SetPenSize(4.0);
			bounds.right 	-=3;
			bounds.bottom	-=3;
			StrokeRect(bounds);
		}
	
		if (drag_file_ok) 
		{
			SetHighColor(255, 255, 0);			// Rahmen gelb
			BRect bounds = Bounds();
			SetPenSize(4.0);
			bounds.right -=3;
			bounds.bottom-=3;
			StrokeRect(bounds);
		}
	
		PopState();
 		SetHighColor(255, 255, 255);			// Schrift weiss
       
} 



void ASQView :: MouseMoved(BPoint point, uint32 state, const BMessage *message)// drag&drop #1  tracker -> appl
{
	if (message == NULL) return;			// wichtig, sonst Absturz

	if (state == B_EXITED_VIEW)				// Maus verlässt View 
	{
		drag_file_ok 				 = false;
		message_from_tracker = NULL;
		Draw(Bounds());									// weißer Rahmen zeichnen, blau verschwindet		
		return;
	}

	if (message != message_from_tracker)
	{	
		message_from_tracker = message;
	
		if (message->FindRef("refs", &ref) != B_OK) return;
		BNode node(&ref);
	
		if (node.InitCheck() != B_OK) return;
		BNodeInfo nodeinfo(&node);
	
		if (nodeinfo.InitCheck() != B_OK) return;
		char mime_type[B_MIME_TYPE_LENGTH];
	
		if (nodeinfo.GetType(mime_type) != B_OK) return;
	
		if (strstr(mime_type, "text/x-vnd.tani-Q-data") != NULL) 
		{	// findet das erste Auftreten von "text/x..." in mime_type
			drag_file_ok = true;					// richtiger Filetyp
			Draw(Bounds());								// Rahmen gelb			
		}
	}	// Ende if...
}


void ASQView :: MouseUp(BPoint)																		
{
	drag_file_ok 					= false;
	message_from_tracker 	= NULL;
	Invalidate();										// Mouse up -> neu zeichnen!!
}




void ASQView::SaveData(BMessage* message)
{
	char buffer[255];
	BFile* file;
    entry_ref* ref;
    BDirectory *dir;
	BString* name;
	BString* data;
	int i=1;
	
	name = new BString();
	if(message!=NULL){
	
		ref = new entry_ref();
		message->FindRef("directory", ref);
		dir = new BDirectory(ref);
		message->FindString("name",name);
		
		
	}else if(hasref==false){
		
		Window()->PostMessage('sset');
		return;
		
	}else{
		
		ref = savedataref;
		dir = new BDirectory(ref);
		name = savedatafilename;
		
		
	}
	
	file = new BFile(dir,name->String(),B_READ_WRITE | B_CREATE_FILE | B_ERASE_FILE);
	file->InitCheck();
	data = new BString();
	data->Append("*** Q 1.0 Data File ***\n");
	
	int32 t=2*(temponob->Value())+4;
	sprintf(buffer,"tempo= %ld\n",t );
	data->Append(buffer);
	sprintf(buffer,"playmode= %ld\n", togulnob->Value());
	data->Append(buffer);
	sprintf(buffer,"CtrlA= %ld\n", portamentA->Value());
	data->Append(buffer);
	sprintf(buffer,"CtrlB= %ld\n", portamentB->Value());
	data->Append(buffer);
	sprintf(buffer,"duty= %ld\n", duty->Value());
	data->Append(buffer);
	sprintf(buffer,"endofnote= %d\n", endofnote);
	data->Append(buffer);
	
	sprintf(buffer,"outputA= %d\t %s\n", output->status[1],outmenu[1]->Menu()->FindMarked()->Label());
	data->Append(buffer);
	sprintf(buffer,"outputB= %d\t %s\n", output->status[2],outmenu[2]->Menu()->FindMarked()->Label());
	data->Append(buffer);
	sprintf(buffer,"outputC= %d\t %s\n", output->status[3],outmenu[3]->Menu()->FindMarked()->Label());
	data->Append(buffer);
	
	sprintf(buffer,"ctrlA= %d\t %s\n", output->statusofctrl[1],ctrlmenu[1]->Menu()->FindMarked()->Label());
	data->Append(buffer);
	sprintf(buffer,"ctrlB= %d\t %s\n", output->statusofctrl[2],ctrlmenu[2]->Menu()->FindMarked()->Label());
	data->Append(buffer);
	sprintf(buffer,"reverb= %d\t %s\n", output->statusofctrl[3],ctrlmenu[3]->Menu()->FindMarked()->Label());
	data->Append(buffer);
	
	sprintf(buffer,"\tA\tB\tC\n");
	data->Append(buffer);
	for(i=0;i<16;i++){
		sprintf(buffer,"%d= \t%ld\t %ld\t %ld\n", i, volA[i]->Value(), volB[i]->Value(),volC[i]->Value());
	data->Append(buffer);
	}
	
	file->Write(data->String(),data->Length());
	
	BNodeInfo* fileinfo;
	fileinfo = new BNodeInfo();
	
	fileinfo->SetTo(file);
	fileinfo->SetPreferredApp("application/x-vnd.tani-Q");
	fileinfo->SetType("text/x-vnd.tani-Q-data");
	
	BRect r(0, 0, 31, 31);
	BBitmap* l_icon = new BBitmap(r,B_CMAP8);
	l_icon->SetBits(kLargeIconBits, 1024, 0, B_CMAP8);
	fileinfo->SetIcon(l_icon, B_LARGE_ICON);
	
	BRect sr(0, 0, 15, 15);
	BBitmap* s_icon = new BBitmap(sr,B_CMAP8);
	s_icon->SetBits(kSmallIconBits, 256, 0, B_CMAP8);
	fileinfo->SetIcon(s_icon, B_MINI_ICON);
	
	
	delete file;
	*savedataref= *ref;
	savedatafilename=name;
	BMessage* msg= new BMessage('clea');
	msg->AddString("name",name->String());
	Window()->PostMessage(msg);
	hasref=true;
	
	

}

void ASQView::LoadData(BMessage *message)
{
	int i;
	char buffer[1025];
	BFile* file;
    entry_ref* ref;
	ref = new entry_ref();
	message->FindRef("refs", ref);
		
	file = new BFile(ref, B_READ_ONLY);
	file->InitCheck();
	ssize_t size; 
	size=file->Read(buffer,1024);     
	if((size)<0){
		return;}
	else{
		
		buffer[size] = 0;
	}
	
	int32 tempo;
	int32 togul;
	int32 ctrlA;
	int32 ctrlB;
	int32 dt;
	int endnote;
	char oA[24];
	char oB[24];
	char oC[24];
	int ov[4];
	int cv[4];
	char cA[24];
	char cB[24];
	char rv[24];
	int32 a[64],b[64],c[64];
	
	int N;
	
	BMenuItem* item;
	
	N=sscanf(buffer,"*** Q 1.0 Data File ***\ntempo= %ld\nplaymode= %ld\nCtrlA= %ld\nCtrlB= %ld\nduty= %ld\nendofnote= %d\noutputA= %d\t %s\noutputB= %d\t %s\noutputC= %d\t %s\nctrlA= %d\t %s\nctrlB= %d\t %s\nreverb= %d\t %s\n\tA\tB\tC\n0= \t%ld\t %ld\t %ld\n1= \t%ld\t %ld\t %ld\n2= \t%ld\t %ld\t %ld\n3= \t%ld\t %ld\t %ld\n4= \t%ld\t %ld\t %ld\n5= \t%ld\t %ld\t %ld\n6= \t%ld\t %ld\t %ld\n7= \t%ld\t %ld\t %ld\n8= \t%ld\t %ld\t %ld\n9= \t%ld\t %ld\t %ld\n10= \t%ld\t %ld\t %ld\n11= \t%ld\t %ld\t %ld\n12= \t%ld\t %ld\t %ld\n13= \t%ld\t %ld\t %ld\n14= \t%ld\t %ld\t %ld\n15= \t%ld\t %ld\t %ld\n"
	,
	&tempo,
	&togul,
	&ctrlA,
	&ctrlB,
	&dt,
	&endnote,
	&ov[1],oA,
	&ov[2],oB,
	&ov[3],oC,
	&cv[1],cA,
	&cv[2],cB,
	&cv[3],rv,
	&a[0],&b[0],&c[0],
	&a[1],&b[1],&c[1],
	&a[2],&b[2],&c[2],
	&a[3],&b[3],&c[3],
	&a[4],&b[4],&c[4],
	&a[5],&b[5],&c[5],
	&a[6],&b[6],&c[6],
	&a[7],&b[7],&c[7],
	&a[8],&b[8],&c[8],
	&a[9],&b[9],&c[9],
	&a[10],&b[10],&c[10],
	&a[11],&b[11],&c[11],
	&a[12],&b[12],&c[12],
	&a[13],&b[13],&c[13],
	&a[14],&b[14],&c[14],
	&a[15],&b[15],&c[15]);
	
	if(N<66){
		printf("N=%d\n",N);
		delete file;
		BAlert *myAlert;
		myAlert = new BAlert("Alert", 
		"This file is not a Q data file, or the file is corrupt.","OK",
		NULL,NULL,B_WIDTH_AS_USUAL,B_WARNING_ALERT); 
		myAlert->Go();
		
	}else{
		int32 t=tempo/2-2;
		temponob->SetValue(t);
		togulnob->SetValue(togul);
		portamentA->SetValue(ctrlA);
		portamentB->SetValue(ctrlB);
		duty->SetValue(dt);
		BMessage *m = new BMessage('lamc');
		m->AddInt16("No.",endnote);
		Window()->PostMessage(m,this);
		
		
		for (i=1;i<4;i++){
		
			m= new BMessage('inst');
			m->AddInt16("CH",i);
			m->AddInt16("inst",ov[i]);
			Window()->PostMessage(m);
			
		}
		for (i=1;i<3;i++){
		
			m= new BMessage('ctrl');
			m->AddInt16("Reverb",cv[3]);
			Window()->PostMessage(m);
			
		}
		
		m= new BMessage('rvrb');
		m->AddInt16("CH",i);
		m->AddInt16("data",cv[i]);
		Window()->PostMessage(m);
		
		item = outmenu[1]->Menu()->FindItem(oA);
		item->SetMarked(true);
		
		item = outmenu[2]->Menu()->FindItem(oB);
		item->SetMarked(true);
		
		item = outmenu[3]->Menu()->FindItem(oC);
		item->SetMarked(true);
	
		item = ctrlmenu[1]->Menu()->FindItem(cA);
		item->SetMarked(true);
		
		item = ctrlmenu[2]->Menu()->FindItem(cB);
		item->SetMarked(true);
		
		item = ctrlmenu[3]->Menu()->FindItem(rv);
		item->SetMarked(true);
		
		bool isplay=false;
		isplay=output->playing;
		output->playing=true;
		
		for(i=0;i<16;i++){
	
		 	volA[i]->SetValue(a[i]);
		 	volB[i]->SetValue(b[i]);
		 	volC[i]->SetValue(c[i]);
		 	
		 	
		}
		
		snooze(20000);
		output->playing=isplay;
		
		
		delete file;
		BMessage* msg= new BMessage('clea');
		BEntry* entry=new BEntry(ref);
		BEntry* dir_entry= new BEntry();
		entry->GetParent(dir_entry);
		dir_entry->GetRef(savedataref);
		savedatafilename=new BString(ref->name);
		msg->AddString("name",ref->name);
		Window()->PostMessage(msg);
		hasref=true;
	}
	
	

}

void ASQView::SaveSMFData(BMessage* message){
	uchar buffer[1024];
	BFile* file;
    entry_ref* ref;
    BDirectory *dir;
	BString* name;
	int i=1;
	
	
	name = new BString();
	if(message!=NULL){
	
		ref = new entry_ref();
		message->FindRef("directory", ref);
		dir = new BDirectory(ref);
		message->FindString("name",name);
			
	}else return;
	
	file = new BFile(dir,name->String(),B_READ_WRITE | B_CREATE_FILE | B_ERASE_FILE);
	file->InitCheck();
	
	//header chunk
	
	buffer[0]=0x4D;//"M"
	buffer[1]=0x54;//"T"
	buffer[2]=0x68;//"h"
	buffer[3]=0x64;//"d"
	buffer[4]=0x00;//data length
	buffer[5]=0x00;//
	buffer[6]=0x00;//
	buffer[7]=0x06;//			=6
	buffer[8]=0x00;//format
	buffer[9]=0x00;//			=0
	buffer[10]=0x00;//number of tracks
	buffer[11]=0x01;//			=1
	buffer[12]=0x01;//delta time
	buffer[13]=0xE0;//			=480
	
	
	//track chunk
	
	buffer[14]=0x4D;//"M"
	buffer[15]=0x54;//"T"
	buffer[16]=0x72;//"r"
	buffer[17]=0x6B;//"k"
	buffer[18]=0x00;//data length
	buffer[19]=0x00;
	buffer[20]=0x00;
	buffer[21]=0x00;//		=0
	
	//meta event
	//set measure
	buffer[22]=0x00;// delta time=0
	buffer[23]=0xff;// meta event
	buffer[24]=0x58;//set measure
	buffer[25]=0x04;
	buffer[26]=0x04;//
	buffer[27]=0x02;// 4/4
	buffer[28]=0x18;
	buffer[29]=0x08; 
	
	//tempo
	buffer[30]=0x00;// delta time=0
	buffer[31]=0xff;// meta event 
	buffer[32]=0x51;//			 set tempo
	buffer[33]=0x03;
	int32 tempo = 1000000 * 60 / (2*(temponob->Value())+4);
	buffer[34]=( tempo & 0xff0000 ) / 0xffff;
	buffer[35]=( tempo & 0x00ff00 ) / 0xff;
	buffer[36]=( tempo & 0x0000ff );
	int32 p= 37;
	//buffer[26]=0x00;//delta time = 0
	for (i=1;i<4;i++)
	{
		if(((output->status[i])>=0) && ((output->status[i])<128))
		{
		
		buffer[p]=0x00;//delta time = 0
		p++;
		buffer[p]=i-1+0xC0;//program change
		p++;
		buffer[p]=(output->status[i]);//program No.
		p++;
		
		}
	}
	
	int32 noteinterval=120; // interval during notes
	int32 notelength=(120*duty->Value())/128; 
	int32 time=0; // time of current event
	int32 ptime=0;// time of last event
	int32 dtime=0;// delta time during current event and last one
	
	for (i=0;i <= endofnote;i++)					// not < endofnote!!!
	{
	
		time=noteinterval*i;
		//Note On
		if((volA[i]->Value())>-1){
			dtime= time - ptime;
			if(dtime > 127){
				buffer[p]=dtime/128+0x80;
				p++;
				buffer[p]=dtime%128;
				p++;
			}else{ 
				buffer[p]=dtime;
				p++;
			}
			
			if ((output->status[1])==-10) buffer[p]=0x99;
			else buffer[p]=0x90;
			p++;
			buffer[p]=volA[i]->Value();
			p++;
			buffer[p]=127;
			p++;
			ptime=time;
		}
		if((volB[i]->Value())>-1){
			dtime= time - ptime;
			if(dtime > 127){
				buffer[p]=dtime/128+0x80;
				p++;
				buffer[p]=dtime%128;
				p++;
			}else{ 
				buffer[p]=dtime;
				p++;
			}
			
			if ((output->status[2])==-10) buffer[p]=0x99;
			else buffer[p]=0x91;
			p++;
			buffer[p]=volB[i]->Value();
			p++;
			buffer[p]=127;
			p++;
			ptime=time;
		}
		if((volC[i]->Value())>-1){
			dtime= time - ptime;
			if(dtime > 127){
				buffer[p]=dtime/128+0x80;
				p++;
				buffer[p]=dtime%128;
				p++;
			}else{ 
				buffer[p]=dtime;
				p++;
			}
			
			if ((output->status[3])==-10) buffer[p]=0x99;
			else buffer[p]=0x92;
			p++;
			buffer[p]=volC[i]->Value();
			p++;
			buffer[p]=127;
			p++;
			ptime=time;
		}
		//Note off
		time=noteinterval*i+notelength;
		if((volA[i]->Value())>-1){
			dtime= time - ptime;
			if(dtime > 127){
				buffer[p]=dtime/128+0x80;
				p++;
				buffer[p]=dtime%128;
				p++;
			}else{ 
				buffer[p]=dtime;
				p++;
			}
			
			if ((output->status[1])==-10) buffer[p]=0x89;
			else buffer[p]=0x80;
			p++;
			buffer[p]=volA[i]->Value();
			p++;
			buffer[p]=64;
			p++;
			ptime=time;
		}
		if((volB[i]->Value())>-1){
			dtime= time - ptime;
			if(dtime > 127){
				buffer[p]=dtime/128+0x80;
				p++;
				buffer[p]=dtime%128;
				p++;
			}else{ 
				buffer[p]=dtime;
				p++;
			}
			
			if ((output->status[2])==-10) buffer[p]=0x89;
			else buffer[p]=0x81;
			p++;
			buffer[p]=volB[i]->Value();
			p++;
			buffer[p]=64;
			p++;
			ptime=time;
		}
		if((volC[i]->Value())>-1){
			dtime= time - ptime;
			if(dtime > 127){
				buffer[p]=dtime/128+0x80;
				p++;
				buffer[p]=dtime%128;
				p++;
			}else{ 
				buffer[p]=dtime;
				p++;
			}
			
			if ((output->status[3])==-10) buffer[p]=0x89;
			else buffer[p]=0x82;
			p++;
			buffer[p]=volC[i]->Value();
			p++;
			buffer[p]=64;
			p++;
			ptime=time;
		}
		
	}
	buffer[p]=0xff;
	p++;
	buffer[p]=0x2f;
	p++;
	buffer[p]=0x00;
	
	//set data length of track chunk
	int32 tn=p-21;
	
	buffer[18]= (tn & 0xff000000) / 0x1000000;
	buffer[19]= (tn & 0x00ff0000) / 0x10000;
	buffer[20]= (tn & 0x0000ff00) / 0x100;
	buffer[21]= (tn & 0x000000ff);
	
	
	file->Write(buffer,p+1);
	
	BNodeInfo* fileinfo;
	fileinfo = new BNodeInfo();
	
	fileinfo->SetTo(file);
//	fileinfo->SetType("Midi Data");
	fileinfo->SetType("audio/x-midi");
	delete file;
	
}
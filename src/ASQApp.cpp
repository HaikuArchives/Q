// 
// ASQApp.cpp 
// 
#include "ASQApp.h" 
#include "ASQWindow.h" 

#include <List.h>
#include <Alert.h>
#include <Message.h>
#include <FilePanel.h>
#include <stdio.h>
#include <Mime.h>
#include <Roster.h>
#include <Path.h>


ASQApp::ASQApp():BApplication( MY_SIG ) 
{ 
    BRect frame; 
    char name[50];
//   	frame.Set( 5, 50, 640, 320 ); 
   	frame.Set( 100, 100, 735, 370 ); 
    sprintf(name,"Q # %ld",Team());
    window = new ASQWindow( frame, name ); 
    window->Show(); 

    refmsg= NULL;
    BMimeType* mytype = new BMimeType(MY_SIG);
    if(!mytype->IsInstalled())mytype->Install();
    
} 

void	ASQApp::MessageReceived(BMessage *msg)
{
	switch (msg->what) 
	{
		case 'str2':
				window->view->timer->PostMessage(msg,window->view->timer);
			break;
		case 'eclk':
				window->view->timer->PostMessage(msg,window->view->timer);
				
			break;
		case 'iclk':
				window->view->timer->PostMessage(msg,window->view->timer);
			break;
	
		case 'open':
				openpanel->Show();
			break;
		
		case 'refs':
				RefRequested();
			break;
			
		
	}
}

void ASQApp::AboutRequested(void){

	BAlert *myAlert;
	myAlert = new BAlert("about", "Q version 1.1\nAnalogue Sequencer Emulator\n\nby Masaaki Tani\nrevised by Dr. Hartmut Reh","OK"); 
	myAlert->SetShortcut(0, B_OK); 
	myAlert->Go();
}

void ASQApp::RefsReceived(BMessage *message)
{

	if(IsLaunching()){
	   refmsg = new BMessage(*message);
	}else window->PostMessage(message,window);
	
}

void ASQApp::RefRequested(void){

	BMessage* m;
	if (refmsg!=NULL)
	{
		m=new BMessage(*refmsg);
		window->PostMessage(m,window);
	}

}

int main() 
{ 
    ASQApp* app; 
    app = new ASQApp(); 
    app->Run(); 
    delete app; 
    return true; 
} 
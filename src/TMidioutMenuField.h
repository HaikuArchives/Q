//
//TMidioutMenuField.h
//

#ifndef TMIDIOUTMENUFIELD_H
#define TMIDIOUTMENUFIELD_H

#include <MenuField.h>
#include <Menu.h>

class	BMenuField;

class TMidioutMenuField : public BMenuField 
{ 
public: 
            TMidioutMenuField(BRect frame, const char *name, const char *label, BMenu *menu, uint32 command);
void		MouseDown(BPoint point); 

uint32 cmd;


}; 

#endif
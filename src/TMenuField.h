//
//TMenuField.h
//

#ifndef TMENUFIELD_H
#define TMENUFIELD_H

#include <MenuField.h>
#include <Menu.h>

class	BMenuField;

class TMenuField : public BMenuField 
{ 
public: 
            TMenuField(BRect frame, const char *name, const char *label, BMenu *menu, uint32 command);
void		MouseDown(BPoint point); 

uint32 cmd;


}; 

#endif
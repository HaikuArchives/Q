//
//TOutputMenuField.h
//

#ifndef TOUTPUTMENUFIELD_H
#define TOUTPUTMENUFIELD_H

#include <MenuField.h>
#include <Menu.h>

class	BMenuField;

class TOutputMenuField : public BMenuField 
{ 
public: 
            TOutputMenuField(BRect frame, const char *name, const char *label, BMenu *menu, int16 channel);
//void		MouseDown(BPoint point); 

int16 CH;


}; 

#endif
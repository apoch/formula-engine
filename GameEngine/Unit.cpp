#include "Pch.h"

#include "Unit.h"


unsigned s_hackRed = 0;
unsigned s_hackBlue = 0;


void Unit::SetRedColor(double red) {
	if(red > 0.0)
		++s_hackRed;
	else
		++s_hackBlue;
}



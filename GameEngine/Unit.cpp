#include "Pch.h"

#include "Unit.h"


unsigned s_hackRed = 0;
unsigned s_hackBlue = 0;


void Unit::SetRedColor(double) {
	++s_hackRed;
}


void Unit::SetBlueColor(double) {
	++s_hackBlue;
}


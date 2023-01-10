#pragma once

#include "Api.h"
#include "keyboard.h"
#include "script.h"

class SnowBlanket
{
private:
	Api api;
	bool winterBlanket;

public:
	SnowBlanket();
	void addSnowBlanket(int coverage);
	void removeSnowBlanket(char* replacementWeather);
	void toggleWinterBlanket();
	void tick();
};

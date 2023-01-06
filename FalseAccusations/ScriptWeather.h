#pragma once

#include "Api.h"
#include "keyboard.h"

class ScriptWeather
{
private:
	Api api;
	bool winterBlanket;

public:
	ScriptWeather();
	void addSnowBlanket(int coverage);
	void removeSnowBlanket(char* replacementWeather);
	void toggleWinterBlanket();
	void tick();
};

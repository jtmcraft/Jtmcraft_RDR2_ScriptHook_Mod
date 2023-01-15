#pragma once

#include <api/Api.h>

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

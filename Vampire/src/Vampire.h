#pragma once

#include <string>
#include "VampireWeather.h"
#include <api/Api.h>

class Vampire
{
private:
	Api api;
	Ped vampire;
	VampireWeather weather;
	bool vampireWasSpawned;

	void spawnVampire();
	bool evilOmen();
	bool midnight();
	bool morning();
	bool defeatVampire();

public:
	Vampire();
	void tick();
};

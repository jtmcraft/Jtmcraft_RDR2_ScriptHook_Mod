#pragma once

#include <string>
#include "../../inc/types.h"
#include "keyboard.h"
#include "Api.h"
#include "VampireWeather.h"

class Vampire
{
private:
	Api api;
	Ped vampire;
	VampireWeather weather;
	bool vampireWasSpawned;

	void spawnVampire();

public:
	Vampire();
	void tick();
};

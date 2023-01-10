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
	bool okToSpawnVampire;
	VampireWeather weather;

	void spawnVampire();
	bool isVampireOutOfRange();

public:
	Vampire();
	void tick();
	bool stillAlive();
};

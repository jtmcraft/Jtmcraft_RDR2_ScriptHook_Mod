#pragma once

#include <string>
#include "../../inc/types.h"
#include "keyboard.h"
#include "Api.h"

class Vampire
{
private:
	Api api;
	Ped vampire;
	bool okToSpawnVampire;

	void spawnVampire();
	bool isVampireOutOfRange();

public:
	Vampire();
	void tick();
};

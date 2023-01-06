#pragma once

#include "../../inc/types.h"
#include "keyboard.h"
#include "Api.h"

class ScriptVampire
{
private:
	Api api;
	Ped vampire;
	bool okToSpawnVampire;
	bool vampireHeadshotHandled;

	void spawnVampire();
	bool isVampireOutOfRange();

public:
	ScriptVampire();
	void tick();
};

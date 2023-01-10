#pragma once

#include <string>
#include "../../inc/types.h"
#include "keyboard.h"
#include "Api.h"

class ScriptVampire
{
private:
	Api api;
	Ped vampire;
	bool okToSpawnVampire;

	void spawnVampire();
	bool isVampireOutOfRange();

public:
	ScriptVampire();
	void tick();
};

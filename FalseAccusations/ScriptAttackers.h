#pragma once

#include "../../inc/types.h"
#include "keyboard.h"
#include "Api.h"

class ScriptAttackers
{
private:
	Api api;
	int groupId;
	void spawnAttackers();
	void createAttacker(char* model, Hash weaponHash, int ammo, int groupId, bool leader, float distance, float a, float b);

public:
	ScriptAttackers();
	void tick();
};


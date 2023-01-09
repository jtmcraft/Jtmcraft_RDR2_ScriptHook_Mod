#pragma once

#include <vector>
#include "../../inc/types.h"
#include "keyboard.h"
#include "Api.h"
#include "ScriptAttacker.h"
#include "ScriptLogger.h"

using namespace std;

class ScriptAttackers
{
private:
	Api api;
	ScriptLogger logger;
	int groupId;
	Ped attackers[5];
	vector<ScriptAttacker> attackers;
	bool okToSpawn;
	void spawnAttackers();
	Ped createAttacker(char* model, Hash weaponHash, int ammo, int groupId, bool leader, float distance, float a, float b);
	bool attackersRemain();

public:
	ScriptAttackers();
	void setLogger(ScriptLogger logger);
	void tick();
};


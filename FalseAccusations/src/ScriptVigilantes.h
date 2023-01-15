#pragma once
#include <api/Api.h>
#include <api/ScriptLogger.h>

class ScriptVigilantes
{
private:
	Api api;
	ScriptLogger logger;
	bool alreadySpawned;
	array<Ped, 32> peds;
	void spawnVigilantes();

public:
	ScriptVigilantes();
	void setLogger(ScriptLogger logger);
	void tick();
};


#pragma once
#include <api/Api.h>
#include <api/ScriptLogger.h>

class ScriptVigilantes
{
private:
	Api api;
	ScriptLogger logger;
	bool alreadySpawned;
	array<Ped, 16> peds{};
	void spawnVigilantes();
	void clearSpawnedPeds(int distance);

public:
	ScriptVigilantes();
	void setLogger(ScriptLogger logger);
	void tick();
};


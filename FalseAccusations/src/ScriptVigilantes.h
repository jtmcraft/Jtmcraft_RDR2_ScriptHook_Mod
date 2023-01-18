#pragma once

#include <api/Api.h>
#include <api/ScriptLogger.h>
#include <random>

class ScriptVigilantes
{
private:
	Api api;
	ScriptLogger logger;
	mt19937 rng;
	bool alreadySpawned;
	array<Vector3, 16> vigilanteSpawnCoords;
	array<Ped, 16> vigilantePeds;
	array<char*, 16> vigilanteModels;
	array<Hash, 2> vigilanteWeapons;
	int vigilantesAlive;

	void spawnVigilantes();
	void clearSpawnedPeds(int distance);
	void detectPlayer(int distance);

public:
	ScriptVigilantes();
	void setLogger(ScriptLogger logger);
	void setRng(mt19937 rng);
	void tick();
};

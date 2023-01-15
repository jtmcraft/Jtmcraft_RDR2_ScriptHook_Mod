#include "ScriptVigilantes.h"

ScriptVigilantes::ScriptVigilantes() {
	api = Api();
	alreadySpawned = false;
}

void ScriptVigilantes::setLogger(ScriptLogger logger) {
	this->logger = logger;
}

void ScriptVigilantes::tick() {
	int gameHour = api.getGameHour();

	if (gameHour == 16 && alreadySpawned) {
		for (int i = 0; i < 32; i++) {
			if (!api.isPedDeadOrDying(peds[i])) {
				if (api.distanceBetween(api.getPlayerCoords(), api.getEntityCoords(peds[i])) > 200) {
					api.deletePed(peds[i]);
				}
			}
		}

		alreadySpawned = false;
	}

	if (gameHour == 17 && !alreadySpawned) {
		spawnVigilantes();
		alreadySpawned = true;
	}
}

void ScriptVigilantes::spawnVigilantes() {
	array<Vector3, 16> wave1 = api.findLocationsAroundPlayer(120, 5, 30);
	array<Vector3, 16> wave2 = api.findLocationsAroundPlayer(120, 5, 30);
	int i;
	Vector3 playerCoords = api.getPlayerCoords();

	for (i = 0; i < 16; i++) {
		peds[i] = api.spawnPedAt("CS_crackpotRobot", wave1[i], playerCoords, true);
	}

	for (; i < 32; i++) {
		peds[i] = api.spawnPedAt("CS_crackpotRobot", wave2[i], playerCoords, true);
	}
}

#include "ScriptVigilantes.h"

ScriptVigilantes::ScriptVigilantes() {
	api = Api();
	alreadySpawned = false;
}

void ScriptVigilantes::setLogger(ScriptLogger logger) {
	this->logger = logger;
}

void ScriptVigilantes::clearSpawnedPeds(int distance) {
	for (int i = 0; i < 16; i++) {
		if (!api.isPedDeadOrDying(peds[i])) {
			if (api.distanceBetween(api.getPlayerCoords(), api.getEntityCoords(peds[i])) > distance) {
				api.deletePed(peds[i]);
			}
		}
	}

	alreadySpawned = false;
}

void ScriptVigilantes::tick() {
	int gameHour = api.getGameHour();

	if (IsKeyJustUp(VK_KEY_Y)) {
		clearSpawnedPeds(0);
	}

	if (gameHour != 17) {
		clearSpawnedPeds(400);
	}

	if (gameHour == 17 && !alreadySpawned) {
		spawnVigilantes();
		alreadySpawned = true;
	}
}

void ScriptVigilantes::spawnVigilantes() {
	array<Vector3, 16> wave = api.findLocationsAroundPlayer(200, 0, 200);
	int i;
	Vector3 playerCoords = api.getPlayerCoords();

	for (i = 0; i < 16; i++) {
		peds[i] = api.spawnPedAt("CS_crackpotRobot", wave[i], playerCoords, true);
	}
}

#include "ScriptVampire.h"

ScriptVampire::ScriptVampire() {
	api = Api();
	vampire = NULL;
	okToSpawnVampire = true;
}

bool ScriptVampire::isVampireOutOfRange() {
	return api.distanceBetween(api.getEntityCoords(vampire), api.getPlayerCoords()) > 140;
}

void ScriptVampire::spawnVampire() {
	vampire = api.spawnRelativeToPlayer("CS_Vampire", 30, 0, 30);
	okToSpawnVampire = false;
}

void ScriptVampire::tick() {
	int gameHour = api.getGameHour();

	if (IsKeyJustUp(VK_KEY_N)) {
		gameHour += 1;

		if (gameHour > 23) {
			gameHour = 0;
		}

		api.setGameTime(gameHour, 45, 0);
		return;
	}

	gameHour = api.getGameHour();
	bool isAlive = vampire != NULL && !api.isEntityDead(vampire);

	if (isAlive) {
		api.setWeather("FOG");
	}
	else {
		if (vampire != NULL && api.detectHeadShot(vampire)) {
			api.notifyHeadShot();
		}
		api.setWeather("SUNNY");

		vampire = NULL;
	}

	if (gameHour > 5) {
		if (isAlive) {
			api.addExplosion(api.getEntityCoords(vampire));
			api.setEntityHealth(vampire, 0);
		}

		vampire = NULL;
		okToSpawnVampire = true;

		return;
	}

	if (isAlive && isVampireOutOfRange()) {
		api.deletePed(vampire);
		spawnVampire();

		return;
	}

	if (okToSpawnVampire) {
		if (gameHour == 23) {
			api.setWeather("FOG");
		}

		if (gameHour == 0) {
			spawnVampire();
		}
	}
}

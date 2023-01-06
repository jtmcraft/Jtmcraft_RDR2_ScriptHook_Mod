#include "ScriptVampire.h"

ScriptVampire::ScriptVampire() {
	api = Api();
	vampire = NULL;
	okToSpawnVampire = true;
	vampireHeadshotHandled = false;
}

bool ScriptVampire::isVampireOutOfRange() {
	return api.distanceBetween(api.getEntityCoords(vampire), api.getPlayerCoords()) > 140;
}

void ScriptVampire::spawnVampire() {
	vampire = api.spawnHostilePedNearPlayer("CS_Vampire");
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

	if (vampire != NULL && !vampireHeadshotHandled && api.detectHeadShot(vampire)) {
		vampireHeadshotHandled = true;
		api.toast("You headshot the vampire.");
	}

	if (isAlive) {
		if (api.detectHeadShot(vampire)) {
			api.toast("You scored a headshot against the vampire.");
		}

		api.setWeather("FOG");
	}

	if (gameHour > 6) {
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

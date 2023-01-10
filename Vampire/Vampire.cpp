#include "Vampire.h"

Vampire::Vampire() {
	api = Api();
	vampire = NULL;
	okToSpawnVampire = true;
	weather = VampireWeather();
}

bool Vampire::isVampireOutOfRange() {
	return api.distanceBetween(api.getEntityCoords(vampire), api.getPlayerCoords()) > 150;
}

void Vampire::spawnVampire() {
	vampire = api.spawnRelativeToPlayer("CS_Vampire", 30, 0, 30, false);
	api.addMoneyLoot(vampire, api.randInt(1000, 2000));
	okToSpawnVampire = false;
}

bool Vampire::stillAlive() {
	return vampire != NULL && api.isEntityDead(vampire);
}

void Vampire::tick() {
	int gameHour = api.getGameHour();

	if (IsKeyJustUp(VK_KEY_N)) {
		gameHour += 1;

		if (gameHour > 23) {
			gameHour = 0;
		}

		api.setGameTime(gameHour, 45, 0);

		char timeStr[255];
		sprintf_s(timeStr, "Time: %d:45", gameHour);
		api.notificationTopLeft(timeStr, 1000);

		return;
	}

	gameHour = api.getGameHour();
	bool isAlive = vampire != NULL && !api.isEntityDead(vampire);

	if (gameHour > 5 && gameHour < 22) {
		if (isAlive) {
			api.addExplosion(api.getEntityCoords(vampire));
			api.setEntityHealth(vampire, 0);
			WAIT(100);
			api.notificationAlert("The vampire died of natural causes.");
			weather.fogOut();
		}

		vampire = NULL;
		okToSpawnVampire = true;

		return;
	}

	if (!okToSpawnVampire && !isAlive) {
		bool isHeadShot = api.detectHeadShot(vampire);
		vampire = NULL;

		api.notificationTitled("Victory", "You defeated the vampire.", "honor_display", "honor_good", "COLOR_PURE_WHITE", 3000);
		if (isHeadShot) {
			api.notifyHeadShot();
		}

		okToSpawnVampire = true;
		weather.fogOut();

		return;
	}

	if (isAlive && isVampireOutOfRange()) {
		api.deletePed(vampire);
		spawnVampire();

		return;
	}

	if (okToSpawnVampire) {
		if (gameHour == 23 && !weather.isFoggy()) {
			weather.fogIn();
		}

		if (gameHour == 0) {
			spawnVampire();
		}
	}
}

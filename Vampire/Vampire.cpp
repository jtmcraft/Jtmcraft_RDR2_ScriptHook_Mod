#include "Vampire.h"

Vampire::Vampire() {
	api = Api();
	vampire = 0;
	weather = VampireWeather();
	vampireWasSpawned = false;
}

void Vampire::spawnVampire() {
	vampire = api.spawnRelativeToPlayer("CS_Vampire", 30, 0, 30, false);
	api.addMoneyLoot(vampire, api.randInt(1000, 2000));
	api.givePedWeapon(vampire, api.getHash("weapon_melee_knife_vampire"), 1);
	vampireWasSpawned = true;
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
	api.removeAllPickups(api.getHash("PICKUP_WEAPON_MELEE_KNIFE_VAMPIRE"));

	if (gameHour == 6) {
		if (vampire != 0 && !api.isPedDeadOrDying(vampire)) {
			api.addExplosion(api.getEntityCoords(vampire));
			api.setEntityHealth(vampire, 0);
			WAIT(100);
			api.notificationAlert("The vampire died of natural causes.");
			weather.fogOut();
		}

		vampire = 0;
		vampireWasSpawned = false;

		return;
	}

	if (!vampireWasSpawned && gameHour == 0 && vampire == 0) {
		spawnVampire();

		return;
	}

	if (gameHour < 6) {
		if (vampire != 0 && api.isPedDeadOrDying(vampire)) {
			bool isHeadShot = api.detectHeadShot(vampire);

			api.notificationTitled("Victory", "You defeated the vampire.", "honor_display", "honor_good", "COLOR_PURE_WHITE", 3000);
			if (isHeadShot) {
				api.notifyHeadShot();
			}

			vampire = 0;
			weather.fogOut();
		}

		return;
	}

	if (gameHour == 23 && !weather.isFoggy()) {
		weather.fogIn();

		return;
	}
}

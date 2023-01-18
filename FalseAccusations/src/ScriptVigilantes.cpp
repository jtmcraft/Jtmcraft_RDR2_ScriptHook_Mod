#include "ScriptVigilantes.h"

ScriptVigilantes::ScriptVigilantes() {
	api = Api();
	alreadySpawned = false;
	vigilanteModels = {
		"U_M_M_HtlForeman_01",
		"U_M_M_BwmStablehand_01",
		"S_M_M_FussarHenchman_01",
		"S_M_M_DispatchLeaderRural_01",
		"S_M_M_ASBCowpoke_01",
		"S_M_M_AmbientLawRural_01",
		"RE_MOONSHINECAMP_MALES_01",
		"MES_MARSTON6_MALES_01",
		"MES_ABIGAIL2_MALES_01",
		"G_M_Y_UniExConfeds_01",
		"G_M_Y_UNIEXCONFEDS_02",
		"G_M_M_UniGrays_01",
		"G_M_M_UniGrays_02",
		"U_M_M_RhdSheriff_01",
		"CS_FamousGunslinger_06",
		"CS_AberdeenPigFarmer"
	};
	vigilanteWeapons = { api.repeaterCarbine(), api.cattlemanRevolver() };
	vigilantesAlive = 0;
}

void ScriptVigilantes::setLogger(ScriptLogger logger) {
	this->logger = logger;
}

void ScriptVigilantes::setRng(mt19937 rng) {
	this->rng = rng;
}

void ScriptVigilantes::clearSpawnedPeds(int distance) {
	for (int i = 0; i < 16; i++) {
		if (!api.isPedDeadOrDying(vigilantePeds[i])) {
			if (api.distanceBetween(api.getPlayerCoords(), api.getEntityCoords(vigilantePeds[i])) > distance) {
				api.deletePed(vigilantePeds[i]);
				vigilantePeds[i] = 0;
			}
		}
	}
}

void ScriptVigilantes::detectPlayer(int distance) {
	int alive = 0;

	for (int i = 0; i < 16; i++) {
		if (!api.isPedDeadOrDying(vigilantePeds[i])) {
			alive += 1;

			float x = api.distanceBetween(api.getPlayerCoords(), api.getEntityCoords(vigilantePeds[i]));
			if (x <= distance) {
				if (!api.hasBlip(vigilantePeds[i])) {
					api.enemyBlip(vigilantePeds[i]);
				}
				api.taskAttackPlayer(vigilantePeds[i]);
			}
			else {
				Vector3 coords = api.getEntityCoords(vigilantePeds[i]);
				api.taskWanderInArea(vigilantePeds[i], coords.x, coords.y, coords.z);
			}
		}
	}

	if (vigilantesAlive != alive) {
		vigilantesAlive = alive;
		char icon[255];

		if (vigilantesAlive > 0) {
			sprintf_s(icon, "overhead_kill_%d", vigilantesAlive);
		}
		else {
			strcpy_s(icon, "overhead_ambient_hunter");
		}

		api.toastRight("Vigilantes", "overhead", icon);
	}
}

void ScriptVigilantes::tick() {
	if (IsKeyJustUp(VK_KEY_Y)) {
		clearSpawnedPeds(0);
	}

	detectPlayer(100);

	int gameHour = api.getGameHour();

	if (gameHour == 17 && !alreadySpawned) {
		spawnVigilantes();
		alreadySpawned = true;
	}

	if (gameHour != 17) {
		alreadySpawned = false;
	}
}

void ScriptVigilantes::spawnVigilantes() {
	vigilanteSpawnCoords = api.findLocationsAroundPlayer(200, 0, 200);
	shuffle(vigilanteModels.begin(), vigilanteModels.end(), rng);

	for (int i = 0; i < 16; i++) {
		if (vigilantePeds[i] == 0) {
			vigilantePeds[i] = api.spawnPedAt(vigilanteModels[i], vigilanteSpawnCoords[i], api.getPlayerCoords(), false, false);
			api.addMoneyLoot(vigilantePeds[i], api.randInt(400, 600));

			if (api.randInt(0, 2)) {
				api.givePedWeapon(vigilantePeds[i], vigilanteWeapons[1], 40);
			}
			else {
				api.givePedWeapon(vigilantePeds[i], vigilanteWeapons[0], 100);
			}
		}
	}
}

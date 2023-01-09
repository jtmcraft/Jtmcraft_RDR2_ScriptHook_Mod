#include "ScriptAttackers.h"

ScriptAttackers::ScriptAttackers() {
	api = Api();
	groupId = 0;
	okToSpawn = true;
	for (int i = 0; i < 5; i++) {
		attackers[i] = 0;
	}
}

void ScriptAttackers::setLogger(ScriptLogger logger) {
	this->logger = logger;
}

void ScriptAttackers::spawnAttackers() {
	Hash carbine = 0xF5175BA1;
	Hash revolver = 0x169F59F7;
	groupId = api.createGroup();
	float distance = 30 + api.randFloat(0, 30);
	float randomA = 0;
	float randomB = 30;
	int i;

	for (i = 0; i < 5; i++) {
		api.deletePed(attackers[i]);
		attackers[i] = 0;
	}

	logger.log("Spawning attackers.");
	api.notificationTitled("Danger", "Some folks are out to get you.", "overhead", "overhead_ambient_hunter", "COLOR_PURE_WHITE", 3000);

	if (api.randInt(0, 2)) {
		for (i = 0; i < 4; i++) {
			attackers[i] = createAttacker("RE_RALLYSETUP_MALES_01", revolver, 40, groupId, false, distance, randomA, randomB);
		}

		attackers[i] = createAttacker("RE_RALLY_MALES_01", carbine, 100, groupId, true, distance, randomA, randomB);
	} else {
		for (i = 0; i < 5; i++) {
			attackers[i] = createAttacker("CS_crackpotRobot", revolver, 40, groupId, i == 0, distance, randomA, randomB);
		}
	}
}

Ped ScriptAttackers::createAttacker(char* model, Hash weaponHash, int ammo, int groupId, bool leader, float distance, float a, float b) {
	Ped ped = api.spawnRelativeToPlayer(model, distance, a, b);
	api.givePedWeapon(ped, weaponHash, ammo);
	api.addMoneyLoot(ped, api.randInt(500, 1000));

	if (leader) {
		api.setPedGroupLeader(ped, groupId);
	}
	else {
		api.setPedGroupMember(ped, groupId);
	}

	return ped;
}

bool ScriptAttackers::attackersRemain() {
	for (vector<ScriptAttacker>::iterator it = attackers.begin(); it != attackers.end(); it++) {
		if (it->isAlive()) {
			return true;
		}
	}

	return false;
}

void ScriptAttackers::tick() {
	if (IsKeyJustUp(VK_KEY_Y)) {
		if (okToSpawn) {
			spawnAttackers();
			okToSpawn = false;
			return;
		}
	}

	if (!okToSpawn) {
		bool isAllDead = true;
		int i;
		int headShots = 0;

		for (i = 0; i < 5; i++) {
			if (attackers[i] != 0 && !api.isEntityDead(attackers[i])) {
				isAllDead = false;
			}

			if (attackers[i] != 0 && api.detectHeadShot(attackers[i])) {
				headShots++;
			}
		}

		if (isAllDead) {
			WAIT(2500);
			char logMsg[255];
			sprintf_s(logMsg, "Killed 'em, scored %d headshots.", headShots);
			logger.log(logMsg);

			api.notificationTitled("Victory", "You defeated the bad guys.", "honor_display", "honor_good", "COLOR_PURE_WHITE", 3000);
			for (i = 0; i < 5; i++) {
				api.deletePed(attackers[i]);
				attackers[i] = 0;
			}

			for (i = 0; i < headShots; i++) {
				api.notifyHeadShot();
				//api.addMoney(api.randInt(5000, 10000));
			}

			okToSpawn = true;
		}
	}
}

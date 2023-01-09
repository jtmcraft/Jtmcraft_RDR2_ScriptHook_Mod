#include "ScriptAttackers.h"

ScriptAttackers::ScriptAttackers() {
	api = Api();
	groupId = 0;
}

void ScriptAttackers::spawnAttackers() {
	Hash carbine = 0xF5175BA1;
	Hash revolver = 0x169F59F7;
	groupId = api.createGroup();
	float distance = 30 + api.randFloat(0, 30);
	float randomA = 0;
	float randomB = 30;
	int i;

	api.notificationTitled("Danger", "Some folks are out to get you.", "overhead", "overhead_ambient_hunter", "COLOR_PURE_WHITE", 3000);

	if (api.randInt(0, 2)) {
		for (i = 0; i < api.randInt(3, 5); i++) {
			createAttacker("RE_RALLYSETUP_MALES_01", revolver, 40, groupId, false, distance, randomA, randomB);
		}

		createAttacker("RE_RALLY_MALES_01", carbine, 100, groupId, true, distance, randomA, randomB);
	} else {
		for (i = 0; i < 4; i++) {
			createAttacker("CS_crackpotRobot", revolver, 40, groupId, i == 0, distance, randomA, randomB);
		}
	}
}

void ScriptAttackers::createAttacker(char* model, Hash weaponHash, int ammo, int groupId, bool leader, float distance, float a, float b) {
	Ped ped = api.spawnRelativeToPlayer(model, distance, a, b);
	api.givePedWeapon(ped, weaponHash, ammo);

	if (leader) {
		api.setPedGroupLeader(ped, groupId);
	}
	else {
		api.setPedGroupMember(ped, groupId);
	}
}

void ScriptAttackers::tick() {
	if (IsKeyJustUp(VK_KEY_Y)) {
		spawnAttackers();
	}
}

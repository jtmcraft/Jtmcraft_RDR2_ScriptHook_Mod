#include "ScriptAttacker.h"

ScriptAttacker::ScriptAttacker(Ped ped) {
	this->ped = ped;
	this->attacking = false;
	this->api = Api();
}

Ped ScriptAttacker::getPed() {
	return ped;
}

void ScriptAttacker::begin() {
	attacking = true;
}

void ScriptAttacker::tick() {
	if (!attacking) {
		return;
	}


}

void ScriptAttacker::end() {
	attacking = false;
}

bool ScriptAttacker::isAttacking() {
	return attacking;
}

bool ScriptAttacker::isAlive() {
	return api.isEntityDead(ped);
}

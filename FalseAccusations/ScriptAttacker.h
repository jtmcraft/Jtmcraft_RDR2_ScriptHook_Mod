#pragma once

#include "../../inc/types.h"
#include "../../inc/natives.h"
#include "Api.h"

class ScriptAttacker
{
private:
	Api api;
	Ped ped;
	bool attacking;

public:
	ScriptAttacker(Ped ped);
	Ped getPed();
	void begin();
	void tick();
	void end();
	bool isAttacking();
	bool isAlive();
};


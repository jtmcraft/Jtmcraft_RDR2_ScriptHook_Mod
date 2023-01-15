#pragma once

#include <sstream>
#include <api/Api.h>
#include <api/ScriptLogger.h>

class DevMode
{
private:
	Api api;
	ScriptLogger logger;
	void savePlayerCoords();
	void giveMoney();
	void toggleInvinciblePlayer();
	void spawnTestEnemy();

public:
	DevMode();
	void setLogger(ScriptLogger logger);
	void tick();
};

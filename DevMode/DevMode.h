#pragma once

#include <sstream>
#include "keyboard.h"
#include "Api.h"
#include "ScriptLogger.h"

class DevMode
{
private:
	Api api;
	ScriptLogger logger;
	void savePlayerCoords();
	void giveMoney();
	void toggleInvinciblePlayer();

public:
	DevMode();
	void setLogger(ScriptLogger logger);
	void tick();
};

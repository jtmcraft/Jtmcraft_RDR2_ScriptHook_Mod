#pragma once

#include <sstream>
#include "keyboard.h"
#include "Api.h"
#include "ScriptLogger.h"

class ScriptDevMode
{
private:
	Api api;
	ScriptLogger logger;
	void savePlayerCoords();
	void giveMoney();
	void toggleInvinciblePlayer();

public:
	ScriptDevMode();
	void setLogger(ScriptLogger logger);
	void tick();
};

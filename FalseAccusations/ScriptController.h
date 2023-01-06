#pragma once

#include <string>
#include "Api.h"
#include "ScriptCrimeController.h"
#include "ScriptLogger.h"
#include "ScriptDataManager.h"
#include "ScriptDataModel.h"
#include "keyboard.h"

class ScriptController
{
private:
	Api api;
	ScriptDataManager dataManager;
	ScriptCrimeController crimeManager;
	ScriptLogger logger;

public:
	ScriptController();
	void handleFalseAccusation(double elapsedFalseAccusation, bool shouldSave);
	bool tryToFalselyAccusePlayer();
	void log(const char* text);
	bool isPaused();
};

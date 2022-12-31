#pragma once

#include "Api.h"
#include "ScriptCrimeManager.h"
#include "ScriptLogger.h"
#include "ScriptDataManager.h"
#include "ScriptDataModel.h"
#include "keyboard.h"

class ScriptController
{
private:
	Api api;
	ScriptDataManager dataManager;
	ScriptCrimeManager crimeManager;
	ScriptLogger logger;

public:
	ScriptController();
	void handleFalseAccusation(double elapsedFalseAccusation, bool shouldSave);
	bool tryToFalselyAccusePlayer();
	void drawUserInterface();
	void giveMoney();
	void saveCoordinates();
	void toggleDevMode();
	void log(const char* text);
};

#pragma once

#include <string>
#include "Api.h"
#include "ScriptCrimeManager.h"
#include "ScriptLogger.h"
#include "ScriptDataManager.h"
#include "ScriptDataModel.h"
#include "keyboard.h"

constexpr char* SNOWY_WEATHER = "SNOWLIGHT";
constexpr char* SUNNY_WEATHER = "SUNNY";

class ScriptController
{
private:
	Api api;
	ScriptDataManager dataManager;
	ScriptCrimeManager crimeManager;
	ScriptLogger logger;
	Ped vampire;
	bool okToSpawnVampire;
	bool isWinterBlanket;

	void toggleWinterBlanket();
	void spawnVampire();
	bool isVampireOutOfRange();

public:
	ScriptController();
	void handleFalseAccusation(double elapsedFalseAccusation, bool shouldSave);
	bool tryToFalselyAccusePlayer();
	void drawUserInterface();
	void giveMoney();
	void saveCoordinates();
	void toggleDevMode();
	void changeWeather();
	void log(const char* text);
	bool isPaused();
	void updateVampire();
};

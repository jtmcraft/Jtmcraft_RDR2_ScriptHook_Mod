#pragma once

#include "Api.h"
#include "ScriptController.h"
#include "ScriptCrimeController.h"
#include "ScriptDataManager.h"
#include "ScriptDevMode.h"
#include "ScriptInfoPanel.h"
#include "ScriptLogger.h"
#include "ScriptVampire.h"
#include "ScriptWeather.h"
#include "script.h"

using namespace std;

void ScriptMain() {
	srand((unsigned int) time(NULL));

	ScriptController controller = ScriptController();
	ScriptDevMode devMode = ScriptDevMode();
	ScriptDataManager dataManager = ScriptDataManager();
	ScriptCrimeController crimeManager = ScriptCrimeController();
	ScriptInfoPanel infoPanel = ScriptInfoPanel();
	ScriptLogger logger = ScriptLogger();
	ScriptVampire vampire = ScriptVampire();
	ScriptWeather weather = ScriptWeather();
	
	crimeManager.setDataModel(dataManager.read());
	devMode.setLogger(logger);

	auto startAutoSave = chrono::steady_clock::now();
	auto startFalseAccusation = chrono::steady_clock::now();

	while (true) {
		devMode.tick();
		infoPanel.tick(crimeManager.getDataModel());
		vampire.tick();
		weather.tick();

		bool shouldSave = false;
		auto now = chrono::steady_clock::now();
		chrono::duration<double> elapsedAutoSave = now - startAutoSave;
		chrono::duration<double> elapsedFalseAccusation = now - startFalseAccusation;

		if (elapsedFalseAccusation.count() >= 1) {
			if (elapsedAutoSave.count() >= 15) {
				shouldSave = true;
				startAutoSave = now;
			}

			controller.handleFalseAccusation(elapsedFalseAccusation.count(), shouldSave);
			startFalseAccusation = now;
		}

		WAIT(0);
	}
}

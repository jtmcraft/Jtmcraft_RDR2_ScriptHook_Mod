#pragma once

#include "Api.h"
#include "ScriptDataManager.h"
#include "ScriptLogger.h"
#include "ScriptCrimeManager.h"
#include "ScriptController.h"
#include "script.h"

using namespace std;

void ScriptMain() {
	ScriptController controller = ScriptController();
	auto startAutoSave = chrono::steady_clock::now();
	auto startFalseAccusation = chrono::steady_clock::now();

	while (true) {
		controller.drawUserInterface();
		controller.giveMoney();
		controller.saveCoordinates();
		controller.toggleDevMode();
		controller.changeWeather();
		controller.updateVampire();

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

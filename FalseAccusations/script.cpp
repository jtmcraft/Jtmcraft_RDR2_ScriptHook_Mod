#pragma once

#include "Api.h"
#include "ScriptCrimeController.h"
#include "ScriptDevMode.h"
#include "ScriptLogger.h"
#include "ScriptVampire.h"
#include "ScriptWeather.h"
#include "script.h"

using namespace std;

void ScriptMain() {
	srand((unsigned int) time(NULL));

	ScriptDevMode devMode = ScriptDevMode();
	ScriptCrimeController crime = ScriptCrimeController();
	ScriptLogger logger = ScriptLogger();
	ScriptVampire vampire = ScriptVampire();
	ScriptWeather weather = ScriptWeather();

	devMode.setLogger(logger);

	while (true) {
		crime.tick();
		devMode.tick();
		vampire.tick();
		weather.tick();
		WAIT(0);
	}
}

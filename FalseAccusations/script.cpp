#pragma once

#include <string>
#include "Api.h"
#include "ScriptAttackers.h"
#include "ScriptCrime.h"
#include "ScriptDevMode.h"
#include "ScriptLogger.h"
#include "ScriptVampire.h"
#include "ScriptWeather.h"
#include "script.h"

using namespace std;

void ScriptMain() {
	srand((unsigned int) time(NULL));

	ScriptAttackers attackers = ScriptAttackers();
	ScriptDevMode devMode = ScriptDevMode();
	ScriptCrime crime = ScriptCrime();
	ScriptLogger logger = ScriptLogger();
	ScriptVampire vampire = ScriptVampire();
	ScriptWeather weather = ScriptWeather();

	devMode.setLogger(logger);

	logger.log(string("Starting jtmcraft's RDR2 mod.").c_str());

	while (true) {
		attackers.tick();
		crime.tick();
		devMode.tick();
		vampire.tick();
		weather.tick();
		WAIT(0);
	}
}

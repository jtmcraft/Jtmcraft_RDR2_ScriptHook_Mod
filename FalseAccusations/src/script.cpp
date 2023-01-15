#pragma once

#include <string>
#include <api/ScriptLogger.h>
#include <inc/main.h>
#include "ScriptCrime.h"
#include "ScriptVigilantes.h"

using namespace std;

void ScriptMain() {
	srand((unsigned int) time(NULL));

	ScriptCrime crime = ScriptCrime();
	ScriptLogger logger = ScriptLogger();
	ScriptVigilantes vigilantes = ScriptVigilantes();
	vigilantes.setLogger(logger);

	logger.log("Starting jtmcraft's RDR2 mod.");

	while (true) {
		crime.tick();
		vigilantes.tick();

		WAIT(0);
	}
}

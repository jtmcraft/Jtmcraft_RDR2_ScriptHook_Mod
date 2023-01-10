#pragma once

#include <string>
#include "Api.h"
#include "ScriptCrime.h"
#include "ScriptLogger.h"
#include "script.h"

using namespace std;

void ScriptMain() {
	srand((unsigned int) time(NULL));

	ScriptCrime crime = ScriptCrime();
	ScriptLogger logger = ScriptLogger();

	logger.log("Starting jtmcraft's RDR2 mod.");

	while (true) {
		crime.tick();
		WAIT(0);
	}
}

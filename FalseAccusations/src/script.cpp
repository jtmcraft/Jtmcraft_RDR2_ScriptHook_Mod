#pragma once

#include <string>
#include <api/ScriptLogger.h>
#include <inc/main.h>
#include "ScriptCrime.h"
#include "ScriptVigilantes.h"
#include <random>

using namespace std;

void ScriptMain() {
	random_device rd;
	mt19937 g(rd());

	ScriptCrime crime = ScriptCrime();
	ScriptLogger logger = ScriptLogger();
	ScriptVigilantes vigilantes = ScriptVigilantes();
	vigilantes.setLogger(logger);
	vigilantes.setRng(g);

	logger.log("Starting jtmcraft's RDR2 mod.");

	while (true) {
		crime.tick();
		vigilantes.tick();

		WAIT(0);
	}
}

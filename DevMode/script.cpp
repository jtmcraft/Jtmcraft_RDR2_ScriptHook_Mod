#include "DevMode.h"

void ScriptMain() {
	DevMode devMode = DevMode();
	ScriptLogger logger = ScriptLogger();
	devMode.setLogger(logger);

	while (true) {
		devMode.tick();
		WAIT(0);
	}
}

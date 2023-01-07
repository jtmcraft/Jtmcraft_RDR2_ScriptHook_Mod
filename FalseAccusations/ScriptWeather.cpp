#include "ScriptWeather.h"

ScriptWeather::ScriptWeather() {
	api = Api();
	winterBlanket = false;
}

void ScriptWeather::addSnowBlanket(int coverage) {
	api.setWeather("SNOWLIGHT");
	api.setSnowLevel(1);
	api.setSnowCoverage(coverage);
}

void ScriptWeather::removeSnowBlanket(char* replacementWeather) {
	api.setWeather(replacementWeather);
	api.setSnowLevel(-1);
	api.setSnowCoverage(0);
}

void ScriptWeather::toggleWinterBlanket() {
	if (winterBlanket) {
		removeSnowBlanket("SUNNY");
	}
	else {
		addSnowBlanket(2);
	}

	winterBlanket = !winterBlanket;
}

void ScriptWeather::tick() {
	if (IsKeyJustUp(VK_KEY_K)) {
		toggleWinterBlanket();
	}

	if (winterBlanket) {
		api.setWeather("SNOWLIGHT");
	}
}

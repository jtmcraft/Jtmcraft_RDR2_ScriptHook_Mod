#include "SnowBlanket.h"

SnowBlanket::SnowBlanket() {
	api = Api();
	winterBlanket = false;
}

void SnowBlanket::addSnowBlanket(int coverage) {
	api.setWeather("SNOWLIGHT");
	api.setSnowLevel(1);
	api.setSnowCoverage(coverage);
}

void SnowBlanket::removeSnowBlanket(char* replacementWeather) {
	api.setWeather(replacementWeather);
	api.setSnowLevel(-1);
	api.setSnowCoverage(0);
}

void SnowBlanket::toggleWinterBlanket() {
	if (winterBlanket) {
		removeSnowBlanket("SUNNY");
	}
	else {
		addSnowBlanket(2);
	}

	winterBlanket = !winterBlanket;
}

void SnowBlanket::tick() {
	if (IsKeyJustUp(VK_KEY_K)) {
		toggleWinterBlanket();
	}

	if (winterBlanket) {
		api.setWeather(_strdup("SNOWLIGHT"));
	}
}

#include "VampireWeather.h"

using namespace std;

VampireWeather::VampireWeather() {
	api = Api();
	foggy = false;
	vampireWeather = api.getHash(VAMPIRE_WEATHER);
	afterVampireWeather = api.getHash(SUNNY_WEATHER);
}

bool VampireWeather::isFoggy() {
	return foggy;
}

void VampireWeather::fogIn() {
	Hash w1, w2;
	float p;

	api.getWeatherTransition(&w1, &w2, &p);
	p = 1.0f - p;
	while (p < 1.0f) {
		WAIT(WEATHER_TRANSITION_DELAY);
		p += WEATHER_TRANSITION_STEP;
		api.setWeatherTransition(w2, vampireWeather, p);
	}

	api.setWeather(VAMPIRE_WEATHER);
	api.freezeWeather(true);
	foggy = true;
}

void VampireWeather::fogOut() {
	float p;

	p = 0.0f;
	while (p < 1.0f) {
		WAIT(WEATHER_TRANSITION_DELAY);
		p += WEATHER_TRANSITION_STEP;
		api.setWeatherTransition(vampireWeather, afterVampireWeather, p);
	}

	api.freezeWeather(false);
	api.setWeather(SUNNY_WEATHER);
	foggy = false;
}

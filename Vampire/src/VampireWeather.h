#pragma once

#include <chrono>
#include <api/Api.h>

using namespace std;

constexpr char* VAMPIRE_WEATHER = "FOG";
constexpr char* SUNNY_WEATHER = "SUNNY";
constexpr int WEATHER_TRANSITION_DELAY = 50;
constexpr float WEATHER_TRANSITION_STEP = 0.01f;

class VampireWeather
{
private:
	Api api;
	bool foggy;
	chrono::steady_clock::time_point startTime;
	Hash vampireWeather;
	Hash afterVampireWeather;

public:
	VampireWeather();
	void fogIn();
	void fogOut();
	void tick();
	bool isFoggy();
};

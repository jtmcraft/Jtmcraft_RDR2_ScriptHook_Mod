#pragma once

#include <chrono>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
#include "ScriptDataModel.h"
#include <inc/types.h>
#include <api/Api.h>

using namespace std;

const Hash CRIMES[] = {
	0x68134DC7,
	0x0BADC882,
	0x971EA5AF,
	0x55AD2BEB,
	0xE28ECE7E,
	0xA3BEDE4C,
	0xFC738E61,
	0x647D2A5A
};

class ScriptCrime
{
private:
	Api api;
	unordered_map<Hash, char*> crimes;
	fstream dataFile;
	const char* fileName;
	double timeToWait;
	double timeElapsed;
	int chance;
	chrono::steady_clock::time_point startAutoSave;
	chrono::steady_clock::time_point startFalseAccusation;
	void handleFalseAccusation(double elapsedFalseAccusation, bool shouldSave);
	bool tryToFalselyAccusePlayer();

public:
	ScriptCrime();
	Hash randomCrime();
	char* getCrime(Hash crime);
	void setDefaults();
	double getTimeToWait();
	double getTimeElapsed();
	int getChance();
	void setTimeToWait(double timeToWait);
	void setTimeElapsed(double timeElapsed);
	void addTimeElapsed(double delta);
	void setChance(int chance);
	void increaseChance();
	void read();
	void write();
	void tick();
};

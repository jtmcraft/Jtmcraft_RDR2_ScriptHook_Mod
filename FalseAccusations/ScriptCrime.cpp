#include "ScriptCrime.h"

using namespace std;

ScriptCrime::ScriptCrime() {
	api = Api();

	crimes[0x68134DC7] = "Arson";
	crimes[0x0BADC882] = "Assault";
	crimes[0x971EA5AF] = "Grave Robbery";
	crimes[0x55AD2BEB] = "Looting";
	crimes[0xE28ECE7E] = "Murder";
	crimes[0xA3BEDE4C] = "Robbery";
	crimes[0xFC738E61] = "Stagecoach Robbery";
	crimes[0x647D2A5A] = "Train Robbery";

	fileName = "jtm.dat";
	bool isEmpty;

	dataFile.open(fileName, ios_base::in);
	isEmpty = (dataFile.peek() == fstream::traits_type::eof());
	dataFile.close();

	if (isEmpty) {
		setDefaults();
		write();
	}
	else {
		read();
	}

	startAutoSave = chrono::steady_clock::now();
	startFalseAccusation = chrono::steady_clock::now();
}

Hash ScriptCrime::randomCrime() {
	int dim = (sizeof(CRIMES) / sizeof(CRIMES[0]));

	return CRIMES[api.randInt(0, dim - 1)];
}

char* ScriptCrime::getCrime(Hash crime) {
	return crimes[crime];
}

void ScriptCrime::setDefaults() {
	timeToWait = 3480;
	timeElapsed = 0;
	chance = 10;
}

double ScriptCrime::getTimeToWait()
{
	return timeToWait;
}

double ScriptCrime::getTimeElapsed() {
	return timeElapsed;
}

int ScriptCrime::getChance()
{
	return chance;
}

void ScriptCrime::setTimeToWait(double timeToWait)
{
	this->timeToWait = timeToWait;
}

void ScriptCrime::setTimeElapsed(double timeElapsed) {
	this->timeElapsed = timeElapsed;
}

void ScriptCrime::addTimeElapsed(double delta) {
	timeElapsed += delta;
}

void ScriptCrime::setChance(int chance)
{
	this->chance = chance;
}

void ScriptCrime::increaseChance() {
	timeToWait /= 2;
	chance += 5;
	timeElapsed = 0;
}

void ScriptCrime::write() {
	dataFile.open(fileName, ios_base::out);
	dataFile << timeToWait << " " << timeElapsed << " " << chance;
	dataFile.close();
}

void ScriptCrime::read() {
	dataFile.open(fileName, ios_base::in);
	dataFile >> timeToWait >> timeElapsed >> chance;
	dataFile.close();
}

bool ScriptCrime::tryToFalselyAccusePlayer() {
	int roll = api.randInt(1, 100);
	char msg[100];

	sprintf_s(msg, "Roll: %d; Chance: %d", roll, chance);
	api.toast(msg);

	if (roll < chance) {
		Hash crime = randomCrime();
		char crimeStr[200];
		sprintf_s(crimeStr, "Someone falsely accused you of %s.", getCrime(crime));
		api.toast(crimeStr);
		WAIT(2000);
		api.reportCrime(crime);

		return true;
	}

	return false;
}

void ScriptCrime::handleFalseAccusation(double elapsedFalseAccusation, bool shouldSave) {
	timeElapsed += elapsedFalseAccusation;

	if (timeElapsed >= timeToWait) {
		bool wasAccused = tryToFalselyAccusePlayer();

		if (wasAccused) {
			setDefaults();
		}
		else {
			increaseChance();
		}

		shouldSave = true;
	}

	if (shouldSave) {
		write();
	}
}

void ScriptCrime::tick() {
	// printInfo();

	bool shouldSave = false;
	auto now = chrono::steady_clock::now();
	chrono::duration<double> elapsedAutoSave = now - startAutoSave;
	chrono::duration<double> elapsedFalseAccusation = now - startFalseAccusation;

	if (elapsedFalseAccusation.count() >= 1) {
		if (elapsedAutoSave.count() >= 15) {
			shouldSave = true;
			startAutoSave = now;
		}

		handleFalseAccusation(elapsedFalseAccusation.count(), shouldSave);
		startFalseAccusation = now;
	}
}

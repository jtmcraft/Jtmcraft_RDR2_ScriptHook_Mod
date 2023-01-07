#include "ScriptCrimeController.h"

using namespace std;

ScriptCrimeController::ScriptCrimeController() {
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

Hash ScriptCrimeController::randomCrime() {
	int dim = (sizeof(CRIMES) / sizeof(CRIMES[0]));

	return CRIMES[api.randInt(0, dim - 1)];
}

char* ScriptCrimeController::getCrime(Hash crime) {
	return crimes[crime];
}

void ScriptCrimeController::setDefaults() {
	timeToWait = 3480;
	timeElapsed = 0;
	chance = 10;
}

double ScriptCrimeController::getTimeToWait()
{
	return timeToWait;
}

double ScriptCrimeController::getTimeElapsed() {
	return timeElapsed;
}

int ScriptCrimeController::getChance()
{
	return chance;
}

void ScriptCrimeController::setTimeToWait(double timeToWait)
{
	this->timeToWait = timeToWait;
}

void ScriptCrimeController::setTimeElapsed(double timeElapsed) {
	this->timeElapsed = timeElapsed;
}

void ScriptCrimeController::addTimeElapsed(double delta) {
	timeElapsed += delta;
}

void ScriptCrimeController::setChance(int chance)
{
	this->chance = chance;
}

void ScriptCrimeController::increaseChance() {
	timeToWait /= 2;
	chance += 5;
	timeElapsed = 0;
}

void ScriptCrimeController::write() {
	dataFile.open(fileName, ios_base::out);
	dataFile << timeToWait << " " << timeElapsed << " " << chance;
	dataFile.close();
}

void ScriptCrimeController::read() {
	dataFile.open(fileName, ios_base::in);
	dataFile >> timeToWait >> timeElapsed >> chance;
	dataFile.close();
}

void ScriptCrimeController::printInfo() {
	stringstream msg;
	Vector3 coords = api.getPlayerCoords();
	float heading = api.getPlayerHeading();

	msg << "X: " << coords.x << endl << "Y: " << coords.y << endl << "Z: " << coords.z << endl << "H: " << heading
		<< endl << "Wait: " << floor(timeToWait) << endl << "Elapsed: " << floor(timeElapsed) << endl << "Chance: " << chance;

	api.drawRectangle(0.04, 0.04, 0.15, 0.2);
	api.drawText(msg.str().c_str(), 0.05, 0.05);
}

bool ScriptCrimeController::tryToFalselyAccusePlayer() {
	int roll = api.randInt(1, 100);
	char msg[100];

	sprintf_s(msg, "Roll: %d; Chance: %d", roll, chance);
	api.toast(msg);

	if (roll < chance) {
		Hash crime = randomCrime();
		char toastStr[100];
		sprintf_s(toastStr, "Someone falsely accused you of %s.", getCrime(crime));
		api.toast(toastStr);
		WAIT(2000);
		api.reportCrime(crime);

		return true;
	}

	return false;
}

void ScriptCrimeController::handleFalseAccusation(double elapsedFalseAccusation, bool shouldSave) {
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

void ScriptCrimeController::tick() {
	printInfo();

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

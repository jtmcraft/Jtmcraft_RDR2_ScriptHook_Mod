#include "ScriptController.h"

using namespace std;

ScriptController::ScriptController() {
	api = Api();
	logger = ScriptLogger();
	dataManager = ScriptDataManager();
	crimeManager = ScriptCrimeManager();
	crimeManager.setDataModel(dataManager.read());
	vampire = NULL;
	okToSpawnVampire = true;
	isWinterBlanket = false;

	logger.log("Starting False Accusations mod.");
}

bool ScriptController::tryToFalselyAccusePlayer() {
	ScriptDataModel dataModel = crimeManager.getDataModel();
	int roll = rand() % 100;
	int chance = dataModel.getChance();
	char msg[100];

	sprintf_s(msg, "Roll: %d; Chance: %d", roll, chance);
	logger.log(msg);

	if (roll < chance) {
		api.toast("Someone falsely accused you of a crime.");
		WAIT(2000);
		api.reportCrime(crimeManager.randomCrime());

		return true;
	}

	return false;
}

void ScriptController::drawUserInterface() {
	stringstream msg;
	Vector3 coords = api.getPlayerCoords();
	float heading = api.getPlayerHeading();
	ScriptDataModel dataModel = crimeManager.getDataModel();
	double timeToWait = dataModel.getTimeToWait();
	double elapsedTime = dataModel.getTimeElapsed();
	int chance = dataModel.getChance();

	msg << "X: " << coords.x << endl << "Y: " << coords.y << endl << "Z: " << coords.z << endl << "H: " << heading
		<< endl << "Wait: " << timeToWait << endl << "Elapsed: " << elapsedTime << endl << "Chance: " << chance;

	api.drawRectangle(0.04, 0.04, 0.15, 0.2);
	api.drawText(msg.str().c_str(), 0.05, 0.05);
}

void ScriptController::saveCoordinates() {
	if (IsKeyJustUp(VK_KEY_I)) {
		stringstream msg;
		Vector3 coords = api.getPlayerCoords();
		float heading = api.getPlayerHeading();

		msg << "X: " << coords.x << "," << "Y: " << coords.y << ", " << "Z: " << coords.z << ", H: " << heading;
		logger.log(msg.str().c_str());
		api.toast("Saved coords.");
	}
}

void ScriptController::changeWeather() {
	if (IsKeyJustUp(VK_KEY_K)) {
		toggleWinterBlanket();
	}
}

void ScriptController::toggleDevMode() {
	if (IsKeyJustUp(VK_KEY_O)) {
		api.togglePlayerInvincible();
		if (api.isPlayerInvincible()) {
			api.toast("You are now invincible.");
		}
		else {
			api.toast("You are no longer invincible.");
		}
	}
}

void ScriptController::giveMoney() {
	if (IsKeyJustUp(VK_KEY_U)) {
		api.giveMoney();
		api.toast("Added $50");
	}
}

void ScriptController::log(const char* text) {
	logger.log(text);
}

void ScriptController::handleFalseAccusation(double elapsedFalseAccusation, bool shouldSave) {
	ScriptDataModel dataModel = crimeManager.getDataModel();
	double timeToWait = dataModel.getTimeToWait();
	double timeElapsed = dataModel.getTimeElapsed() + elapsedFalseAccusation;
	
	dataModel.addTimeElapsed(elapsedFalseAccusation);

	if (timeElapsed >= timeToWait) {
		bool wasAccused = tryToFalselyAccusePlayer();

		if (wasAccused) {
			dataModel.setDefaults();
		}
		else {
			dataModel.increaseChance();
		}

		shouldSave = true;
	}

	crimeManager.setDataModel(dataModel);

	if (shouldSave) {	
		dataManager.write(crimeManager.getDataModel());
	}
}

void ScriptController::toggleWinterBlanket() {
	if (isWinterBlanket) {
		api.setWeather(SUNNY_WEATHER);
		api.setSnowLevel(-1);
		api.setSnowCoverage(0);
	}
	else {
		api.setWeather(SNOWY_WEATHER);
		api.setSnowLevel(1);
		api.setSnowCoverage(2);
	}

	isWinterBlanket = !isWinterBlanket;
}

bool ScriptController::isPaused() {
	return api.isPaused();
}

bool ScriptController::isVampireOutOfRange() {
	return api.distanceBetween(api.getEntityCoords(vampire), api.getPlayerCoords()) > 140;
}

void ScriptController::spawnVampire() {
	vampire = api.spawnHostilePedNearPlayer("CS_Vampire");
	okToSpawnVampire = false;
}

void ScriptController::updateVampire() {
	bool isAlive = vampire != NULL && !api.isEntityDead(vampire);
	int gameHour = api.getGameHour();

	if (gameHour > 6) {
		if (isAlive) {
			api.setEntityHealth(vampire, 0);
			api.addExplosion(api.getEntityCoords(vampire));
		}

		vampire = NULL;
		okToSpawnVampire = true;
		
		return;
	}

	if (isAlive && isVampireOutOfRange()) {
		api.deletePed(vampire);
		spawnVampire();

		return;
	}

	if (okToSpawnVampire && gameHour == 0) {
		spawnVampire();
	}
}

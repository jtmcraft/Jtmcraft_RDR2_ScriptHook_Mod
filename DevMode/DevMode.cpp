#include "DevMode.h"

using namespace std;

DevMode::DevMode() {
	api = Api();
}

void DevMode::setLogger(ScriptLogger logger) {
	this->logger = logger;
}

void DevMode::savePlayerCoords() {
	Vector3 coords = api.getPlayerCoords();
	float heading = api.getPlayerHeading();

	stringstream msg;
	msg << "X: " << coords.x << "," << "Y: " << coords.y << ", " << "Z: " << coords.z << ", H: " << heading;
	logger.log(msg.str().c_str());
	api.toast("Saved coords.");
}

void DevMode::giveMoney() {
	api.giveMoney();
	api.toast("Added $50");
}

void DevMode::toggleInvinciblePlayer() {
	api.togglePlayerInvincible();
	if (api.isPlayerInvincible()) {
		api.toast("You are now invincible.");
	}
	else {
		api.toast("You are no longer invincible.");
	}
}

void DevMode::tick() {
	if (IsKeyJustUp(VK_KEY_I)) {
		savePlayerCoords();
	}

	if (IsKeyJustUp(VK_KEY_O)) {
		toggleInvinciblePlayer();
	}

	if (IsKeyJustUp(VK_KEY_U)) {
		giveMoney();
	}
}

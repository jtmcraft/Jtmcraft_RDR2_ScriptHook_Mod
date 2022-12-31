#include "Api.h"

Vector3 Api::getPlayerCoords() {
	return ENTITY::GET_ENTITY_COORDS(getPlayerPed(), true, 0);
}

Player Api::getPlayer() {
	return PLAYER::PLAYER_ID();
}

Ped Api::getPlayerPed() {
	return PLAYER::PLAYER_PED_ID();
}

float Api::getPlayerHeading() {
	return ENTITY::GET_ENTITY_HEADING(getPlayerPed());
}

int Api::getMaxWantedLevel() {
	return PLAYER::GET_MAX_WANTED_LEVEL();
}

int Api::getPlayerWantedLevel() {
	return PLAYER::GET_PLAYER_WANTED_LEVEL(getPlayer());
}

void Api::setPlayerWantedLevel(int wantedLevel) {
	PLAYER::SET_PLAYER_WANTED_LEVEL(getPlayer(), wantedLevel, false);
}

void Api::incrementPlayerWantedLevel() {
	Player player = getPlayer();
	Ped playerPed = getPlayerPed();
	int maxWantedLevel = getMaxWantedLevel();
	int nextWantedLevel = 1 + getPlayerWantedLevel();

	if (nextWantedLevel > maxWantedLevel) {
		nextWantedLevel = maxWantedLevel;
	}

	setPlayerWantedLevel(nextWantedLevel);
}

char* Api::createString(const char* text) {
	return GAMEPLAY::CREATE_STRING(10, "LITERAL_STRING", _strdup(text));
}

void Api::debugText(const char* text) {
	UI::SET_TEXT_COLOR_RGBA(255, 128, 0, 0);
	UI::SET_TEXT_SCALE(0.33, 0.33);
	UI::DRAW_TEXT(createString(text), 0, 0);
}

void Api::displaySubTitle(const char* text) {
	UILOG::_0xFA233F8FE190514C((Any*) createString(text));
	UILOG::_0xE9990552DEC71600();
	UILOG::_0xDFF0D417277B41F8();
}

void Api::playNotification() {
	AUDIO::_0xCE5D0FFE83939AF1(-1, (Any*) "WEAPON_PURCHASE", (Any*) "HUD_AMMO_SHOP_SOUNDSET", true);
}

void Api::playInformational() {
	AUDIO::_0xCE5D0FFE83939AF1(-1, (Any*) "BACK", (Any*) "HUD_FRONTEND_DEFAULT_SOUNDSET", 0);
}

void Api::toast(const char* text) {
	displaySubTitle(text);
}

void Api::drawText(const char* text, float x, float y) {
	UI::SET_TEXT_COLOR_RGBA(255, 128, 0, 255);
	UI::SET_TEXT_SCALE(0.33, 0.33);
	UI::DRAW_TEXT(createString(text), x, y);
}

void Api::drawRectangle(float x, float y, float width, float height) {
	float fX = x + width / 2;
	float fY = y + height / 2;

	GRAPHICS::DRAW_RECT(fX, fY, width, height, 0, 0, 0, 190, true, 0);
}

void Api::reportCrime(Hash crime) {
	PURSUIT::_0xF60386770878A98F(getPlayer(), crime, 0, 0, true);
}

void Api::requestModel(Hash modelHash, bool b) {
	STREAMING::REQUEST_MODEL(modelHash, false);
	while (!STREAMING::HAS_MODEL_LOADED(modelHash)) {
		WAIT(0);
	}
}

Vector3 Api::getOffsetFromPlayerInWorldCoords(float offsetX, float offsetY, float offsetZ) {
	return ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(getPlayerPed(), offsetX, offsetY, offsetZ);
}

void Api::giveMoney() {
	CASH::PLAYER_ADD_CASH(5000, 1);
}

bool Api::isPlayerInvincible() {
	return PLAYER::GET_PLAYER_INVINCIBLE(getPlayer());
}

void Api::togglePlayerInvincible() {
	bool isInvincible = isPlayerInvincible();

	PLAYER::SET_PLAYER_INVINCIBLE(getPlayer(), !isInvincible);
	if (isPlayerOnMount()) {
		ENTITY::SET_ENTITY_INVINCIBLE(getPlayerMount(), !isInvincible);
	}
}

bool Api::isPlayerOnMount() {
	return PED::IS_PED_ON_MOUNT(getPlayerPed());
}

Ped Api::getPlayerMount() {
	return PED::GET_MOUNT(getPlayerPed());
}

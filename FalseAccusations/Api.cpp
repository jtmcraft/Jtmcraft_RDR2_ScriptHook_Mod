#include "Api.h"

Vector3 Api::getPlayerCoords() {
	return getEntityCoords(getPlayerPed());
}

Vector3 Api::getEntityCoords(Entity entity) {
	return ENTITY::GET_ENTITY_COORDS(entity, true, 0);
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

int Api::randInt(int a, int b) {
	return GAMEPLAY::GET_RANDOM_INT_IN_RANGE(a, b);
}

float Api::randFloat(float a, float b) {
	return GAMEPLAY::GET_RANDOM_FLOAT_IN_RANGE(a, b);
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
	float fY = (y + height / 2);

	GRAPHICS::DRAW_RECT(fX, fY, width, height, 0, 0, 0, 190, true, 0);
}

void Api::reportCrime(Hash crime) {
	PURSUIT::_0xF60386770878A98F(getPlayer(), crime, 0, 0, true);
}

void Api::loadModel(Hash modelHash, bool b) {
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

void Api::setSnowLevel(float level) {
	GAMEPLAY::_0xF6BEE7E80EC5CA40(level);
}

void Api::setSnowCoverage(int coverage) {
	if (coverage < 0) {
		coverage = 0;
	}

	if (coverage > 2) {
		coverage = 2;
	}

	GRAPHICS::_0xF02A9C330BBFC5C7(coverage);
}

void Api::setWeather(const char* weatherType) {
	GAMEPLAY::CLEAR_OVERRIDE_WEATHER();
	GAMEPLAY::SET_WEATHER_TYPE(GAMEPLAY::GET_HASH_KEY(_strdup(weatherType)), 0, 1, 0, 0.0, 0);
	GAMEPLAY::CLEAR_WEATHER_TYPE_PERSIST();
}

Hash Api::getHash(char* key) {
	return GAMEPLAY::GET_HASH_KEY(key);
}

Vector3 Api::findLocationRelativeToPlayer(float distance, float a, float b) {
	Vector3 playerLocation = getPlayerCoords();
	float playerHeading = getPlayerHeading();
	Vector3 nearLocation = OBJECT::_GET_OBJECT_OFFSET_FROM_COORDS(
		playerLocation.x, playerLocation.y, playerLocation.z,
		playerHeading,
		distance + randFloat(a, b), distance + randFloat(a, b), 0
	);

	PATHFIND::GET_SAFE_COORD_FOR_PED(nearLocation.x, nearLocation.y, nearLocation.z, true, &nearLocation, 16);

	return nearLocation;
}

Ped Api::createPed(Hash model, Vector3 spawnLocation, bool onGround) {
	float x, y, z;

	x = spawnLocation.x;
	y = spawnLocation.y;
	z = onGround ? groundAt(spawnLocation) : spawnLocation.z;

	Ped created = PED::CREATE_PED(model, x, y, z, 0.0, 1, 0, 0, 0);

	return created;
}

Blip Api::addBlip(Hash blipHash, Ped ped) {
	return RADAR::_0x23F74C2FDA6E7C61(blipHash, ped);
}

void Api::addPedToWorld(Ped ped, char* relationship, bool isHostileToPlayer, Vector3 turnToCoords, char* blipStyle) {
	PED::SET_PED_VISIBLE(ped, true);
	AI::TASK_TURN_PED_TO_FACE_COORD(ped, turnToCoords.x, turnToCoords.y, turnToCoords.z, 0);
	PED::SET_PED_RELATIONSHIP_GROUP_HASH(ped, getHash(relationship));
	addBlip(getHash(blipStyle), ped);

	if (isHostileToPlayer) {
		AI::TASK_COMBAT_PED(ped, getPlayerPed(), 0, 16);
	}
}

float Api::groundAt(Vector3 location) {
	float z;

	GAMEPLAY::GET_GROUND_Z_FOR_3D_COORD(location.x, location.y, 500, &z, false);

	return z;
}

Ped Api::spawnRelativeToPlayer(char* model, float distance, float a, float b) {
	Vector3 playerLocation = getPlayerCoords();
	Vector3 spawnLocation = findLocationRelativeToPlayer(distance, a, b);
	Hash skin = getHash(model);

	loadModel(skin, true);
	Ped spawned = createPed(skin, spawnLocation, true);

	addPedToWorld(spawned, "REL_CRIMINALS", true, playerLocation, "BLIP_STYLE_ENEMY");
	STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(skin);

	return spawned;
}

int Api::createGroup() {
	return PED::CREATE_GROUP(0);
}

void Api::setPedGroupLeader(Ped ped, int groupId) {
	PED::SET_PED_AS_GROUP_LEADER(ped, groupId, 0);
}

void Api::setPedGroupMember(Ped ped, int groupId) {
	PED::GET_PED_AS_GROUP_MEMBER(ped, groupId);
}

void Api::givePedWeapon(Ped ped, Hash weaponHash, int ammo) {
	WEAPON::GIVE_DELAYED_WEAPON_TO_PED(ped, weaponHash, ammo, true, 0);
	WEAPON::SET_CURRENT_PED_WEAPON(ped, weaponHash, true, 0, false, false);
}

bool Api::isPaused() {
	return UI::IS_PAUSE_MENU_ACTIVE();
}

int Api::getGameHour() {
	return TIME::GET_CLOCK_HOURS();
}

int Api::getGameMinute() {
	return TIME::GET_CLOCK_MINUTES();
}

int Api::getGameSecond() {
	return TIME::GET_CLOCK_SECONDS();
}

void Api::setGameTime(int hours, int minutes, int seconds) {
	TIME::SET_CLOCK_TIME(hours, minutes, seconds);
}

void Api::addExplosion(Vector3 coords) {
	FIRE::ADD_EXPLOSION(coords.x, coords.y, coords.z, 27, 1.0f, true, false, 1.0f);
}

void Api::setEntityHealth(Entity entity, int health) {
	ENTITY::SET_ENTITY_HEALTH(entity, health, 0);
}

float Api::distanceBetween(Vector3 a, Vector3 b) {
	return GAMEPLAY::GET_DISTANCE_BETWEEN_COORDS(a.x, a.y, a.z, b.x, b.y, b.z, false);
}

void Api::deletePed(Ped ped) {
	PED::DELETE_PED(&ped);
}

bool Api::isEntityDead(Entity entity) {
	return ENTITY::IS_ENTITY_DEAD(entity);
}

bool Api::isPedDeadOrDying(Ped ped) {
	return PED::IS_PED_DEAD_OR_DYING(ped, true);
}

void Api::addSnowBlanket(int coverage) {
	setWeather("SNOW");
	setSnowLevel(1);
	setSnowCoverage(coverage);
}

void Api::removeSnowBlanket(char* replacementWeather) {
	setWeather(replacementWeather);
	setSnowLevel(-1);
	setSnowCoverage(0);
}

bool Api::detectHeadShot(Ped victim) {
	int bone;

	PED::GET_PED_LAST_DAMAGE_BONE(victim, &bone);

	return bone == 21030;
}

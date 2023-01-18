#include "Api.h"

using namespace std;

Api::Api() {
	initAngles();
}

void Api::initAngles() {
	float pi = (2 * acosf(0.0));

	angles[0] = 0;
	angles[1] = pi / 6;
	angles[2] = pi / 4;
	angles[3] = pi / 3;
	angles[4] = pi / 2;
	angles[5] = 2 * pi / 3;
	angles[6] = 3 * pi / 4;
	angles[7] = 5 * pi / 6;
	angles[8] = pi;
	angles[9] = 7 * pi / 6;
	angles[10] = 5 * pi / 4;
	angles[11] = 4 * pi / 3;
	angles[12] = 3 * pi / 2;
	angles[13] = 5 * pi / 3;
	angles[14] = 7 * pi / 4;
	angles[15] = 11 * pi / 6;
}

void Api::initPostOffices() {
	postOffices["Annesburg"] = { 2931.73, 1283.24, 44.6528 };
}

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

char* Api::createString(char* text) {
	return GAMEPLAY::CREATE_STRING(10, "LITERAL_STRING", text);
}

int Api::randInt(int a, int b) {
	return GAMEPLAY::GET_RANDOM_INT_IN_RANGE(a, b);
}

float Api::randFloat(float a, float b) {
	return GAMEPLAY::GET_RANDOM_FLOAT_IN_RANGE(a, b);
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

void Api::loadTexture(char* dict) {
	TEXTURE::REQUEST_STREAMED_TEXTURE_DICT(dict, false);
	while (!TEXTURE::HAS_STREAMED_TEXTURE_DICT_LOADED(dict)) {
		WAIT(0);
	}
}

Vector3 Api::getOffsetFromPlayerInWorldCoords(float offsetX, float offsetY, float offsetZ) {
	return ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(getPlayerPed(), offsetX, offsetY, offsetZ);
}

void Api::giveMoney() {
	CASH::PLAYER_ADD_CASH(5000, 1);
}

void Api::addMoney(int pennies) {
	CASH::PLAYER_ADD_CASH(pennies, 1);
}

Ped Api::getMountOwnedByPlayer() {
	return PLAYER::_0xF49F14462F0AE27C(getPlayer());
}

void Api::setPlayerInvincible(bool isInvincible) {
	PLAYER::SET_PLAYER_INVINCIBLE(getPlayer(), isInvincible);
	ENTITY::SET_ENTITY_INVINCIBLE(getMountOwnedByPlayer(), isInvincible);
	if (isPlayerOnMount()) {
		ENTITY::SET_ENTITY_INVINCIBLE(getPlayerMount(), isInvincible);
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

Hash Api::getNextWeather() {
	return GAMEPLAY::_0x51021D36F62AAA83();
}

void Api::getWeatherTransition(Hash* weatherType1, Hash* weatherType2, float* percentWeather2) {
	GAMEPLAY::_GET_WEATHER_TYPE_TRANSITION(weatherType1, weatherType2, percentWeather2);
}

void Api::setWeatherTransition(Hash weatherType1, Hash weatherType2, float percentWeather2) {
	GAMEPLAY::_SET_WEATHER_TYPE_TRANSITION(weatherType1, weatherType2, percentWeather2, true);
}

void Api::freezeWeather(bool frozen) {
	GAMEPLAY::FREEZE_WEATHER(frozen);
}

void Api::setWeather(char* weatherType) {
	GAMEPLAY::CLEAR_OVERRIDE_WEATHER();
	GAMEPLAY::SET_WEATHER_TYPE(GAMEPLAY::GET_HASH_KEY(weatherType), 0, 1, 0, 0.0, 0);
	GAMEPLAY::CLEAR_WEATHER_TYPE_PERSIST();
}

Hash Api::getHash(char* key) {
	return GAMEPLAY::GET_HASH_KEY(key);
}

array<Vector3, 16> Api::findLocationsAroundPlayer(float distance, float a, float b) {
	Vector3 playerLocation = getPlayerCoords();
	float playerHeading = getPlayerHeading();
	array<Vector3, 16> locations = { 0 };

	for (int i = 0; i < 16; i++) {
		Vector3 location = {
			(distance + randFloat(a, b)) * cosf(angles[i]),
			(distance + randFloat(a, b)) * sinf(angles[i]),
			0
		};

		locations[i] = OBJECT::_GET_OBJECT_OFFSET_FROM_COORDS(playerLocation.x, playerLocation.y, playerLocation.z, playerHeading, location.x, location.y, location.z);
		PATHFIND::GET_SAFE_COORD_FOR_PED(locations[i].x, locations[i].y, locations[i].z, true, &locations[i], 16);
	}

	return locations;
}

Vector3 Api::findLocationInFrontOfPlayer(float distance, float a, float b) {
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

bool Api::hasBlip(Entity entity) {
	return RADAR::_0x9FA00E2FC134A9D0(entity);
}

void Api::enemyBlip(Ped ped) {
	addBlip(getHash("BLIP_STYLE_ENEMY"), ped);
}

Blip Api::addBlip(Hash blipHash, Ped ped) {
	return RADAR::_0x23F74C2FDA6E7C61(blipHash, ped);
}

void Api::addPedToWorld(Ped ped, char* relationship, bool isHostileToPlayer, Vector3 turnToCoords) {
	PED::SET_PED_VISIBLE(ped, true);
	AI::TASK_TURN_PED_TO_FACE_COORD(ped, turnToCoords.x, turnToCoords.y, turnToCoords.z, 0);
	PED::SET_PED_RELATIONSHIP_GROUP_HASH(ped, getHash(relationship));

	if (isHostileToPlayer) {
		taskAttackPlayer(ped);
	}
}

void Api::taskAttackPlayer(Ped ped) {
	AI::TASK_COMBAT_PED(ped, getPlayerPed(), 0, 16);
}

void Api::taskWanderInArea(Ped ped, float x, float y, float z, float radius, float minimalLength, float timeBetween) {
	AI::TASK_WANDER_IN_AREA(ped, x, y, z, radius, minimalLength, timeBetween, false);
}

void Api::taskWanderInArea(Ped ped, float x, float y, float z) {
	taskWanderInArea(ped, x, y, z, 200, 10, 10);
}

float Api::groundAt(Vector3 location) {
	float z;

	GAMEPLAY::GET_GROUND_Z_FOR_3D_COORD(location.x, location.y, 500, &z, false);

	return z;
}

Ped Api::spawnPedAt(char* model, Vector3 spawnCoords, Vector3 turnToCoords, bool withBlip, bool hostileToPlayer) {
	Hash skin = getHash(model);

	loadModel(skin, true);
	Ped spawned = createPed(skin, spawnCoords, true);
	addPedToWorld(spawned, "REL_CRIMINALS", hostileToPlayer, turnToCoords);
	STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(skin);

	if (withBlip) {
		enemyBlip(spawned);
	}

	return spawned;
}

Ped Api::spawnRelativeToPlayer(char* model, float distance, float a, float b, bool withBlip, bool hostileToPlayer) {
	return spawnPedAt(model, findLocationInFrontOfPlayer(distance, a, b), getPlayerCoords(), withBlip, hostileToPlayer);
}

void Api::addMoneyLoot(Ped ped, int pennies) {
	DECORATOR::DECOR_SET_INT(ped, "loot_money", pennies);
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

Hash Api::repeaterCarbine() {
	return getHash("weapon_repeater_carbine");
}

Hash Api::cattlemanRevolver() {
	return getHash("weapon_revolver_cattleman");
}

Hash Api::vampireKnife() {
	return getHash("weapon_melee_knife_vampire");
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

struct {
	alignas(8) int duration;
	alignas(8) int idk0;
	alignas(8) int idk1;
	alignas(8) int idk2;
} notificationTopLeftParam0;

struct {
	alignas(8) int idk0;
	alignas(8) const char* text;
} notificationTopLeftParam1;

void Api::notificationTopLeft(char* text, int duration) {
	notificationTopLeftParam0.duration = duration;
	notificationTopLeftParam0.idk0 = 0;
	notificationTopLeftParam0.idk1 = 0;
	notificationTopLeftParam0.idk2 = 0;

	notificationTopLeftParam1.idk0 = 0;
	notificationTopLeftParam1.text = createString(text);

	UIUNK::_0x049D5C615BD38BAD((Any*)&notificationTopLeftParam0, (Any*)&notificationTopLeftParam1, 1);
}

struct {
	alignas(8) int duration;
	alignas(8) const char* dict;
	alignas(8) const char* sound;
	alignas(8) int idk0;
} notificationRightParam0;

struct {
	alignas(8) int idk0;
	alignas(8) const char* text;
	alignas(8) const char* dict;
	alignas(8) Hash icon;
	alignas(8) int idk1;
	alignas(8) Hash color;
	alignas(8) int idk2;
} notificationRightParam1;

void Api::notificationRight(char* text, char* dict, char* icon, char* color, int duration) {
	notificationRightParam0.duration = duration;
	notificationRightParam0.dict = createString("Transaction_Feed_Sounds");
	notificationRightParam0.sound = createString("Transaction_Positive");
	notificationRightParam0.idk0 = 0;

	notificationRightParam1.idk0 = 0;
	notificationRightParam1.text = createString(text);
	notificationRightParam1.dict = createString(dict);;
	notificationRightParam1.icon = getHash(icon);
	notificationRightParam1.idk1 = 1;
	notificationRightParam1.color = getHash(color);
	notificationRightParam1.idk2 = 0;

	UIUNK::_0xB249EBCB30DD88E0((Any*)&notificationRightParam0, (Any*)&notificationRightParam1, true);
}

void Api::toastRight(char* text, char* dict, char* icon) {
	notificationRight(text, dict, icon, "COLOR_PURE_WHITE", 1000);
}

void Api::notifyHeadShot() {
	toastRight("Head shot", "toast_awards_set_h", "awards_set_h_006");
}

void Api::toast(char* text) {
	invoke<Void>(0xFA233F8FE190514C, createString(text));
	UILOG::_0xE9990552DEC71600();
	UILOG::_0xDFF0D417277B41F8();
}

struct {
	alignas(8) int duration;
	alignas(8) int unk0 = 0;
	alignas(8) int unk1 = 0;
	alignas(8) int unk2 = 0;
} notificationTitledParam0;

struct {
	alignas(8) int unk = 0;
	alignas(8) const char* title;
	alignas(8) const char* subtitle;
	alignas(8) int unk2 = 0;
	alignas(8) Hash iconDict;
	alignas(8) Hash icon;
	alignas(8) Hash color;
	alignas(8) int unk3 = 0;
} notificationTitledParam1;

void Api::notificationTitled(char* title, char* subTitle, char* dict, char* icon, char* color, int duration) {
	loadTexture(dict);

	notificationTitledParam0.duration = duration;

	notificationTitledParam1.icon = getHash(icon);
	notificationTitledParam1.iconDict = getHash(dict);
	notificationTitledParam1.title = createString(title);
	notificationTitledParam1.subtitle = createString(subTitle);
	notificationTitledParam1.color = getHash(color);

	UIUNK::_0x26E87218390E6729((Any*)&notificationTitledParam0, (Any*)&notificationTitledParam1, 1, 1);
}

void Api::notificationAlert(char* text) {
	notificationTitled("Information", text, "menu_textures", "menu_icon_alert", "COLOR_PURE_WHITE", 3000);
}

void Api::fadeOut() {
	CAM::DO_SCREEN_FADE_OUT(1000);
	while (!CAM::IS_SCREEN_FADED_OUT()) {
		WAIT(1);
	}
}

void Api::fadeIn() {
	if (CAM::IS_SCREEN_FADED_OUT()) {
		CAM::DO_SCREEN_FADE_IN(1000);
		while (!CAM::IS_SCREEN_FADED_IN()) {
			WAIT(1);
		}
	}
}

void Api::removeAllPickups(Hash pickup) {
	OBJECT::REMOVE_ALL_PICKUPS_OF_TYPE(pickup);
}

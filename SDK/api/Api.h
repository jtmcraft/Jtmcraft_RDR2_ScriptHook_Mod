#pragma once

#include <cmath>
#include <string>
#include <array>
#include <unordered_map>
#include <keyboard.h>
#include "script.h"

using namespace std;

class Api
{
private:
	array<float, 16> angles;
	unordered_map<char*, Vector3> postOffices;

	void initAngles();
	void initPostOffices();
	Player getPlayer();
	Ped getPlayerPed();
	Vector3 getOffsetFromPlayerInWorldCoords(float offsetX, float offsetY, float offsetZ);
	void setPlayerWantedLevel(int wantedLevel);
	void loadModel(Hash modelHash, bool b);
	void loadTexture(char* dict);
	Ped createPed(Hash skin, Vector3 location, bool onGround);

public:
	Api();
	char* createString(char* text);
	int randInt(int a, int b);
	float randFloat(float a, float b);
	Vector3 getPlayerCoords();
	Vector3 getEntityCoords(Entity entity);
	float getPlayerHeading();
	int getMaxWantedLevel();
	int getPlayerWantedLevel();
	void incrementPlayerWantedLevel();
	void reportCrime(Hash crime);
	void giveMoney();
	void addMoney(int pennies);
	Ped getMountOwnedByPlayer();
	void setPlayerInvincible(bool isInvincible);
	bool isPlayerOnMount();
	Ped getPlayerMount();
	void freezeWeather(bool frozen);
	void setWeather(char* weatherType);
	Hash getNextWeather();
	void getWeatherTransition(Hash* weatherType1, Hash* weatherType2, float* percentWeather2);
	void setWeatherTransition(Hash weatherType1, Hash weatherType2, float percentWeather2);
	void setSnowLevel(float level);
	void setSnowCoverage(int coverage);
	Hash getHash(char* key);
	Blip addBlip(Hash blipHash, Ped ped);
	array<Vector3, 16> findLocationsAroundPlayer(float distance, float a, float b);
	Vector3 findLocationInFrontOfPlayer(float distance, float a, float b);
	void addPedToWorld(Ped ped, char* relationship, bool isHostileToPlayer, Vector3 turnToCoords);
	void taskAttackPlayer(Ped ped);
	void taskWanderInArea(Ped ped, float x, float y, float z, float radius, float minimalLength, float timeBetween);
	void taskWanderInArea(Ped ped, float x, float y, float z);
	float groundAt(Vector3 location);
	bool hasBlip(Entity entity);
	void enemyBlip(Ped ped);
	Ped spawnPedAt(char* model, Vector3 coords, Vector3 turnToCoords, bool withBlip, bool hostileToPlayer);
	Ped spawnRelativeToPlayer(char* model, float distance, float a, float b, bool withBlip, bool hostileToPlayer);
	int createGroup();
	void setPedGroupMember(Ped ped, int groupId);
	void setPedGroupLeader(Ped ped, int groupId);
	Hash repeaterCarbine();
	Hash cattlemanRevolver();
	Hash vampireKnife();
	void givePedWeapon(Ped ped, Hash weaponHash, int ammo);
	bool isPaused();
	int getGameHour();
	int getGameMinute();
	int getGameSecond();
	void setGameTime(int hours, int minutes, int seconds);
	void addExplosion(Vector3 coords);
	void setEntityHealth(Entity entity, int health);
	float distanceBetween(Vector3 a, Vector3 b);
	void deletePed(Ped ped);
	bool isEntityDead(Entity entity);
	bool isPedDeadOrDying(Ped ped);
	void addSnowBlanket(int coverage);
	void removeSnowBlanket(char* replacementWeather);
	bool detectHeadShot(Ped victim);
	void notificationTopLeft(char* text, int duration);
	void notificationRight(char* text, char* dict, char* icon, char* colour, int duration);
	void toastRight(char* text, char* dict, char* icon);
	void notifyHeadShot();
	void toast(char* text);
	void notificationTitled(char* title, char* subTitle, char* dict, char* icon, char* color, int duration);
	void notificationAlert(char* text);
	void addMoneyLoot(Ped ped, int pennies);
	void fadeOut();
	void fadeIn();
	void removeAllPickups(Hash pickup);
};

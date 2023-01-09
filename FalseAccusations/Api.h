#pragma once

#include <cmath>
#include <string>
#include "../../inc/types.h"
#include "../../inc/natives.h"

class Api
{
private:
	Player getPlayer();
	Ped getPlayerPed();
	Vector3 getOffsetFromPlayerInWorldCoords(float offsetX, float offsetY, float offsetZ);
	void setPlayerWantedLevel(int wantedLevel);
	void loadModel(Hash modelHash, bool b);
	void loadTexture(char* dict);
	Ped createPed(Hash skin, Vector3 location, bool onGround);

public:
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
	bool isPlayerInvincible();
	void togglePlayerInvincible();
	bool isPlayerOnMount();
	Ped getPlayerMount();
	void setWeather(char* weatherType);
	void setSnowLevel(float level);
	void setSnowCoverage(int coverage);
	Hash getHash(char* key);
	Blip addBlip(Hash blipHash, Ped ped);
	Vector3 findLocationRelativeToPlayer(float distance, float a, float b);
	void addPedToWorld(Ped ped, char* relationship, bool isHostileToPlayer, Vector3 turnToCoords, char* blipStyle);
	float groundAt(Vector3 location);
	Ped spawnRelativeToPlayer(char* model, float distance, float a, float b);
	int createGroup();
	void setPedGroupMember(Ped ped, int groupId);
	void setPedGroupLeader(Ped ped, int groupId);
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
	void notifyHeadShot();
	void toast(char* text);
	void notificationTitled(char* title, char* subTitle, char* dict, char* icon, char* color, int duration);
};

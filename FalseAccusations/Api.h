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
	char* createString(const char* text);
	void displaySubTitle(const char* text);
	void playNotification();
	void playInformational();
	void loadModel(Hash modelHash, bool b);
	Ped createPed(Hash skin, Vector3 location);

public:
	void debugText(const char* text);
	Vector3 getPlayerCoords();
	Vector3 getEntityCoords(Entity entity);
	float getPlayerHeading();
	int getMaxWantedLevel();
	int getPlayerWantedLevel();
	void incrementPlayerWantedLevel();
	void reportCrime(Hash crime);
	void giveMoney();
	void toast(const char* text);
	void drawText(const char* text, float x, float y);
	void drawRectangle(float x, float y, float width, float height);
	bool isPlayerInvincible();
	void togglePlayerInvincible();
	bool isPlayerOnMount();
	Ped getPlayerMount();
	void setWeather(const char* weatherType);
	void setSnowLevel(float level);
	void setSnowCoverage(int coverage);
	Hash getHash(char* key);
	Blip addBlip(Hash blipHash, Ped ped);
	Vector3 findLocationNearPlayer(float distance);
	void addPedToWorld(Ped ped, char* relationship, bool isHostileToPlayer, Vector3 turnToCoords, char* blipStyle);
	Ped spawnHostilePedNearPlayer(char* model);
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
	void addSnowBlanket(int coverage);
	void removeSnowBlanket(char* replacementWeather);
	bool detectHeadShot(Ped victim);
};

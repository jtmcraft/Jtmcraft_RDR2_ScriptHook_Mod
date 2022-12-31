#pragma once

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
	void requestModel(Hash modelHash, bool b);

public:
	void debugText(const char* text);
	Vector3 getPlayerCoords();
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
};

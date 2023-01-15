#include "ScriptDataModel.h"

ScriptDataModel::ScriptDataModel() {
	setDefaults();
}

void ScriptDataModel::setDefaults() {
	timeToWait = 3480;
	timeElapsed = 0;
	chance = 10;
}

double ScriptDataModel::getTimeToWait()
{
	return timeToWait;
}

double ScriptDataModel::getTimeElapsed() {
	return timeElapsed;
}

int ScriptDataModel::getChance()
{
	return chance;
}

void ScriptDataModel::setTimeToWait(double timeToWait)
{
	this->timeToWait = timeToWait;
}

void ScriptDataModel::setTimeElapsed(double timeElapsed) {
	this->timeElapsed = timeElapsed;
}

void ScriptDataModel::addTimeElapsed(double delta) {
	timeElapsed += delta;
}

void ScriptDataModel::setChance(int chance)
{
	this->chance = chance;
}

void ScriptDataModel::increaseChance() {
	timeToWait /= 2;
	chance += 5;
	timeElapsed = 0;
}

#pragma once

class ScriptDataModel
{
private:
	double timeToWait;
	double timeElapsed;
	int chance;

public:
	ScriptDataModel();
	void setDefaults();
	double getTimeToWait();
	double getTimeElapsed();
	int getChance();
	void setTimeToWait(double timeToWait);
	void setTimeElapsed(double timeElapsed);
	void addTimeElapsed(double delta);
	void setChance(int chance);
	void increaseChance();
};

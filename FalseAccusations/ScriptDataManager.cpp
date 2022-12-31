#include "ScriptDataManager.h"

using namespace std;

ScriptDataManager::ScriptDataManager() {
	fileName = "jtm.dat";
	bool isEmpty;

	dataFile.open(fileName, ios_base::in);
	isEmpty = (dataFile.peek() == fstream::traits_type::eof());
	dataFile.close();

	if (isEmpty) {
		ScriptDataModel dataModel = ScriptDataModel();
		dataModel.setDefaults();
		write(dataModel);
	}
}

void ScriptDataManager::write(ScriptDataModel dataModel) {
	dataFile.open(fileName, ios_base::out);
	dataFile << dataModel.getTimeToWait() << " " << dataModel.getTimeElapsed() << " " << dataModel.getChance();
	dataFile.close();
}

ScriptDataModel ScriptDataManager::read() {
	double timeToWait;
	double timeElapsed;
	int chance;

	dataFile.open(fileName, ios_base::in);
	dataFile >> timeToWait >> timeElapsed >> chance;
	dataFile.close();

	ScriptDataModel dataModel = ScriptDataModel();
	dataModel.setTimeToWait(timeToWait);
	dataModel.setTimeElapsed(timeElapsed);
	dataModel.setChance(chance);

	return dataModel;
}

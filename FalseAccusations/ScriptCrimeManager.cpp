#include "ScriptCrimeManager.h"

using namespace std;

ScriptCrimeManager::ScriptCrimeManager() {
	dataModel = ScriptDataModel();
}

ScriptDataModel ScriptCrimeManager::getDataModel() {
	return dataModel;
}

void ScriptCrimeManager::setDataModel(ScriptDataModel dataModel) {
	this->dataModel = dataModel;
}

Hash ScriptCrimeManager::randomCrime() {
	int dim = (sizeof(CRIMES) / sizeof(CRIMES[0]));

	return CRIMES[rand() % dim];
}

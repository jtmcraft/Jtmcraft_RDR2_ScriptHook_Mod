#include "ScriptCrimeController.h"

using namespace std;

ScriptCrimeController::ScriptCrimeController() {
	dataModel = ScriptDataModel();
}

ScriptDataModel ScriptCrimeController::getDataModel() {
	return dataModel;
}

void ScriptCrimeController::setDataModel(ScriptDataModel dataModel) {
	this->dataModel = dataModel;
}

Hash ScriptCrimeController::randomCrime() {
	int dim = (sizeof(CRIMES) / sizeof(CRIMES[0]));

	return CRIMES[rand() % dim];
}

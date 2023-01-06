#include "ScriptInfoPanel.h"

using namespace std;

ScriptInfoPanel::ScriptInfoPanel() {
	api = Api();
}

void ScriptInfoPanel::tick(ScriptDataModel dataModel) {
	stringstream msg;
	Vector3 coords = api.getPlayerCoords();
	float heading = api.getPlayerHeading();
	double timeToWait = dataModel.getTimeToWait();
	double elapsedTime = dataModel.getTimeElapsed();
	int chance = dataModel.getChance();

	msg << "X: " << coords.x << endl << "Y: " << coords.y << endl << "Z: " << coords.z << endl << "H: " << heading
		<< endl << "Wait: " << timeToWait << endl << "Elapsed: " << floor(elapsedTime) << endl << "Chance: " << chance;

	api.drawRectangle(0.04, 0.04, 0.15, 0.2);
	api.drawText(msg.str().c_str(), 0.05, 0.05);
}

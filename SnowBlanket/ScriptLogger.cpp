#include "ScriptLogger.h"

using namespace std;

ofstream logFile;

ScriptLogger::ScriptLogger() {
	fileName = "jtm.log";

	logFile.open(fileName, ios_base::out);
	logFile.close();
}

void ScriptLogger::log(const char* msg) {
	stringstream txt;
	struct tm current_tm;
	__time64_t t64;
	char stamp[50];
	errno_t err;

	logFile.open(fileName, ios_base::app);
	if (logFile.is_open())
	{
		_time64(&t64);
		err = _localtime64_s(&current_tm, &t64);

		if (!err) {
			err = asctime_s(stamp, 26, &current_tm);

			if (!err) {
				txt << "[ False Accusations ] " << stamp << msg;
				logFile << txt.str().c_str() << endl;
				logFile.close();
			}
		}
	}
}

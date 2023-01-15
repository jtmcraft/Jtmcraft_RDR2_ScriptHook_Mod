#pragma once

#include <fstream>
#include <sstream>
#include <ctime>

class ScriptLogger
{
private:
	char* fileName;

public:
	ScriptLogger();
	void log(const char* str);
};

#include <iostream>
#include <vector>
#include <chrono>

#include "../Logger/LoggerHandler.h"


int main(int argc, char* argv[])
{
	LoggerHandler logger;
	logger.begin("Welcome to this new project.");

	auto stage_log = FireStageChangeLog();
	stage_log.execute(logger, Message ("Intro log!", Location(__FILE__, __LINE__, 69, __FUNCTION__) ));

	return 0;
}

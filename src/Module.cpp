#include "Module.hpp"

Module::Module(const char * name, int taskCore) : Thread(name, taskCore) {
}

void Module::testReset() {
	if (--this->remainingAttempts == 0) {
		esp_restart();
	}
}

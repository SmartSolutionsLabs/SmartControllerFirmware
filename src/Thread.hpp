#ifndef INC_SMART_THREAD
#define INC_SMART_THREAD

#include <Arduino.h>

#include "esp_task_wdt.h"

class Thread {
	protected:
		TaskHandle_t taskHandler = nullptr;
		int taskCore;
		const int taskPriority = 1;
		const char * name;

		/**
		 * Iteration speed.
		 */
		TickType_t iterationDelay = 1000 / portTICK_PERIOD_MS;

	public:
		Thread(const char * name, int taskCore = 0);

		Thread();

		void setTaskCore(int core) {
			taskCore = core;
		}

		static void runTask(void* data);

		void start();

		void suspend();

		void resume();

		/**
		 * Should not be used because this thread must be perpetual.
		 */
		void stop();

		virtual void run(void* data) = 0; // Make run pure virtual
};

#endif

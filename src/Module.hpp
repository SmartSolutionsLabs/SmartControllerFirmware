#ifndef INC_SMART_MODULE
#define INC_SMART_MODULE

#include "Thread.hpp"

/**
 * Controlling any hardware.
 */
class Module : public Thread {
	protected:
		bool connectedStatus;

		unsigned int remainingAttempts = 10;

	public:
		Module(const char * name, int taskCore = 0);

		/**
		 * Here starts.
		 */
		virtual void connect(void * data) = 0;

		virtual void run(void* data) = 0;

		void testReset();

		bool isConnected() const {
			return connectedStatus;
		}

		void resetRemaining() {
			remainingAttempts = 10;
		}
};

#endif

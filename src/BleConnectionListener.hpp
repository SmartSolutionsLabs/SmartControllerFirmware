#ifndef INC_SMART_BLE_CONNECTION_LISTENER
#define INC_SMART_BLE_CONNECTION_LISTENER

#include <BLEServer.h>
#include <Arduino.h>

#include "Application.hpp"

class BleConnectionListener : public BLEServerCallbacks {
	private:
		Application * application = nullptr;

	public:
		BleConnectionListener(Application * application);
		void onConnect(BLEServer * bluetoothServer);
		void onDisconnect(BLEServer * bluetoothServer);
};
#endif

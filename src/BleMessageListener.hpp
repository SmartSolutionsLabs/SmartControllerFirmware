#ifndef INC_SMART_BLE_LISTENER
#define INC_SMART_BLE_LISTENER

#include <BLEServer.h>
#include <Arduino.h>

#include "Application.hpp"

class BleMessageListener : public BLECharacteristicCallbacks {
	private:
		Application * application = nullptr;

	public:
		BleMessageListener(Application * application);

		void onWrite(BLECharacteristic * pCharacteristic);
};
#endif

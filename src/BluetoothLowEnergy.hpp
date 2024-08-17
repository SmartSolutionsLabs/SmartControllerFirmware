#ifndef INC_SMART_BLE
#define INC_SMART_BLE

#ifdef __SMART_APPLICATION_WITH_BLE__

#include "BleMessageListener.hpp"
#include "BleConnectionListener.hpp"

#include <Arduino.h>
#include <BLEDevice.h>
#include <BLE2902.h>

#ifndef BLE_SERVICE_UUID
#define BLE_SERVICE_UUID "49e0b347-e722-4ac0-92fb-a316e887fdea"
#endif

#define MTU_SIZE 517

class BluetoothLowEnergy {
	private:
		BLEDevice device;
		BLEService * dataService = nullptr;
		BleConnectionListener * connectionListener = nullptr;

	public:
		BluetoothLowEnergy(Application * application);

		static BleMessageListener * bleCallback;

		static BLEServer * bluetoothServer;
};

#endif

#endif // About including BLE

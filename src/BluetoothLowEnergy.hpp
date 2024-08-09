#ifndef INC_SMART_BLE
#define INC_SMART_BLE

#ifdef __SMART_APPLICATION_WITH_BLE__

#include "BleMessageListener.hpp"
#include "BleConnectionListener.hpp"

#include <Arduino.h>
#include <BLEDevice.h>
#include <BLE2902.h>

#define BLE_SERVICE_UUID  "49e0b347-e722-4ac0-92fb-a316e887fdea"
#define BLE_READ_UUID     "52491fd0-7498-4cd5-9cd6-b03c1d3b5272"  // Listen
#define BLE_WRITE_UUID    "64f316dc-0a57-49f0-9f48-9500a9009d93"  // Send out
#define BLE_STATUS_UUID   "a12f4c9e-503b-45eb-8d7b-7fb774cf51d1"  // Notify sensor data

#define MTU_SIZE 517

class BluetoothLowEnergy {
	private:
		BLEDevice device;
		BLEService * dataService = nullptr;
		BleConnectionListener * connectionListener = nullptr;

	public:
		BluetoothLowEnergy(Application * application);

		static BleMessageListener * bleCallback;

		static BLECharacteristic *resCharacteristic;
		static BLECharacteristic *statusCharacteristic;
		static BLECharacteristic *reqCharacteristic;

		static BLEServer * bluetoothServer;
};

#endif

#endif // About including BLE

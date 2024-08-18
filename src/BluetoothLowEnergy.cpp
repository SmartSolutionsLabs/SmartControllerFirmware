#ifdef __SMART_APPLICATION_WITH_BLE__

#include "BluetoothLowEnergy.hpp"

BLEServer * BluetoothLowEnergy::bluetoothServer = nullptr;

BluetoothLowEnergy::BluetoothLowEnergy(Application * application) {
	this->device.init(application->getBluetoothName().c_str()); // name in list of search.
	this->device.setMTU(MTU_SIZE);
	this->bluetoothServer = this->device.createServer();

	// We always need to call it
	application->initializeBluetoothCharacteristicsArray();

	this->bluetoothServer->setCallbacks(new BleConnectionListener(application));

	this->service = this->bluetoothServer->createService(BLE_SERVICE_UUID);

	unsigned int bleCharacteristicsIndex = application->getBluetoothCharacteristicsQuantity();
	while (bleCharacteristicsIndex) {
		--bleCharacteristicsIndex; // offset from quantity
		BLECharacteristic * characteristic = application->getBluetoothCharacteristic(bleCharacteristicsIndex);

		if (bleCharacteristicsIndex == 0) { // first element must be to receive data
			characteristic->setCallbacks(new BleMessageListener(application));
		}

		this->service->addCharacteristic(characteristic);
	}

	this->service->start();

	BluetoothLowEnergy::bluetoothServer->getAdvertising()->start();

	Serial.print("BT server created\n");
}

#endif // About including BLE

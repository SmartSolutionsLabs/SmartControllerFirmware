#ifdef __SMART_APPLICATION_WITH_BLE__

#include "BluetoothLowEnergy.hpp"

BleMessageListener * BluetoothLowEnergy::bleCallback = nullptr;

BLEServer * BluetoothLowEnergy::bluetoothServer = nullptr;

BluetoothLowEnergy::BluetoothLowEnergy(Application * application) {
	this->device.init(application->getBluetoothName().c_str()); // name in list of search.
	this->device.setMTU(MTU_SIZE);
	this->bluetoothServer = this->device.createServer();

	this->connectionListener = new BleConnectionListener(application);

	this->bluetoothServer->setCallbacks(this->connectionListener);

	this->dataService = this->bluetoothServer->createService(BLE_SERVICE_UUID);

	BluetoothLowEnergy::bleCallback = new BleMessageListener(application);

	application->getBluetoothCharacteristic(0)->setCallbacks(BluetoothLowEnergy::bleCallback);

	unsigned int bleCharacteristicsQuantity = application->getBluetoothCharacteristicsQuantity();
	if (bleCharacteristicsQuantity > 0) {
		while (--bleCharacteristicsQuantity > 0) {
			application->getBluetoothCharacteristic(bleCharacteristicsQuantity)->addDescriptor(new BLE2902());
		}
	}

	this->dataService->start();

	BluetoothLowEnergy::bluetoothServer->getAdvertising()->start();

	Serial.print("BT server created\n");
}

#endif // About including BLE

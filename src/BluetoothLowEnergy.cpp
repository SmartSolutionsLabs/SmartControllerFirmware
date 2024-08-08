#ifdef __SMART_APPLICATION_WITH_BLE__

#include "BluetoothLowEnergy.hpp"

BleMessageListener * BluetoothLowEnergy::bleCallback = nullptr;

BLECharacteristic * BluetoothLowEnergy::resCharacteristic = nullptr;
BLECharacteristic * BluetoothLowEnergy::reqCharacteristic = nullptr;
BLECharacteristic * BluetoothLowEnergy::statusCharacteristic = nullptr;

BLEServer * BluetoothLowEnergy::bluetoothServer = nullptr;

BluetoothLowEnergy::BluetoothLowEnergy(Application * application) {
	this->device.init(application->getBluetoothName().c_str()); // name in list of search.
	this->device.setMTU(MTU_SIZE);
	this->bluetoothServer = this->device.createServer();

	this->connectionListener = new BleConnectionListener(application);

	this->bluetoothServer->setCallbacks(this->connectionListener);

	this->dataService = this->bluetoothServer->createService(BLE_SERVICE_UUID);

	this->reqCharacteristic = this->dataService->createCharacteristic(
		BLE_READ_UUID,
		BLECharacteristic::PROPERTY_WRITE
	);

	BluetoothLowEnergy::bleCallback = new BleMessageListener(application);

	BluetoothLowEnergy::reqCharacteristic->setCallbacks(BluetoothLowEnergy::bleCallback);

	BluetoothLowEnergy::resCharacteristic = this->dataService->createCharacteristic(
		BLE_WRITE_UUID,
		BLECharacteristic::PROPERTY_NOTIFY
	);
	BluetoothLowEnergy::resCharacteristic->addDescriptor(new BLE2902());

	BluetoothLowEnergy::statusCharacteristic = this->dataService->createCharacteristic(
		BLE_STATUS_UUID,
		BLECharacteristic::PROPERTY_NOTIFY
	);
	BluetoothLowEnergy::statusCharacteristic->addDescriptor(new BLE2902());

	this->dataService->start();

	BluetoothLowEnergy::bluetoothServer->getAdvertising()->start();

	Serial.print("BT server created\n");
}

#endif // About including BLE

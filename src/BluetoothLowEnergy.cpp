#include "BluetoothLowEnergy.hpp"

BleMessageListener * Ble::bleCallback = nullptr;

BLECharacteristic * BluetoothLowEnergy::resCharacteristic = nullptr;
BLECharacteristic * Ble::reqCharacteristic = nullptr;
BLECharacteristic * Ble::statusCharacteristic = nullptr;

BLEServer * BluetoothLowEnergy::bluetoothServer = nullptr;

BluetoothLowEnergy::BluetoothLowEnergy(const char * name) {
	this->device.init(name); // name of SSID.
	this->device.setMTU(MTU_SIZE);
	this->bluetoothServer = this->device.createServer();

	this->connectionListener = new BleConnectionListener();

	this->bluetoothServer->setCallbacks(this->connectionListener);

	this->dataService = this->bluetoothServer->createService(BLE_SERVICE_UUID);

	this->reqCharacteristic = this->dataService->createCharacteristic(
		BLE_READ_UUID,
		BLECharacteristic::PROPERTY_WRITE
	);

	BluetoothLowEnergy::bleCallback = new BleMessageListener();

	BluetoothLowEnergy::reqCharacteristic->setCallbacks(Ble::bleCallback);

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

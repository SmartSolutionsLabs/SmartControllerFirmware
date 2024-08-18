#ifdef __SMART_APPLICATION_WITH_BLE__

#include "BluetoothLowEnergy.hpp"

BluetoothLowEnergy::BluetoothLowEnergy(Application * application) {
	this->application = application;

	this->device.init(application->getBluetoothName().c_str()); // name in list of search.
	this->device.setMTU(MTU_SIZE);
	this->server = this->device.createServer();

	// We always need to call it
	application->initializeBluetoothCharacteristicsArray();

	this->server->setCallbacks(new BleConnectionListener(application));

	this->service = this->server->createService(BLE_SERVICE_UUID);

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

	this->server->getAdvertising()->start();

	Serial.print("BT server created\n");
}

BLEServer * BluetoothLowEnergy::getServer() const {
	return this->server;
}

void BluetoothLowEnergy::checkAdvertising() {
	const static TickType_t xDelay = 300 / portTICK_PERIOD_MS;

	// disconnecting
	if (!this->application->getBluetoothDeviceConnected() && this->application->getOldBluetoothDeviceConnected()) {
		vTaskDelay(xDelay); // give the bluetooth stack the chance to get things ready
		this->server->startAdvertising(); // restart advertising
		Serial.println("restart BT advertising");
		this->application->setOldBluetoothDeviceConnected(this->application->getBluetoothDeviceConnected());
	}

	// connecting
	if (this->application->getBluetoothDeviceConnected() && !this->application->getOldBluetoothDeviceConnected()) {
		// do stuff here on connecting
		this->application->setOldBluetoothDeviceConnected(this->application->getBluetoothDeviceConnected());
	}
}

#endif // About including BLE

#ifdef __SMART_APPLICATION_WITH_BLE__

#include "BleConnectionListener.hpp"
#include "Application.hpp"

BleConnectionListener::BleConnectionListener(Application * application) : application(application) {
}

void BleConnectionListener::onConnect(BLEServer * bluetoothServer) {
	this->application->setBluetoothDeviceConnected(true);
}

void BleConnectionListener::onDisconnect(BLEServer * bluetoothServer) {
	this->application->setBluetoothDeviceConnected(false);
}

#endif // About including BLE

#include "Application.hpp"
#include "BluetoothLowEnergy.hpp"

Application::~Application() {
#ifdef __SMART_APPLICATION_WITH_BLE__
	if (this->bleCharacteristics != nullptr) {
		delete[] this->bleCharacteristics;
	}
#endif
}

#ifdef __SMART_APPLICATION_WITH_BLE__

bool Application::getBluetoothDeviceConnected() const {
	return this->bluetoothDeviceConnected;
}

bool Application::getOldBluetoothDeviceConnected() const {
	return this->oldBluetoothDeviceConnected;
}

void Application::setBluetoothDeviceConnected(bool connected) {
	this->bluetoothDeviceConnected = connected;
}

void Application::setOldBluetoothDeviceConnected(bool connected) {
	this->oldBluetoothDeviceConnected = connected;
}

void Application::setBluetoothName(String bluetoothName, bool persistent){
	this->deviceBluetoothName = bluetoothName;
}

String Application::getBluetoothName() const{
	return this->deviceBluetoothName;
}

BLECharacteristic * Application::getBluetoothCharacteristic(unsigned int index) const {
	return &this->bleCharacteristics[index];
}

size_t Application::getBluetoothCharacteristicsQuantity() const {
	return this->bluetoothCharacteristicsQuantity;
}
#endif // About BLE

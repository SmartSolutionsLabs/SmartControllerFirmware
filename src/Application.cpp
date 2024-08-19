#include "Application.hpp"
#include "BluetoothLowEnergy.hpp"

Application::~Application() {
#ifdef __SMART_APPLICATION_WITH_BLE__
	if (this->bleCharacteristics != nullptr) {
		delete[] this->bleCharacteristics;
	}
#endif

	if (this->modulesPointer != nullptr) {
		while (this->modulesPointerQuantity) {
			delete this->modulesPointer[--this->modulesPointerQuantity];
		}
		delete[] this->modulesPointer;
	}
}

#ifdef __SMART_APPLICATION_WITH_BLE__
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

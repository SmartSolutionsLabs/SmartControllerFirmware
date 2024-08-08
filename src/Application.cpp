#include "Application.hpp"
#include "BluetoothLowEnergy.hpp"

#ifdef __SMART_APPLICATION_WITH_BLE__
void Application::checkAdvertising() {
	const static TickType_t xDelay = 500 / portTICK_PERIOD_MS;
	// disconnecting
	if (!this->bluetoothDeviceConnected && this->oldBluetoothDeviceConnected) {
		vTaskDelay(xDelay); // give the bluetooth stack the chance to get things ready
		BluetoothLowEnergy::bluetoothServer->startAdvertising(); // restart advertising
		Serial.println("restart BT advertising");
		this->oldBluetoothDeviceConnected = this->bluetoothDeviceConnected;
	}

	// connecting
	if (this->bluetoothDeviceConnected && !this->oldBluetoothDeviceConnected) {
		// do stuff here on connecting
		this->oldBluetoothDeviceConnected = this->bluetoothDeviceConnected;
	}
}

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
#endif // About BLE

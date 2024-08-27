#ifdef __SMART_APPLICATION_WITH_BLE__

#include "BleMessageListener.hpp"
#include "BluetoothLowEnergy.hpp"

BleMessageListener::BleMessageListener(Application * application) : application(application) {
}

void BleMessageListener::onWrite(BLECharacteristic * characteristic) {
	unsigned int len = characteristic->getValue().length();
	if (len > 0) {
		char * message = new char[len + 1]; // plus 1 for null terminator
		memcpy(message, characteristic->getValue().c_str(), len);

		this->application->processMessage(message, true);
	}
}

#endif // About including BLE

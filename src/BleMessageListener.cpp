#ifdef __SMART_APPLICATION_WITH_BLE__

#include "BleMessageListener.hpp"
#include "BluetoothLowEnergy.hpp"

BleMessageListener::BleMessageListener(Application * application) : application(application) {
}

void BleMessageListener::onWrite(BLECharacteristic * characteristic) {
	String * message = new String(characteristic->getValue().c_str());
	if (message->length() > 0){
		this->application->processMessage(message);
		return;
	}
	delete[] message;
}

#endif // About including BLE

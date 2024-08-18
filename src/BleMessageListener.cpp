#ifdef __SMART_APPLICATION_WITH_BLE__

#include "BleMessageListener.hpp"
#include "BluetoothLowEnergy.hpp"

BleMessageListener::BleMessageListener(Application * application) : application(application) {
}

void BleMessageListener::onWrite(BLECharacteristic * characteristic) {
	String input(characteristic->getValue().c_str());
	if (input.length() > 0){
		this->application->processMessage(&input);
	}
}

#endif // About including BLE

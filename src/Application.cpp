#include "Application.hpp"
#include "BluetoothLowEnergy.hpp"

void Application::beginSerialPort(HardwareSerial& serial, unsigned long baud, uint32_t config, int8_t rxPin, int8_t txPin) {
	serial.setRxBufferSize(APPLICATION_SERIAL_BUFFER_SIZE);
	serial.begin(baud, config, rxPin, txPin);
	serial.onReceive([&]() {
		static unsigned char buffer[APPLICATION_SERIAL_BUFFER_SIZE] = {0};
		static unsigned int bufferCharPosition = 0;
		static unsigned char c;

		while (serial.available() > 0) {
			c = (unsigned char) serial.read();
			if (c != '\n') {
				buffer[bufferCharPosition] = c; // append each character
				bufferCharPosition++; // next character position

				// process and reset if buffer is full
				if (bufferCharPosition >= APPLICATION_SERIAL_BUFFER_SIZE) {
					this->processSerialBuffer(buffer, bufferCharPosition);
					bufferCharPosition = 0;
				}
			}
			else {
				this->processSerialBuffer(buffer, bufferCharPosition);
				bufferCharPosition = 0;
			}
		}

		// process data ramaining
		if (bufferCharPosition > 0) {
			this->processSerialBuffer(buffer, bufferCharPosition);
		}

		bufferCharPosition = 0;
	});
}

void Application::processSerialBuffer(unsigned char buffer[], size_t length) {
	unsigned char * message = new unsigned char[length + 1]; // plus 1 for null terminator
	memcpy(message, buffer, length);

	this->processMessage(message, length, false);

	// Reset the buffer for next data
	memset(buffer, 0, APPLICATION_SERIAL_BUFFER_SIZE);
}

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

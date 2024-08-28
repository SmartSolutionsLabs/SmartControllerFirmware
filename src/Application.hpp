#ifndef INC_SMART_APPLICATION
#define INC_SMART_APPLICATION

#include <Arduino.h>
#include <BLECharacteristic.h>

#include <Module.hpp>

#ifndef APPLICATION_SERIAL_BUFFER_SIZE
#define APPLICATION_SERIAL_BUFFER_SIZE 512
#endif

class Application {
	protected:
#ifdef __SMART_APPLICATION_WITH_BLE__
		bool bluetoothDeviceConnected = false;
		bool oldBluetoothDeviceConnected = false;

		String deviceBluetoothName;

		// Pointer to fill it in derived
		BLECharacteristic * bleCharacteristics = nullptr;
		size_t bluetoothCharacteristicsQuantity = 0;
#endif

		Module ** modulesPointer = nullptr;
		size_t modulesPointerQuantity = 0;

	public:
		/**
		 * Set a callback to redirect input towards processMessage().
		 */
		void beginSerialPort(HardwareSerial& serial, unsigned long baud = 115200, uint32_t config = SERIAL_8N1, int8_t rxPin = -1, int8_t txPin = -1);

		/**
		 * Event to handle message that is generally a string.
		 */
		virtual void processMessage(unsigned char * message, size_t length, bool printable) = 0;

		virtual ~Application();

		virtual void initializeModulesPointerArray() = 0;

#ifdef __SMART_APPLICATION_WITH_BLE__
		inline bool getBluetoothDeviceConnected() const {
			return bluetoothDeviceConnected;
		}
		inline bool getOldBluetoothDeviceConnected() const {
			return oldBluetoothDeviceConnected;
		}
		inline void setBluetoothDeviceConnected(bool connected) {
			bluetoothDeviceConnected = connected;
		}
		inline void setOldBluetoothDeviceConnected(bool connected) {
			oldBluetoothDeviceConnected = connected;
		}
		String getBluetoothName() const;
		void setBluetoothName(String bluetoothName, bool persistent = true);

		virtual void initializeBluetoothCharacteristicsArray() = 0;
		BLECharacteristic * getBluetoothCharacteristic(unsigned int index) const;
		size_t getBluetoothCharacteristicsQuantity() const;
#endif // About Bluetooth Low Energy

#ifdef __SMART_APPLICATION_WITH_WIFI__
		void getWifiCredentials(String &ssid, String &password) const;
		void setWifiCredentials(String &ssid, String &password);
#endif // About WiFi

		private:
			void processSerialBuffer(unsigned char buffer[], size_t length);
};

#endif

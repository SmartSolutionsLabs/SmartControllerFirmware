#ifndef INC_SMART_APPLICATION
#define INC_SMART_APPLICATION

#include <Arduino.h>
#include <BLECharacteristic.h>

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

	public:
		/**
		 * Event to handle message that is generally a string.
		 */
		virtual void processMessage(void* message) = 0;

		virtual ~Application();

#ifdef __SMART_APPLICATION_WITH_BLE__
		bool getBluetoothDeviceConnected() const;
		bool getOldBluetoothDeviceConnected() const;
		void setBluetoothDeviceConnected(bool connected);
		void setOldBluetoothDeviceConnected(bool connected);
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
};

#endif

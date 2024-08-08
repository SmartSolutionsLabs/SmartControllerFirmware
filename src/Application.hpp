#ifndef INC_SMART_APPLICATION
#define INC_SMART_APPLICATION

#include <Arduino.h>

class Application {
	protected:
#ifdef __SMART_APPLICATION_WITH_BLE__
		bool bluetoothDeviceConnected = false;
		bool oldBluetoothDeviceConnected = false;

		String deviceBluetoothName;
#endif

	public:
		/**
		 * Event to handle message that is generally a string.
		 */
		virtual void processMessage(void* message) = 0;

#ifdef __SMART_APPLICATION_WITH_BLE__
		bool getBluetoothDeviceConnected() const;
		bool getOldBluetoothDeviceConnected() const;
		void setBluetoothDeviceConnected(bool connected);
		void setOldBluetoothDeviceConnected(bool connected);
		void checkAdvertising();
		String getBluetoothName() const;
#endif // About Bluetooth Low Energy

#ifdef __SMART_APPLICATION_WITH_WIFI__
		void getWifiCredentials(String &ssid, String &password) const;
		void setWifiCredentials(String &ssid, String &password);
#endif // About WiFi
};

#endif

#ifndef INC_SMART_NETWORK
#define INC_SMART_NETWORK

#ifdef __SMART_APPLICATION_WITH_WIFI__

#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <ElegantOTA.h>

#ifndef MAX_ATTEMPTS_QUANTITY
#define MAX_ATTEMPTS_QUANTITY 4
#endif

class Network {
	protected:
		static Network * network;
		Network(const char * hostname);

		static uint32_t remainingAttempts;

	public:
		void operator=(const Network &) = delete;
		static Network * getInstance(const char * hostname);
		Network(Network &other) = delete;

		AsyncWebServer server;

		/**
		 * Call it when change the credentials.
		 */
		void connect();

		// credentials caché
		static String SSID;
		static String PASSWORD;
};

#endif

#endif // About including __SMART_APPLICATION_WITH_WIFI__

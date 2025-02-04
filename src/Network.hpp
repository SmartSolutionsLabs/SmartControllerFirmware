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

/**
 * Helper class for managing network over WiFi.
 */
class Network {
	protected:
		static Network * network;
		Network();

		static uint32_t remainingAttempts;

	public:
		void operator=(const Network &) = delete;
		static Network * getInstance();
		Network(Network &other) = delete;

		AsyncWebServer server;

		/**
		 * Set WiFi mode and starts a HTTP server.
		 */
		void begin(const char * hostname, bool withOTA);

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

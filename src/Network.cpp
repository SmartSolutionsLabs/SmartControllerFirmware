#ifdef __SMART_APPLICATION_WITH_WIFI__

#include "Network.hpp"

#include <functional>

String Network::SSID;
String Network::PASSWORD;
uint32_t Network::remainingAttempts;

Network * Network::network = nullptr;

Network * Network::getInstance() {
	if (network == nullptr) {
		network = new Network();
	}

	return network;
}

Network::Network() : server(80) {
	WiFi.mode(WIFI_STA);
	WiFi.config(INADDR_NONE, INADDR_NONE, INADDR_NONE, INADDR_NONE);

	server.on("/", HTTP_GET, [](AsyncWebServerRequest * request) {
		request->send(200, "text/plain", "This is the ESP HTTP server.");
	});

	// Start AsyncElegantOTA
	ElegantOTA.begin(&server);
	ElegantOTA.setAutoReboot(true);
	ElegantOTA.onStart([]() {
		Serial.print("OTA update started!\n");
	});
	ElegantOTA.onProgress([](size_t current, size_t final) {
		Serial.printf("OTA progress: %u%%\n", (current * 100) / final);
	});
	ElegantOTA.onEnd([](bool success) {
		if (success) {
			Serial.println("OTA update completed successfully.");
		}
		else {
			Serial.println("OTA update failed.");
			// Add failure handling here.
		}
	});

	server.begin();

	// Delete old configuration
	WiFi.disconnect(true);
}

void Network::connect() {
	if (Network::SSID == "" || Network::PASSWORD == "") {
		Serial.print("No net credentials.");
		return;
	}

	// Reset the counter
	Network::remainingAttempts = MAX_ATTEMPTS_QUANTITY;

	// Attempt the connection
	WiFi.begin(Network::SSID, Network::PASSWORD);
}

#endif // About including __SMART_APPLICATION_WITH_WIFI__

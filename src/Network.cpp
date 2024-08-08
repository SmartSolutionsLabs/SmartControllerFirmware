#include "Network.hpp"

String Network::SSID;
String Network::PASSWORD;
uint32_t Network::remainingAttempts;

Network * Network::network = nullptr;

Network * Network::getInstance(const char * hostname) {
	if (network == nullptr) {
		network = new Network(hostname);
	}

	return network;
}

Network::Network(const char * hostname) : server(80) {
	WiFi.mode(WIFI_STA);
	WiFi.config(INADDR_NONE, INADDR_NONE, INADDR_NONE, INADDR_NONE);
	WiFi.setHostname(hostname);

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

	WiFi.onEvent(onConnected, WiFiEvent_t::ARDUINO_EVENT_WIFI_STA_CONNECTED);
	WiFi.onEvent(onAddressed, WiFiEvent_t::ARDUINO_EVENT_WIFI_STA_GOT_IP);
	WiFi.onEvent(onDisconnected, WiFiEvent_t::ARDUINO_EVENT_WIFI_STA_DISCONNECTED);
}

void Network::onConnected(WiFiEvent_t event, WiFiEventInfo_t info) {
	Serial.print("WiFi.connected\n");
}

void Network::onAddressed(WiFiEvent_t event, WiFiEventInfo_t info) {
	Serial.print("WiFi.addressed: ");
	Serial.println(WiFi.localIP());
}

void Network::onDisconnected(WiFiEvent_t event, WiFiEventInfo_t info) {
	Serial.print("WiFi.disconnected\n");

	if (Network::SSID == "" || Network::PASSWORD == "") {
		Serial.print("No net credentials.");
		return;
	}

	// Reattempt the connection
	if (Network::remainingAttempts > 0) {
		--Network::remainingAttempts;
		WiFi.begin(Network::SSID, Network::PASSWORD);
	}
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

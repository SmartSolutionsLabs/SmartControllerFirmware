#include "Record.hpp"

MCP23017* Record::MCP = nullptr;
File* Record::file = nullptr;
bool Record::openFile = false;
File* Record::directory = nullptr;

int Record::init(bool primary) {
	if (Record::MCP == nullptr) {
		Wire.begin(5, 4);
		Record::MCP = new MCP23017(0x20);
		bool initialized = Record::MCP->begin(true);
		//setPullup16(0xFF);
		Serial.print(initialized ? "Iniciado\n" : "incapaz de arrancar\n");
		Record::MCP->pinMode16(0b00010000); // 0 = output , 1 = input
	}

	pinMode(CS_CARD_DETECTOR_PIN, INPUT);

	// Make operations over pins according primary or secondary
	if (primary) {
		// 0 as exists, 1 as absense
		if (digitalRead(CS_CARD_DETECTOR_PIN)) {
			return -1;
		}

		pinMode(CS_SECONDARY_PIN, OUTPUT);
		digitalWrite(CS_SECONDARY_PIN, LOW);

		Record::MCP->write16(0x00);

		if (SD.begin(CS_PRIMARY_PIN)) {
			return 0;
		}

		return 1;
	}
	else {
		Serial.print("Reading 16 bits: ");
		Serial.println(Record::MCP->read16());
		if ((Record::MCP->read16() & 16) == 16) {
			return -1;
		}

		pinMode(CS_PRIMARY_PIN, OUTPUT);
		digitalWrite(CS_PRIMARY_PIN, LOW);

		Record::MCP->write16(32);

		if (SD.begin(CS_SECONDARY_PIN)) {
			return 0;
		}

		return 1;
	}
}

bool Record::start(const char* fileName) {
	if (Record::openFile) {
		Serial.println("Ya hay un archivo abierto. Cierra el archivo antes de abrir otro.");
		return false;
	}

	Record::file = new File(SD.open(fileName, FILE_APPEND));
	if (!Record::file || !*Record::file) {
		Serial.println("No se pudo crear o abrir el archivo");
		delete Record::file;
		Record::file = nullptr;
		return false;
	}

	Record::openFile = true;
	Serial.println("Archivo abierto para escritura");
	return true;
}

bool Record::finalize() {
	if (Record::file && *Record::file) {
		Record::file->close();
		delete Record::file;
		Record::file = nullptr;
		Record::openFile = false;
		return true;
	}

	Serial.println("El archivo ya estaba cerrado");
	return false;
}

bool Record::openForRead(const char* fileName) {
	if (Record::file) {
		Serial.println("Ya hay un archivo abierto en lectura.");
		return false;
	}

	Record::file = new File(SD.open(fileName, FILE_READ));
	if (!Record::file || !*Record::file) {
		Serial.println("No se pudo abrir el archivo para lectura.");
		delete Record::file;
		Record::file = nullptr;
		return false;
	}

	Serial.println("Archivo abierto en modo lectura.");
	return true;
}

void Record::closeRead() {
	if (Record::file) {
		Record::file->close();
		delete Record::file;
		Record::file = nullptr;
		Serial.println("Archivo cerrado después de lectura.");
	}
}


void Record::initList(const char* path) {
	if (Record::directory) {
		Record::directory->close();
		delete Record::directory;
	}

	Record::directory = new File(SD.open(path));
	if (!Record::directory || !Record::directory->isDirectory()) {
		Serial.println("Error al abrir el directorio");
		delete Record::directory;
		Record::directory = nullptr;
	}
}

void Record::listNextFile() {
	if (!Record::directory) {
		Serial.println("No hay un directorio abierto");
		return;
	}

	File file = Record::directory->openNextFile();
	if (file) {
		Serial.print(file.name());
		if (file.isDirectory()) {
			Serial.println("/");
		}
		else {
			Serial.print(" - Tamaño: ");
			Serial.println(file.size());
		}
		file.close();
	}
	else {
		Serial.println("No hay más archivos");
		Record::directory->close();
		delete Record::directory;
		Record::directory = nullptr;
	}
}

void Record::end() {
	SD.end();
}

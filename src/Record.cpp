#include "Record.hpp"

File* Record::file = nullptr;
bool Record::openFile = false;
File* Record::directory = nullptr;

bool Record::init(bool primary) {
	pinMode(CS_PRIMARY_PIN, OUTPUT);
	pinMode(CS_SECONDARY_PIN, OUTPUT);

	digitalWrite(CS_PRIMARY_PIN, LOW);
	digitalWrite(CS_SECONDARY_PIN, LOW);

	if (!SD.begin(primary ? CS_PRIMARY_PIN : CS_SECONDARY_PIN)) {
		Serial.println("Error al inicializar la tarjeta SD");
		return false;
	}

	return true;
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

void Record::append(const DataBuffer& data) {
	if (Record::file && *Record::file) {
		Record::file->write((uint8_t*)&data, sizeof(DataBuffer));
		Record::file->flush();
	}
	else {
		Serial.println("El archivo no está abierto");
	}
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

bool Record::readNext(Data& data) {
	if (!Record::file || !*Record::file) {
		Serial.println("No hay un archivo abierto en lectura.");
		return false;
	}

	if (Record::file->read((uint8_t*)&data, sizeof(Data)) == sizeof(Data)) {
		return true;
	}
	else {
		Serial.println("No hay más datos o error en la lectura.");
		Record::closeRead();
		return false;
	}
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

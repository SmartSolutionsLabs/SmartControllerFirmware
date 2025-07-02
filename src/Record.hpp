#ifndef _INC_SMART_RECORD_
#define _INC_SMART_RECORD_

#include <SD.h>
#include <sd_defines.h>
#include <sd_diskio.h>

#include "FS.h"
#include "SD.h"
#include "SPI.h"

#include "Data.hpp"

#define CS_PRIMARY_PIN 5 // Primary SD selector pin
#define CS_SECONDARY_PIN 14 // Secondary SD selector pin

class Record {
	private:
		static File * file;

		/**
		 * A simple flag to indicate that if the file is open it should be closed.
		 */
		static bool openFile;

		static File * directory;

	public:
		/**
		 * Initialization of physical connection.
		 * @param primary as true or secondary as false.
		 */
		static bool init(bool primary = true);

		/**
		 * Create new file.
		 */
		static bool start(const char* fileName);

		/**
		 * Appends data after creating a file.
		 */
		template <typename DataBuffer>
		static void append(const DataBuffer& data) {
			if (file && *file) {
				file->write(reinterpret_cast<const uint8_t*>(&data), sizeof(DataBuffer));
				file->flush();
			}
			else {
				Serial.println("El archivo no está abierto");
			}
		}

		/**
		 * Close to safely save the file.
		 */
		static bool finalize();

		/**
		 * Open file for reading.
		 */
		static bool openForRead(const char* fileName);

		/**
		 * Read and fill the next Data structure.
		 */
		static bool readNext(Data& data);

		/**
		 * Close file after reading.
		 */
		static void closeRead();

		static void initList(const char* ruta);

		static void listNextFile();
};

#endif

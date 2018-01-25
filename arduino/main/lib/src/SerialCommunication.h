#ifndef SerialCommunication_h
#define SerialCommunication_h

#include <Arduino.h>
#include "MotorController.h"
#include "ServoController.h"
#include "UltraSoundReader.h"

class SerialCommunication {
	public:
		SerialCommunication(MotorController * mCtrl, ServoController * sCtrl, UltraSoundReader * usReader)
			: mc(mCtrl), sc(sCtrl), ur(usReader){}
		int readBuffer(byte * buffer, int bufferSize);
		byte validatePackage(byte * Package, int packageByteSize);
		void processPackage(byte * Package);
		void sendPackage(byte command, byte dataSize, byte * packageData);
		void sendErrorPackage(byte errorCode);

	private:
		MotorController * mc;
		ServoController * sc;
		UltraSoundReader * ur;
		byte calculateChecksum(byte header, byte command, byte dataSize, int packageByteSize);
};

#endif

#include "SerialCommunication.h"

// Package structure definitions
#define PACKAGE_HEADER		0xCA	// Jeff da CA!
#define PACKAGE_EOL			0x0A	// \n
#define PACKAGE_DATA_MAX	4


// GET and SET commands
#define GET_SPEED 			0
#define GET_ANGLE 			1
#define GET_SPEEDANGLE 		2
#define GET_ULTRAREADER 	3

#define SET_SPEED 			100
#define SET_ANGLE 			101
#define SET_SPEEDANGLE 		102

#define GET_STATUS 			200
#define ACK_ERROR			254
#define ACK_OK				255


// Error codes
#define ERROR_PKG_SIZE		1		// Validation: Package too small
#define ERROR_PKG_HEADER	2		// Validation: Invalid package header
#define ERROR_PKG_CHKSUM	3		// Validation: Invalid checksum
#define ERROR_UNKN_CMD		11		// Package content: Undefined command
#define ERROR_DATA_SIZE		12		// Package content: Invalid data size for the current command


char angle_tmp = 0;
byte ultrasoundDistance=10;


int SerialCommunication::readBuffer(byte * buffer, int bufferSize){
	return Serial.readBytesUntil(PACKAGE_EOL, buffer, bufferSize);
}

byte SerialCommunication::calculateChecksum(byte header, byte command, byte dataSize, int packageByteSize){
	return (header+command+dataSize+packageByteSize) % 255;
}

void SerialCommunication::sendPackage(byte command, byte dataSize = 0, byte * packageData = NULL){
	byte responsePackage[5+dataSize];

	responsePackage[0] = PACKAGE_HEADER;
	responsePackage[1] = command;
	responsePackage[2] = dataSize;
	responsePackage[3+dataSize] = calculateChecksum(PACKAGE_HEADER,command,dataSize,4+dataSize);
	responsePackage[4+dataSize] = PACKAGE_EOL;

	if (dataSize>0) {
		for (int i = 0; i < dataSize; ++i) {
			responsePackage[i+3] = packageData[i];
		}
	}

	Serial.write(responsePackage, 5+dataSize);
}

void SerialCommunication::sendErrorPackage(byte errorCode){
	byte errorMsg[1] = {errorCode};
	sendPackage(ACK_ERROR, 1, errorMsg);
}

void SerialCommunication::processPackage(byte * Package){
	byte command = Package[1];
	byte dataSize = Package[2];
	byte inputData[dataSize];
	byte outputData[PACKAGE_DATA_MAX];

	if (dataSize>0) {
		for (int i = 0; i < dataSize; ++i) {
			inputData[i] = Package[i+3];
		}
	}

	// ENTER COMMAND DEFINITIONS HERE
	switch (command) {
		// GET PACKAGES
		case GET_SPEED: // Get speed
			outputData[0] = (byte)mc->get_speed();
			sendPackage(command, 1, outputData);
			break;

		case GET_ANGLE:
			outputData[0] = (byte)angle_tmp;
			sendPackage(command, 1, outputData);
			break;

		case GET_SPEEDANGLE:
			outputData[0] = (byte)mc->get_speed();
			outputData[1] = (byte)angle_tmp;
			sendPackage(command, 2, outputData);
			break;

		case GET_ULTRAREADER:
			outputData[0] = ultrasoundDistance;
			outputData[1] = ur->has_lock();
			sendPackage(command, 2, outputData);
			break;

		case GET_STATUS:
			outputData[0] = (byte)mc->get_speed();
			outputData[1] = (byte)angle_tmp;
			outputData[2] = ultrasoundDistance;
			outputData[3] = ur->has_lock();
			sendPackage(command, 4, outputData);
			break;


		// SET PACKAGES
		case SET_SPEED:
			if (dataSize==1) {
				// speed = (char)inputData[0];
				mc->set_speed(inputData[0]);
				sendPackage(ACK_OK);
			}
			else {
				sendErrorPackage(ERROR_DATA_SIZE);
			}
			break;

		case SET_ANGLE:
			if (dataSize==1) {
				angle_tmp = (char)inputData[0];
				sendPackage(ACK_OK);
			}
			else {
				sendErrorPackage(ERROR_DATA_SIZE);
			}
			break;

		case SET_SPEEDANGLE:
			if (dataSize==2) {
				mc->set_speed(inputData[0]);
				angle_tmp = (char)inputData[1];
				sendPackage(ACK_OK);
			}
			else {
				sendErrorPackage(ERROR_DATA_SIZE);
			}
			break;


		// OTHER PACKAGES
		case ACK_OK:
			sendPackage(ACK_OK);
			break;

		default:
			sendErrorPackage(ERROR_UNKN_CMD);
			break;
	}
}



byte SerialCommunication::validatePackage(byte * Package, int packageByteSize){
	byte packageChecksum, calcChecksum, errorCode;

	if (packageByteSize<4) {
		errorCode = ERROR_PKG_SIZE;
	}
	else if (Package[0]!=PACKAGE_HEADER) {
		errorCode = ERROR_PKG_HEADER;
	}
	else {
		packageChecksum = Package[packageByteSize-1];
		calcChecksum = calculateChecksum(Package[0],Package[1],Package[2],packageByteSize);
		if (packageChecksum != calcChecksum){
			errorCode = ERROR_PKG_CHKSUM;
		}
		else {
			errorCode = 0;
		}
	}

	return errorCode;
}

#include "SerialCommunication.h"

// Package structure definitions
#define PACKAGE_HEADER		0xCA	// Jeff da CA!
#define RETURN_DATA_MAX		4


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


bool new_speed, new_angle;
char speed, angle;
byte ultrasoundDistance=10;
byte hasLock=0;


byte SerialCommunication::calculateChecksum(byte header, byte command, byte dataSize, int packageByteSize){
	return (header+command+dataSize+packageByteSize) % 255;
}

void SerialCommunication::sendPackage(byte command, byte dataSize = 0, byte * packageData = NULL){
	byte responsePackage[4+dataSize];

	responsePackage[0] = PACKAGE_HEADER;
	responsePackage[1] = command;
	responsePackage[2] = dataSize;
	responsePackage[3+dataSize] = calculateChecksum(PACKAGE_HEADER,command,dataSize,4+dataSize);

	if (dataSize>0) {
		for (int i = 0; i < dataSize; ++i) {
			responsePackage[i+3] = packageData[i];
		}
	}

	for (unsigned int i = 0; i < sizeof(responsePackage); ++i){
		Serial.print(responsePackage[i]);
	}
	Serial.println();
	// Serial.println(responsePackage);
	// std::cout << "Sending response package (" << sizeof(responsePackage) << "): " << responsePackage << std::endl;
}

void SerialCommunication::sendErrorPackage(byte errorCode){
	byte errorMsg[1] = {errorCode};
	sendPackage(ACK_ERROR, 1, errorMsg);
}

void SerialCommunication::processPackage(byte * Package){
	byte command = Package[1];
	byte dataSize = Package[2];
	byte inputData[dataSize];
	byte outputData[RETURN_DATA_MAX];

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
			outputData[0] = (byte)angle;
			sendPackage(command, 1, outputData);
			break;

		case GET_SPEEDANGLE:
			outputData[0] = (byte)mc->get_speed();
			outputData[1] = (byte)angle;
			sendPackage(command, 2, outputData);
			break;

		case GET_ULTRAREADER:
			outputData[0] = ultrasoundDistance;
			outputData[1] = hasLock;
			sendPackage(command, 2, outputData);
			break;

		case GET_STATUS:
			outputData[0] = (byte)mc->get_speed();
			outputData[1] = (byte)angle;
			outputData[2] = ultrasoundDistance;
			outputData[3] = hasLock;
			sendPackage(command, 4, outputData);
			break;


		// SET PACKAGES
		case SET_SPEED:
			if (dataSize==1) {
				speed = (char)inputData[0];
				new_speed = true;
				sendPackage(ACK_OK);
			}
			else {
				sendErrorPackage(ERROR_DATA_SIZE);
			}
			break;

		case SET_ANGLE:
			if (dataSize==1) {
				angle = (char)inputData[0];
				new_angle = true;
				sendPackage(ACK_OK);
			}
			else {
				sendErrorPackage(ERROR_DATA_SIZE);
			}
			break;

		case SET_SPEEDANGLE:
			if (dataSize==2) {
				speed = (char)inputData[0];
				angle = (char)inputData[1];
				new_speed = true;
				new_angle = true;
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

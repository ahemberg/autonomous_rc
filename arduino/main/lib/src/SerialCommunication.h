#ifndef SerialCommunication_h
#define SerialCommunication_h

#include "MotorController.h"
#include "ServoController.h"
#include "UltraSoundReader.h"
#include <Arduino.h>

class SerialCommunication {
public:
  SerialCommunication(MotorController *mCtrl, ServoController *sCtrl,
                      UltraSoundReader *usReader)
      : _mc(mCtrl), _sc(sCtrl), _ur(usReader) {}
  int readBuffer(byte *buffer, int bufferSize);
  byte validatePackage(byte *Package, int packageByteSize);
  void parsePackage(byte *Package);
  byte processPackage(byte *Package, int bytesRead);
  void sendPackage(byte command, byte dataSize, byte *packageData);
  void sendErrorPackage(byte errorCode);

private:
  MotorController *_mc;
  ServoController *_sc;
  UltraSoundReader *_ur;
  byte calculateChecksum(byte header, byte command, byte dataSize,
                         int packageByteSize);
};

#endif

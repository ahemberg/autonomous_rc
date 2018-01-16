from time import sleep

from SerialCommunication import SerialCommunication


class Brain:
    # GET and SET commands
    GET_SPEED = 0
    GET_ANGLE = 1
    GET_SPEEDANGLE = 2
    GET_ULTRAREADER = 3

    SET_SPEED = 100
    SET_ANGLE = 101
    SET_SPEEDANGLE = 102

    GET_STATUS = 200

    def __init__(self):
        self.scom = SerialCommunication()

    # SET commands
    def setSpeed(self, speed):
        # TODO: Make sure that speed is unsigned char
        data = bytearray([speed])
        self.scom.sendPackage(self.SET_SPEED, data)
        sleep(0.1)
        self.scom.getResponsePackage()

    # GET commands. Response package format:
    # [header, command, dataSize, data0, ..., dataN, checksum]
    def getSpeed(self):
        self.scom.sendPackage(self.GET_SPEED)
        sleep(0.3)
        respPkg = self.scom.getResponsePackage()
        if len(respPkg) > 0:
            if (respPkg[1] == self.GET_SPEED) & (respPkg[2] == 1):
                # TODO: Convert respPkg[3] to int/signed char
                speed = respPkg[3]
            else:
                speed = -999
                print("GET SPEED: Invalid data size")
        else:
            print("GET SPEED: Error")
            speed = -999

        return speed

import serial
from time import sleep, time

GET_WAIT_TIME = 0.005
SET_WAIT_TIME = 0.05


# High level functions
class Brain:
    GET_SPEED = 0
    GET_ANGLE = 1
    GET_SPEEDANGLE = 2
    GET_ULTRAREADER = 3

    SET_SPEED = 100
    SET_ANGLE = 101
    SET_SPEEDANGLE = 102

    GET_STATUS = 200

    def __init__(self):
        self.spine = SpinalCord()

    # SET commands
    def setSpeed(self, speed):
        speed = speed + 128
        self.spine.sendImpulse(self.SET_SPEED, speed)
        sleep(SET_WAIT_TIME)
        self.spine.readImpulse()

    def setDirection(self, direction):
        direction = direction + 128
        self.spine.sendImpulse(self.SET_ANGLE, direction)
        sleep(SET_WAIT_TIME)
        self.spine.readImpulse()

    def setSpeedDir(self, speed, direction):
        speed = speed + 128
        direction = direction + 128
        self.spine.sendImpulse(self.SET_SPEEDANGLE, [speed, direction])
        sleep(SET_WAIT_TIME)
        self.spine.readImpulse()

    # GET commands
    def getSpeed(self):
        self.spine.sendImpulse(self.GET_SPEED)
        sleep(GET_WAIT_TIME)
        respPkg = self.spine.readImpulse()
        if len(respPkg) > 0:
            if (respPkg[1] == self.GET_SPEED) & (respPkg[2] == 1):
                speed = respPkg[3] - 128
            else:
                speed = None
                print("GET SPEED: Invalid data size")
        else:
            print("GET SPEED: Error")
            speed = None

        return speed

    def getDirection(self):
        t = time()
        self.spine.sendImpulse(self.GET_ANGLE)
        print(time()-t)
        t2 = time()
        # sleep(SET_WAIT_TIME)
        respPkg = self.spine.readImpulse()
        print(time()-t2)
        if len(respPkg) > 0:
            if (respPkg[1] == self.GET_ANGLE) & (respPkg[2] == 1):
                speed = respPkg[3] - 128
            else:
                speed = None
                print("GET ANGLE: Invalid data size")
        else:
            print("GET ANGLE: Error")
            speed = None

        return speed

    def getSpeedDir(self):
        self.spine.sendImpulse(self.GET_SPEEDANGLE)
        sleep(GET_WAIT_TIME)
        respPkg = self.spine.readImpulse()
        if len(respPkg) > 0:
            if (respPkg[1] == self.GET_SPEEDANGLE) & (respPkg[2] == 2):
                speedDir = [respPkg[3] - 128, respPkg[4] - 128]
            else:
                speedDir = None
                print("GET SPEED: Invalid data size")
        else:
            print("GET SPEED: Error")
            speedDir = None

        return speedDir

    def getDistance(self):
        self.spine.sendImpulse(self.GET_ULTRAREADER)
        sleep(GET_WAIT_TIME)
        respPkg = self.spine.readImpulse()
        if len(respPkg) > 0:
            if (respPkg[1] == self.GET_ULTRAREADER) & (respPkg[2] == 5):
                distance = int.from_bytes(respPkg[3:6], byteorder='little')
            else:
                distance = None
                print("GET SPEED: Invalid data size")
        else:
            print("GET SPEED: Error")
            distance = None

        return distance

    def getStatus(self):
        self.spine.sendImpulse(self.GET_STATUS)
        sleep(GET_WAIT_TIME)
        respPkg = self.spine.readImpulse()
        if len(respPkg) > 0:
            if (respPkg[1] == self.GET_STATUS) & (respPkg[2] == 7):
                # [speed, angle, dist_LSB, dist, dist, dist_MSB, has_lock()]
                status = [respPkg[3] - 128, respPkg[4] - 128]
                status.append(int.from_bytes(respPkg[5:8], byteorder='little'))
                status.append(respPkg[9])
            else:
                status = None
                print("GET SPEED: Invalid data size")
        else:
            print("GET SPEED: Error")
            status = None

        return status


# Handles serial communication
class SpinalCord:
    PACKAGE_HEADER = 0xCA   # Jeff da CA!
    PACKAGE_EOL = 0x0A      # End-of-line character (\n)
    ERROR_PKG_SIZE = 1      # Validation: Package too small
    ERROR_PKG_HEADER = 2    # Validation: Invalid package header
    ERROR_PKG_CHKSUM = 3    # Validation: Invalid checksum
    ACK_ERROR = 254
    ACK_OK = 255

    def __init__(self):
        self.ser = serial.Serial('/dev/ttyS0', baudrate=115200, timeout=0.1)
        # print("dbg mode")

    def __countNeurons(self, header, command, dataSize, pkgSize):
        return (header+command+dataSize+pkgSize) % 255

    def __createImpulse(self, command, data):
        # Make sure that data is a list
        if not isinstance(data, (list,)):
            data = [data]

        # Build package as a list [header, command, dataSize, data, chksum]
        dataSize = len(data)
        packageDec = [self.PACKAGE_HEADER, command, dataSize]
        packageDec.extend(data)
        packageDec.append(self.__countNeurons(self.PACKAGE_HEADER, command,
                                              dataSize, dataSize+4))

        # Convert list to list of bytes
        package = bytearray(packageDec)

        return package

    def sendImpulse(self, command, data=[]):
        package = self.__createImpulse(command, data)
        package.append(self.PACKAGE_EOL)
        # print(":: Sending impulse:")
        # print(repr(package))
        self.ser.write(package)
        self.ser.flush()

    def readImpulse(self):
        # Read serial port as string
        package = self.ser.readline()[:-1]

        # Validate package
        validPkg = self.validateImpulse(package)
        if validPkg == 0:
            if package[1] == self.ACK_OK:
                print("SUCCESS: Settings updated")
                package = []
            elif package[1] == self.ACK_ERROR:
                print("ERROR: Received error package #{}".format(package[2]))
                package = []
            else:
                print("SUCCESS: Received requested data")
        else:
            print("ERROR. Broken response #{}".format(validPkg))
            package = []

        return package

    def validateImpulse(self, package):
        pkgSize = len(package)
        if pkgSize < 4:
            errorCode = self.ERROR_PKG_SIZE
        elif package[0] != self.PACKAGE_HEADER:
            errorCode = self.ERROR_PKG_HEADER
        else:
            chksum = self.__countNeurons(self.PACKAGE_HEADER, package[1],
                                         package[2], pkgSize)

            if chksum != package[pkgSize-1]:
                errorCode = self.ERROR_PKG_CHKSUM
            else:
                errorCode = 0

        return errorCode

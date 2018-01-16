import serial


class SerialCommunication:
    PACKAGE_HEADER = 0xCA   # Jeff da CA!
    PACKAGE_EOL = 0x0A
    ERROR_PKG_SIZE = 1      # Validation: Package too small
    ERROR_PKG_HEADER = 2    # Validation: Invalid package header
    ERROR_PKG_CHKSUM = 3    # Validation: Invalid checksum
    ACK_ERROR = 254
    ACK_OK = 255

    def __init__(self):
        self.ser = serial.Serial('/dev/ttyS0', 9600)

    def __calculateChecksum(header, command, dataSize, pkgSize):
        return (header+command+dataSize+pkgSize) % 255

    def __createPackage(self, command, data):
        dataSize = len(data)
        package = bytearray(4+dataSize)
        package[0] = self.PACKAGE_HEADER
        package[1] = command
        package[2] = dataSize
        package[3+dataSize] = self.__calculateChecksum(self.PACKAGE_HEADER,
                                                       command, dataSize,
                                                       dataSize+4)
        package[4+dataSize] = self.PACKAGE_EOL

        if dataSize > 0:
            for i in range(0, dataSize):
                package[3+i] = data[i]

        return package

    def sendPackage(self, command, data=[]):
        package = self.__createPackage(command, data)
        self.ser.write(package)

    def getResponsePackage(self):
        package = self.ser.readline()
        validPkg = self.validatePackage(package)
        if validPkg == 0:
            if package[1] == self.ACK_OK:
                print("SET: Success")
                package = []
            elif package[1] == self.ACK_ERROR:
                print("COMMAND FAILED: " + package[2])
                package = []
        else:
            print("INVALID RESPONSE PACKAGE: " + validPkg)
            package = []

        return package

    def validatePackage(self, package):
        pkgSize = len(package)
        if pkgSize < 4:
            errorCode = self.ERROR_PKG_SIZE
        elif package[0] != self.PACKAGE_HEADER:
            errorCode = self.ERROR_PKG_HEADER
        else:
            chksum = self.__calculateChecksum(self.PACKAGE_HEADER, package[1],
                                              package[2], pkgSize)
            if chksum != package[pkgSize-1]:
                errorCode = self.ERROR_PKG_CHKSUM
            else:
                errorCode = 0

        return errorCode

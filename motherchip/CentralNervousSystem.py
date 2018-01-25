import serial
from time import sleep, time

GET_WAIT_TIME = 0.0
SET_WAIT_TIME = 0.0

PACKAGE_HEADER = 0xCA  # Jeff da CA!
PACKAGE_EOL = 0x0A  # End-of-line character (\n)

GET_SPEED = 0
GET_ANGLE = 1
GET_SPEEDANGLE = 2
GET_ULTRAREADER = 3

SET_SPEED = 100
SET_ANGLE = 101
SET_SPEEDANGLE = 102

GET_STATUS = 200
ACK_ERROR = 254
ACK_OK = 255

ERROR_PKG_SIZE = 1  # Validation: Package too small
ERROR_PKG_HEADER = 2  # Validation: Invalid package header
ERROR_PKG_CHKSUM = 3  # Validation: Invalid checksum


# High level functions
class Brain:
    def __init__(self):
        self.spine = SpinalCord()

    # SET commands
    def set_speed(self, speed):
        speed = speed + 128
        self.spine.send_impulse(SET_SPEED, speed)
        self.spine.read_impulse()

    def set_direction(self, direction):
        direction = direction + 128
        self.spine.send_impulse(SET_ANGLE, direction)
        self.spine.read_impulse()

    def set_speed_dir(self, speed, direction):
        speed = speed + 128
        direction = direction + 128
        self.spine.send_impulse(SET_SPEEDANGLE, [speed, direction])
        self.spine.read_impulse()

    # GET commands
    def get_speed(self):
        self.spine.send_impulse(GET_SPEED)
        sleep(GET_WAIT_TIME)
        resp_pkg = self.spine.read_impulse()
        if len(resp_pkg) > 0:
            if (resp_pkg[1] == GET_SPEED) & (resp_pkg[2] == 1):
                speed = resp_pkg[3] - 128
            else:
                speed = None
                print("GET SPEED: Invalid data size")
        else:
            print("GET SPEED: Error")
            speed = None

        return speed

    def get_direction(self):
        self.spine.send_impulse(GET_ANGLE)
        sleep(GET_WAIT_TIME)
        resp_pkg = self.spine.read_impulse()
        if len(resp_pkg) > 0:
            if (resp_pkg[1] == GET_ANGLE) & (resp_pkg[2] == 1):
                direction = resp_pkg[3] - 128
            else:
                direction = None
                print("GET DIRECTION: Invalid data size")
        else:
            print("GET DIRECTION: Error")
            direction = None

        return direction

    def get_speed_dir(self):
        speed_dir = {'speed': None, 'direction': None}

        self.spine.send_impulse(GET_SPEEDANGLE)
        sleep(GET_WAIT_TIME)
        resp_pkg = self.spine.read_impulse()
        if len(resp_pkg) > 0:
            if (resp_pkg[1] == GET_SPEEDANGLE) & (resp_pkg[2] == 2):
                speed_dir['speed'] = resp_pkg[3] - 128
                speed_dir['direction'] = resp_pkg[4] - 128
            else:
                print("GET SPEED&DIR: Invalid data size")
        else:
            print("GET SPEED&DIR: Error")

        return speed_dir

    def get_distance(self):
        us_status = {'distance': None, 'lock': None}

        self.spine.send_impulse(GET_ULTRAREADER)
        sleep(GET_WAIT_TIME)
        resp_pkg = self.spine.read_impulse()
        if len(resp_pkg) > 0:
            if (resp_pkg[1] == GET_ULTRAREADER) & (resp_pkg[2] == 5):
                us_status['distance'] = int.from_bytes(resp_pkg[3:6], byteorder='little')
                us_status['lock'] = resp_pkg[7]
            else:
                print("GET DISTANCE: Invalid data size")
        else:
            print("GET DISTANCE: Error")

        return us_status

    def get_status(self):
        status = {'speed': None, 'distance': None, 'direction': None, 'lock': None}

        self.spine.send_impulse(GET_STATUS)
        sleep(GET_WAIT_TIME)
        resp_pkg = self.spine.read_impulse()
        if len(resp_pkg) > 0:
            if (resp_pkg[1] == GET_STATUS) & (resp_pkg[2] == 7):
                # [speed, angle, dist_LSB, dist, dist, dist_MSB, has_lock()]
                status['speed'] = resp_pkg[3] - 128
                status['direction'] = resp_pkg[4] - 128
                status['distance'] = int.from_bytes(resp_pkg[5:8], byteorder='little')
                status['lock'] = resp_pkg[9]
            else:
                print("GET STATUS: Invalid data size")
        else:
            print("GET STATUS: Error")

        return status


# Handles serial communication
class SpinalCord:
    def __init__(self):
        self.ser = serial.Serial('/dev/ttyS0', baudrate=115200, timeout=0.1)
        # print("dbg mode")

    @staticmethod
    def __count_neurons(header, command, data_size, pkg_size):
        return (header + command + data_size + pkg_size) % 255

    def __create_impulse(self, command, data):
        # Make sure that data is a list
        if not isinstance(data, (list,)):
            data = [data]

        # Build package as a list [header, command, data_size, data, chksum]
        data_size = len(data)
        package_dec = [PACKAGE_HEADER, command, data_size]
        package_dec.extend(data)
        package_dec.append(self.__count_neurons(PACKAGE_HEADER, command,
                                                data_size, data_size+4))

        # Convert list to list of bytes
        package = bytearray(package_dec)

        return package

    def send_impulse(self, command, data=[]):
        package = self.__create_impulse(command, data)
        package.append(PACKAGE_EOL)
        self.ser.write(package)

    def read_impulse(self):
        # Read serial port as string
        package = self.ser.readline()[:-1]

        # Validate package
        valid_pkg = self.validate_impulse(package)
        if valid_pkg == 0:
            if package[1] == ACK_OK:
                print("SUCCESS: Settings updated")
                package = []
            elif package[1] == ACK_ERROR:
                print("ERROR: Received error package #{}".format(package[2]))
                package = []
            else:
                print("SUCCESS: Received requested data")
        else:
            print("ERROR. Broken response #{}".format(valid_pkg))
            package = []

        return package

    def validate_impulse(self, package):
        pkg_size = len(package)
        if pkg_size < 4:
            error_code = ERROR_PKG_SIZE
        elif package[0] != PACKAGE_HEADER:
            error_code = ERROR_PKG_HEADER
        else:
            chksum = self.__count_neurons(PACKAGE_HEADER, package[1],
                                          package[2], pkg_size)

            if chksum != package[pkg_size-1]:
                error_code = ERROR_PKG_CHKSUM
            else:
                error_code = 0

        return error_code

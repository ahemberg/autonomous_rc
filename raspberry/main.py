from time import sleep

import serial


class Brain:

    def __init__(self):
        self.ser = serial.Serial('/dev/ttyS0', 9600)

    def send_command(self, command):
        self.ser.write(command)

    def forward(self):
        self.send_command(b'w')

    def backward(self):
        self.send_command(b's')

    def stop(self):
        self.send_command(b'q')

    def right(self):
        self.send_command(b'd')

    def left(self):
        self.send_command(b'a')

    def straight(self):
        self.send_command(b'x')

    def take_picture(self):
        self.send_command(b'p')

    def read_status(self):
        return self.ser.readline()


def main():
    brain = Brain()
    brain.forward()
    print(brain.read_status())
    sleep(1)
    brain.stop()
    sleep(1)
    brain.backward()
    sleep(1)
    brain.right()
    sleep(1)
    brain.forward()
    sleep(0.5)
    brain.left()
    sleep(0.5)
    brain.stop()
    sleep(1)
    brain.straight()


if __name__ == '__main__':
    main()

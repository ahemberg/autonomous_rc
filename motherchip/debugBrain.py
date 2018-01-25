from time import sleep
from CentralNervousSystem import Brain


def main():
    # sc = SpinalCord()
    brain = Brain()

    # tmp resp. package for readImpulse()
    # tmp = bytearray.fromhex("ca ff 00 ce 0a").decode("latin-1")[:-1]
    # sc.readImpulse()
    # for i in range(20,120,20):
    #    brain.setDirection(i)
    #    print(brain.getDirection())
    #    sleep(1)

    # brain.setDirection(-100)
    # for i in range(100):
    #    print(brain.getDirection())
    brain.set_direction(0)
    while 1:
        brain.set_speed_dir(100, -100)
        sleep(1)
        brain.set_speed_dir(0, 0)
        sleep(1)
        brain.set_speed_dir(-100, 100)
        sleep(1)
        brain.set_speed_dir(0, 0)
        sleep(1)
    # print(brain.set_speed(0))
    # sleep(20)
    # print(brain.set_speed(0))


if __name__ == "__main__":
    main()

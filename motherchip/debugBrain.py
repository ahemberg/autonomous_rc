# from CentralNervousSystem import SpinalCord
from CentralNervousSystem import Brain


def main():
    # sc = SpinalCord()
    brain = Brain()

    # tmp resp. package for readImpulse()
    # tmp = bytearray.fromhex("ca ff 00 ce 0a").decode("latin-1")[:-1]
    # sc.readImpulse()
    brain.setSpeed(100)


if __name__ == "__main__":
    main()

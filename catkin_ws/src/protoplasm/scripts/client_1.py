#!/usr/bin/env python3

import rospy
from protoplasm.srv import GetDirection


def get_direction_client():
    rospy.wait_for_service('get_direction')
    try:
        get_direction = rospy.ServiceProxy('get_direction', GetDirection)
        return (get_direction.motor_percent, get_direction.angle, get_direction.measured_speed)
    except:
        print("Service call failed")

if __name__ == '__main__':
    print("Requesting status from board")
    print("Motor percent: %s, Angle: %s, Speed: %s", get_direction_client())
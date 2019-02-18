#!/usr/bin/env python3

from CentralNervousSystem import Brain
from protoplasm.srv import GetDirection
from ptotoplasm.msg import Direction

import rospy

def get_direction(req):
    return Direction(50, 0, 10)

def get_status_server():
    rospy.init_node('get_direction_server')
    s = rospy.Service('get_direction', GetDirection, get_direction)

if __name__ == '__main__':
    get_status_server()
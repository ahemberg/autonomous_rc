#!/usr/bin/env python3

import rospy
from std_msgs.msg import String
from CentralNervousSystem import Brain
from time import sleep

brain = Brain()

def callback(data):
    rospy.loginfo(rospy.get_caller_id() + 'Message: %s', data.data)
    #brain.set_direction(data.data)
    
    if data.data == 'w':
        brain.set_speed_dir(100, 0)        
    elif data.data == 's':
        brain.set_speed_dir(-100, 0)        
    elif data.data == 'a':
        brain.set_direction(-100)        
    elif data.data == 'd':
        brain.set_direction(100)        
    else:
        brain.set_speed_dir(0, 0)        


def listener():

    # In ROS, nodes are uniquely named. If two nodes with the same
    # name are launched, the previous one is kicked off. The
    # anonymous=True flag means that rospy will choose a unique
    # name for our 'listener' node so that multiple listeners can
    # run simultaneously.
    rospy.init_node('listener', anonymous=True)

    rospy.Subscriber('chatter', String, callback)

    # spin() simply keeps python from exiting until this node is stopped
    rospy.spin()
    

if __name__ == '__main__':
    listener()

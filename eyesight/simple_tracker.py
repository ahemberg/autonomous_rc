import cv2
import sys
import imutils
import numpy as np
from collections import deque

lemoncapture = [(17, 153, 103), (41, 194, 232)]
pencap = [(170, 142, 124), (179, 189, 197)]

video = cv2.VideoCapture(0)

if not video.isOpened():
    print("Could not open video")
    sys.exit(1)

greenLower = pencap[0]
greenUpper = pencap[1]
pts = deque(maxlen=64)

ok, frame = video.read()

if not ok:
    print("Could not open video")

while True:
    ok, frame = video.read()

    if not ok:
        break

    #frame = imutils.resize(frame, width=600)
    hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)

    mask = cv2.inRange(hsv, greenLower, greenUpper)
    mask = cv2.erode(mask, None, iterations=2)
    mask = cv2.dilate(mask, None, iterations=2)

    cnts = cv2.findContours(mask.copy(), cv2.RETR_EXTERNAL,
                            cv2.CHAIN_APPROX_SIMPLE)[-2]
    center = None

    if len(cnts) > 0:
        # find the largest contour in the mask, then use
        # it to compute the minimum enclosing circle and
        # centroid
        c = max(cnts, key=cv2.contourArea)
        ((x, y), radius) = cv2.minEnclosingCircle(c)
        M = cv2.moments(c)
        center = (int(M["m10"] / M["m00"]), int(M["m01"] / M["m00"]))

        # only proceed if the radius meets a minimum size
        if radius > 10:
            # draw the circle and centroid on the frame,
            # then update the list of tracked points
            cv2.circle(frame, (int(x), int(y)), int(radius),
                       (0, 255, 255), 2)
            cv2.circle(frame, center, 5, (0, 0, 255), -1)

    pts.appendleft(center)

    # loop over the set of tracked points
    for i in range(1, len(pts)):
        # if either of the tracked points are None, ignore
        # them
        if pts[i - 1] is None or pts[i] is None:
            continue

        # otherwise, compute the thickness of the line and
        # draw the connecting lines
        thickness = int(np.sqrt(64 / float(i + 1)) * 2.5)
        cv2.line(frame, pts[i - 1], pts[i], (0, 0, 255), thickness)

    objstr = "No object found!"
    if center:
        objstr = "Object at %s, %s" % center

    font = cv2.FONT_HERSHEY_SIMPLEX
    cv2.putText(frame, objstr, (20, 400), font, 0.5, (255, 255, 255), 2, cv2.LINE_AA)

    cv2.imshow('Tracker Demo', frame)
    cv2.imshow('Mask', mask)

    key = cv2.waitKey(1) & 0xFF

    # if the 'q' key is pressed, stop the loop
    if key == ord("q"):
        break

import cv2
import sys
import imutils


pencap_hsv = [(146, 125, 134), (179, 255, 255)]
IMAGE_WIDTH = 600


class ColorLocator:
    def __init__(self):
        self.video = cv2.VideoCapture(0)

        if not self.video.isOpened():
            print("Could not open video")
            sys.exit(1)

        self.greenLower = pencap_hsv[0]
        self.greenUpper = pencap_hsv[1]

    def locate(self):
        ok, frame = self.video.read()

        if not ok:
            print("Could not open video")

        ok, frame = self.video.read()

        if not ok:
            return None

        frame = imutils.resize(frame, width=IMAGE_WIDTH)
        hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)

        mask = cv2.inRange(hsv, self.greenLower, self.greenUpper)
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

        return center

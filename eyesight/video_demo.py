import cv2
import sys
video = cv2.VideoCapture(0)

if not video.isOpened():
    print("Could not open video")
    sys.exit(1)

ok, frame = video.read()

if not ok:
    print("Could not open video")

while True:
    cv2.imshow("Stream Demo", frame)
    ok, frame = video.read()
    if not ok:
        break

    if cv2.waitKey(1) == 27:
        break

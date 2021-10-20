import cv2
import numpy as np
import serial
import time
import sys
import imutils

defaultSpeed = 50
windowCenter = 320
centerBuffer = 10
pwmBound = float(50)
cameraBound = float(320)
kp = pwmBound / cameraBound
leftBound = int(windowCenter - centerBuffer)
rightBound = int(windowCenter + centerBuffer)
error = 0
ballPixel = 0

arduino = serial.Serial('/dev/ttyACM0', 9600)
if(arduino.isOpen()):
    #arduino.open()
    time.sleep(2)
    print("Connection to arduino...")

ballPixel = 0

cap = cv2.VideoCapture(0);
cap.set(3,640)
cap.set(4,480)
cap.set(10,5)


while True:
    _, frame = cap.read()

    hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)

    l_y = np.array([110, 50, 50])
    u_y = np.array([130, 255, 255])

    mask = cv2.inRange(hsv, l_y, u_y)
    mask= cv2.erode(mask,None,iterations=2)
    mask= cv2.dilate(mask,None,iterations=2)
    
    res = cv2.bitwise_and(frame, frame, mask=mask)
    
    gray = cv2.cvtColor(res, cv2.COLOR_BGR2GRAY)
    
    circles = cv2.HoughCircles(gray, cv2.HOUGH_GRADIENT, 3, 500, minRadius = 10, maxRadius = 200, param1 = 100,  param2 = 60)
    
    ballPixel = 0
    
    if circles is not None:
		circles = np.round(circles[0, :]).astype("int")
		for (x, y, radius) in circles:

			cv2.circle(res, (x, y), radius, (0, 255, 0), 4)
			#cv2.rectangle(output, (x - 5, y - 5), (x + 5, y + 5), (0, 128, 255), -1)	
		
			if radius > 10:	
				ballPixel = x
			else:
				ballPixel = 0
    
    #if ballPixel == 0:
	#arduino.write("s".encode())
    #else:
	#arduino.write("f".encode())
	
    if ballPixel == 0:
	#print "no ball"
	error = 0
	updatePwm=[str(0),str(0)]
	updatePwm=','.join(updatePwm)
	updatePwm+="\n"
	print updatePwm
	arduino.write(updatePwm.encode('utf-8'))
    elif (ballPixel < leftBound) or (ballPixel > rightBound):
	error = windowCenter - ballPixel
	pwmOut = abs(error * kp) 
	#print ballPixel
	turnPwm = int(pwmOut + defaultSpeed)
	if  ballPixel < (leftBound):
	    #print "left side"
	    if radius > 50 and ballPixel < 110:
		#print ballPixel
		updatePwm=[str(defaultSpeed),str(20)]
		updatePwm=','.join(updatePwm)
		updatePwm+="\n"
		print updatePwm
		arduino.write(updatePwm.encode('utf-8'))
	    else:
		updatePwm=[str(turnPwm),str(defaultSpeed)]
		updatePwm=','.join(updatePwm)
		updatePwm+="\n"
		print updatePwm
		arduino.write(updatePwm.encode('utf-8'))
	elif ballPixel > (rightBound):
	    #print "right side"
	    if radius > 50 and ballPixel > 540:
		#print ballPixel
		updatePwm=[str(20),str(defaultSpeed)]
		updatePwm=','.join(updatePwm)
		updatePwm+="\n"
		print updatePwm
		arduino.write(updatePwm.encode('utf-8'))
	    else:
		updatePwm=[str(defaultSpeed),str(turnPwm)]
		updatePwm=','.join(updatePwm)
		updatePwm+="\n"
		print updatePwm
		arduino.write(updatePwm.encode('utf-8'))
    else:	
	#print "middle"
	if (radius < 10):
	    updatePwm=[str(defaultSpeed),str(defaultSpeed)]
	    updatePwm=','.join(updatePwm)
	    updatePwm+="\n"
	    print updatePwm
	    arduino.write(updatePwm.encode('utf-8'))
	else:
	    updatePwm=[str(0),str(0)]
	    updatePwm=','.join(updatePwm)
	    updatePwm+="\n"
	    print updatePwm
	    arduino.write(updatePwm.encode('utf-8'))

    
    cv2.imshow("Live Stream", frame)
    cv2.imshow("mask", mask)
    cv2.imshow("res", res)

    key = cv2.waitKey(1)
	
    if key == 27:
        break    

cap.release()
cv2.destroyAllWindows()

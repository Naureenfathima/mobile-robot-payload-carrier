#!/usr/bin/env python
# -*- coding: utf-8 -*-
# lsusb to check device name
#dmesg | grep "tty" to find port name

import serial,time


if __name__ == '__main__':
    
    print('Running. Press CTRL-C to exit.')
    with serial.Serial("/dev/ttyACM0", 9600, timeout=1) as arduino:
        time.sleep(0.1) #wait for serial to open
        if arduino.isOpen():
            print("{} connected!".format(arduino.port))
            try:
                while True:
                    print("Forward-'F' \n Backward- 'B' \n Right -'R' \n Left - 'L' \n")
                    f0 = open("/var/www/html/team13robo/direction/dir.txt", "r+")
                    str0 = f0.read(5)
                    f0.close()
                    cmd=str0.strip()
                    #cmd=input("Enter direction : ")
                    cmd_options=["W","w","A","a","S","s","D","d","Q","q"]
                    if (cmd in cmd_options):
                        arduino.write(cmd.encode())
                        #time.sleep(0.1) #wait for arduino to answer
                        while arduino.inWaiting()==0: pass
                        if  arduino.inWaiting()>0:
                            answer=arduino.readline()
                            print(answer)
                            arduino.flushInput() #remove data after reading
                    else:
                        print("Wrong input")
            except KeyboardInterrupt:
                print("KeyboardInterrupt has been caught.")

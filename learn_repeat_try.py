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
                path=[]
                cmd_options=["b","B","F","f","l","L","R","r","S","s"]
                temp_cmd=""
                while True:
                    print ("Learn - 'L' \nRepeat - 'R' \n")
                    t=raw_input("Enter mode:")
                    if (t == 'L'):
                        ch="y"
                        new_path=[]
                        while True:
                            if (ch=="y" or ch == "Y"):
                                print("Forward-'F' \nBackward- 'B' \nRight -'R' \nLeft - 'L' \nStop - 'S' \n")
                                cmd=raw_input("Enter direction : ")
                                temp_cmd=cmd
                                if (cmd in cmd_options):
                                    arduino.write(cmd.encode())
                                    new_path.append(temp_cmd)
                                    #time.sleep(0.1) #wait for arduino to answer
                                    while arduino.inWaiting()==0: pass
                                    if  arduino.inWaiting()>0:
                                        answer=arduino.readline()
                                        print(answer)
                                        arduino.flushInput() #remove data after reading
                                else:
                                    print("Wrong input")
                            elif (ch=="n"):
                                name=raw_input("Enter path name to store:")
                                new_path.append(name)
                                path.append(new_path)
                                break
                            ch=raw_input("Do you want to continue? (y/n) ")
                    elif(t == 'R'):
                        if path != []:
                            for i in range(0,len(path)):
                                temp=path[i]
                                mssg=str(i+1)+". "+temp[len(temp)-1]
                                print (mssg)
                            chi=int(input("Enter the path number you wish to repeat:"))
                            if chi < 0 or chi > len(path):
                                print ("Path number chosen doesn't exist!")
                            else:
                                rep=path[chi-1]
                                print ("Repeat Mode")
                                for i in range(0, len(rep)):
                                    if (rep[i] in cmd_options):
                                        arduino.write(rep[i].encode())
                                        time.sleep(0.1) #wait for arduino to answer
                                        while arduino.inWaiting()==0: pass
                                        if  arduino.inWaiting()>0:
                                            answer=arduino.readline()
                                            print(answer)
                                            arduino.flushInput() #remove data after reading
                        else:
                            print("No path learnt!")
                    else:
                        print ("Wrong input")
                                
            except KeyboardInterrupt:
                print("KeyboardInterrupt has been caught.")

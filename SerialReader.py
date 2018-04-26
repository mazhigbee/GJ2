#!/usr/bin/python

import serial
import datetime
import thread


ph = []
turb = []

#this saves a string to is proper list
def saveString(s):
	if s.startswith("$"): #we have a valid string to read!
		key,value = s.split(":")
		
		if key =="$ph":
			#add to ph list
			ph.append(value.rstrip())
		elif key =="$turb":
			#add to turb
			turb.append(value.rstrip())
			
#write avg's to the database...			
def writeToDB():
	
	






#########################################################################
##END FUNCTIONS														 ####
#########################################################################



ser = serial.Serial('/dev/ttyACM0',9600,8,'N',1,timeout=5)


while True:
	now = datetime.datetime.now()
	if ser.in_waiting > 0:
		curLine = ser.readline();
		#print(curLine)
		saveString(curLine);
		print(turb)	 
	if now.minute % 5 == 0: #we are on a time that is divisible by 5 lets write to the db
		print("Writing to the database  " +"Time: " + now.hour + ":" + now.minute)
		writeToDB()
		#write to database on a different thread 
		#copy data structures and pass to function
		#clear data
		#open thread with copies
		
		
		
		
		
		
		
		
		

			
			
		
		
		
		
	

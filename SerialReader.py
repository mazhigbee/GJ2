#!/usr/bin/python

import serial
import datetime
import thread
import os
import glob
import sys
import re
import time
import subprocess
import mysql


#database creds
config = {
  'user': 'ginger',
  'password': 'ginger',
  'host': '127.0.0.1',
  'database': 'gj2',
  'raise_on_warnings': True,
}


ph = []
turb = []
temp = []
wind = []
dissolved_o = []
lat = 0
longitude = 0
battery = 100
dblock = False 

ser = serial.Serial('/dev/ttyACM0',9600,8,'N',1,timeout=5)

#init modprobe for therm
os.system('modprobe w1-gpio')
os.system('modprobe w1-therm')
 
base_dir = '/sys/bus/w1/devices/'
device_folder = glob.glob(base_dir + '28*')[0]
device_file = device_folder + '/w1_slave'

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
		elif key =="$wind":
			wind.append(value.rstrip())
			
def read_temp_raw():
	catdata = subprocess.Popen(['cat',device_file], 
	stdout=subprocess.PIPE, stderr=subprocess.PIPE)
	out,err = catdata.communicate()
	out_decode = out.decode('utf-8')
	lines = out_decode.split('\n')
	return lines

 
def read_temp():
    lines = read_temp_raw()
    while lines[0].strip()[-3:] != 'YES':
        time.sleep(0.2)
        lines = read_temp_raw()
    equals_pos = lines[1].find('t=')
    if equals_pos != -1:
        temp_string = lines[1][equals_pos+2:]
        temp_c = float(temp_string) / 1000.0
        temp_f = temp_c * 9.0 / 5.0 + 32.0
        #print(temp_f)
        return temp_f#, temp_c
        	
def takeAvg(list):
	avg = sum(list) / float(len(list)
	return avg
			
#write avg's to the database...			
def writeToDB():
	print("Writing to the database  " +"Time: " + str(now.hour) + ":" + str(now.minute))
	
	
	cnx = mysql.connector.connect(**config)
	now = datetime.datetime.now()
	cursor = cnx.cursor()
	query = ("INSERT INTO sensor_data VALUES (%s, %s, %s, %s, %s,%s, %s, %s, %s, %s)")
	data_query = (battery,now,lat,longitude,takeAvg(ph),takeAvg(temp),takeAvg(wind),takeAvg(turb),takeAvg(dissolved_o))
	cursor.execute(query,data_query)

	# Make sure data is committed to the database
	cnx.commit()
	#after we commit we should reset the lists
	ph = []
	turb = []
	temp = []
	wind = []
	dissolved_o = []
	cursor.close()     
	cnx.close()
	print("Closing connection to DB")






#########################################################################
##END FUNCTIONS														 ####
#########################################################################






while True:
	now = datetime.datetime.now()
	if ser.in_waiting > 0:
		curLine = ser.readline();
		print(curLine)
		saveString(curLine);
		temp.append(read_temp())
		#print("temp: " + str(temp[-1:]))	 
		#print("pH: " + str(ph[-1:]))
		#print("turb: " + str(turb[-1:]))
		#print("wind: " + str(wind[-1:]))
		#print(wind)
		

	#we are on a time that is divisible by 5 lets write to the db
	if now.minute % 5 == 0 and dblock == False: 
		dblock = True
		writeToDB()
		#write to database on a different thread 
		#copy data structures and pass to function
		#clear data
		#open thread with copies

	#we must not try and write to the db for the entire minute we care about only do it once
	#this unlocks it when that minute has passed...
	if now.minute % 6 == 0 and dblock == True: 	
		print("unlocking db!")
		dblock = False										
		
		
		
		
		
		
		
		

			
			
		
		
		
		
	

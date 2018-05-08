## Ginger Judge 2.0 
Ginger Judge 2.0 is designed to be a semi-autonomous research vessel. This was a project complete at Endicott College.
## Other repos:
A list of the other contributions to this project can be found here
|Name|link  |
|--|--|
|  PixHawk Stuff| https://github.com/JeffreyThor/GJ2-Pixhawk  |

# SerialReader.py
This script provides the nessasary info to extract data from the sensors over a serial connection to Arduino and then store them in a MySQL database. This also defines the user info for the database which you are welcome to change, but it must match your database info.
# dataBaseCreate.sql
Provides schema and info for setting up the database. 

# sensors.ino
this provides the script to read info from sensors and send it over serial to a RPi3 on the other side. Its important to note that each sensors serial print starts with a $. This is important as SerialReader.py expects it. Also because its a serial stream you need to know when things begin. 

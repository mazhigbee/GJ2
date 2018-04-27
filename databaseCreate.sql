/*file for creating database for sensor storage information
 *Author: Mazlin Higbee
 *Email: mhigb411@mail.endicott.edu
 *
 */



create table sensor_data (
	id int not null auto_increment,
	battery_percent float not null,
	sample_time datetime not null,
	lat int not null,
	latitude int not null,
	longitude int not null,
	ph float not null,
	temperture float not null,
	wind_speed float not null,
	turbitity float not null,
	dissolved_o float not null,
	notes varchar(2500),
	PRIMARY KEY (id)
);


/*Example insert
 *
 */






/*
  # Author : Mazlin Higbee
  # Ver    : 1.0
  # Purpose: script to read array of sensors data and return that info over serial monitor
  #IF YOU DO A GOOGLE SEARCH FOR THE SENSOR YOUR USING YOU CAN FIND THE CODE!!!
  #Thats what i did, not much orignal stuff here.
*/
#define phPin A0            //pH meter Analog output to Arduino Analog Input 0
#define turbPin A1          //turbitity output analog on pin 1
#define windPin A2          
#define Offset 0.00            //deviation compensate
#define LED 13
#define samplingInterval 500
#define printInterval 500
#define ArrayLenth  40    //times of collection





int pHArray[ArrayLenth];   //Store the average value of the sensor feedback
int pHArrayIndex = 0;


void setup()
{
  pinMode(LED, OUTPUT);
  pinMode(turbPin, INPUT);
  pinMode(phPin, INPUT);
  pinMode(windPin, INPUT);
  Serial.begin(9600);
  Serial.println("--------Sensors init--------");    //Test the serial monitor
}
void loop()
{
  readPH();
  readTurb();
  readWind();
  delay(300);
  //Serial.println(analogRead(SensorPin));

}


void readTurb() {
  int sensorValue = analogRead(turbPin);// read the input on analog pin 0:
  float voltage = sensorValue * (5.0 / 1024.0); // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
  Serial.print("$turb:");
  Serial.println(voltage); // print out the value you read:
  delay(700);
}

void readPH() {
  static unsigned long samplingTime = millis();
  static unsigned long printTime = millis();
  static float pHValue, voltage;
  if (millis() - samplingTime > samplingInterval)
  {
    pHArray[pHArrayIndex++] = analogRead(phPin);
    if (pHArrayIndex == ArrayLenth)pHArrayIndex = 0;
    voltage = avergearray(pHArray, ArrayLenth) * 5.0 / 1024;
    pHValue = 3.5 * voltage + Offset;
    samplingTime = millis();
  }
  if (millis() - printTime > printInterval)  //Every 800 milliseconds, print a numerical, convert the state of the LED indicator
  {

    Serial.print("$ph: ");
    Serial.println(pHValue, 2);
    digitalWrite(LED, digitalRead(LED) ^ 1);
    printTime = millis();
  }
}
void readWind() {
  //int sensorValue = 0; //Variable stores the value direct from the analog pin
  float sensorVoltage = 0; //Variable that stores the voltage (in Volts) from the anemometer being sent to the analog pin
  float windSpeed = 0; // Wind speed in meters per second (m/s)

  float voltageConversionConstant = .004882814; //This constant maps the value provided from the analog read function, which ranges from 0 to 1023, to actual voltage, which ranges from 0V to 5V
  int sensorDelay = 1000; //Delay between sensor readings, measured in milliseconds (ms)

  //Anemometer Technical Variables
  //The following variables correspond to the anemometer sold by Adafruit, but could be modified to fit other anemometers.

  float voltageMin = .4; // Mininum output voltage from anemometer in mV.
  float windSpeedMin = 0; // Wind speed in meters/sec corresponding to minimum voltage

  float voltageMax = 2.0; // Maximum output voltage from anemometer in mV.
  float windSpeedMax = 32;
  float windVal = analogRead(windPin); //Get a value between 0 and 1023 from the analog pin connected to the anemometer
 
  windVal = windVal * voltageConversionConstant; //Convert sensor value to actual voltage

  //Convert voltage value to wind speed using range of max and min voltages and wind speed for the anemometer
  if (windVal <= voltageMin) {
    windSpeed = 0; //Check if voltage is below minimum value. If so, set wind speed to zero.
  } else {
    windSpeed = (windVal - voltageMin) * windSpeedMax / (voltageMax - voltageMin); //For voltages above minimum value, use the linear relationship to calculate wind speed.
  }
  Serial.print("$wind:");
  Serial.println(windSpeed);
  //delay(1000);
}

double avergearray(int* arr, int number) {
  int i;
  int max, min;
  double avg;
  long amount = 0;
  if (number <= 0) {
    Serial.println("Error number for the array to avraging!/n");
    return 0;
  }
  if (number < 5) { //less than 5, calculated directly statistics
    for (i = 0; i < number; i++) {
      amount += arr[i];
    }
    avg = amount / number;
    return avg;
  } else {
    if (arr[0] < arr[1]) {
      min = arr[0]; max = arr[1];
    }
    else {
      min = arr[1]; max = arr[0];
    }
    for (i = 2; i < number; i++) {
      if (arr[i] < min) {
        amount += min;      //arr<min
        min = arr[i];
      } else {
        if (arr[i] > max) {
          amount += max;  //arr>max
          max = arr[i];
        } else {
          amount += arr[i]; //min<=arr<=max
        }
      }//if
    }//for
    avg = (double)amount / (number - 2);
  }//if
  return avg;
}


/*Ginger Judge 2.0 Linear Actuator Control
   Author: Mazlin Higee
      Help from: Jeff Thor, Nick Dos Santos

   This code enables control from a pixhawk running ArduPilot
   Taking control values form the pixhawk and moving a linear
   Actuator to the respective position.
   This specifically has been applied to the rudder of a boat

   This code has been tailored from the example below to fit our needs.
   https://create.arduino.cc/projecthub/robotgeek-projects-team/control-a-large-linear-actuator-with-arduino-8a3953
*/



// constants won't change. They're used here to set pin numbers:
const int button1Pin = 2;     // the number of the pushbutton1 pin
const int button2Pin = 4;     // the number of the pushbutton2 pin
const int relay1Pin =  7;      // the number of the Realy1 pin white
const int relay2Pin =  8;      // the number of the Relay2 pin red
const int sensorPin = 0;    // select the input pin for the potentiometer
const int pix = 3;

// variables will change:
int button1State = 0;         // variable for reading the pushbutton status
int button2State = 0;         // variable for reading the pushbutton status
double sensorValue = 0;  // variable to store the value coming from the sensor
double positionInches = 0; //position of the linear actuator
double setPosition = 0; //the position we want to set the actuator too
bool retracting = false; //the actuator is retracting
bool extending = false; //the actuator is extending





void setup() {


  //start serial connection
  Serial.begin(9600);

  // initialize the pushbutton pin as an input:
  pinMode(button1Pin, INPUT);
  pinMode(button2Pin, INPUT);
  // pinMode(sensorPin, INPUT);
  pinMode(pix, INPUT_PULLUP);
  // initialize the relay pin as an output:
  pinMode(relay1Pin, OUTPUT);
  pinMode(relay2Pin, OUTPUT);
}



void loop() {


  // read the value from the sensor:
  positionInches = analogRead(sensorPin);

  setPosition = pulseIn(pix, HIGH);
  //calc offset to normalize values from pixhawk to output on actuator
  double temp = setPosition;
  setPosition = setPosition - 1077;
  setPosition = setPosition / 1.616;
  setPosition = setPosition + 140;

//  Serial.print("pix val: ");
  Serial.print(temp);
  Serial.print(" PosIN: ");
  Serial.print(positionInches);
  Serial.print(" | Desired:  ");
  Serial.println(setPosition);


  if(temp == 0 && positionInches < 60){ //if we go inside our bounds or pixhawk sends 0 we should turn everything off
    digitalWrite(relay1Pin,!LOW);
    digitalWrite(relay2Pin,!LOW);
    extending = false;
    retracting = false;
  }else if (positionInches < 405 && positionInches > 335 && setPosition > 335 && setPosition < 405  ) { //if we are close to center we dont want the actuator to stutter
    extending = false;
    retracting = false;
    digitalWrite(relay1Pin, !LOW);
    digitalWrite(relay2Pin, !LOW);
  } else if (positionInches < setPosition ) { //i need to go out
    extending = true;
    retracting = false;
    digitalWrite(relay1Pin, !HIGH);
    digitalWrite(relay2Pin, !LOW);
  } else if (positionInches > setPosition) { //i need to go in
    extending = false;
    retracting = true;
    digitalWrite(relay1Pin, !LOW);   //this is in
    digitalWrite(relay2Pin, !HIGH); 
  } //else if (positionInches > 

  if (extending == true && positionInches >= setPosition - 10) {
    //we have reached our goal, shut the relay off
    digitalWrite(relay1Pin, !LOW);
    digitalWrite(relay2Pin,!LOW);
    extending = false;
    Serial.println("IDLE");
    //delay(1000);`                           ` 
  }

  if (retracting == true && positionInches <= setPosition) {
    //we have reached our goal, shut the relay off
    digitalWrite(relay2Pin, !LOW); 
    digitalWrite(relay1Pin, !LOW);

    retracting = false;
    Serial.println("IDLE");
    //delay(1000);
  }
  //delay(30);

/*
 * Button control code is below.
 * 
 */

  
//        // read the state of the pushbutton values:
//        button1State = digitalRead(button1Pin);
//        button2State = digitalRead(button2Pin);
//        // check if the pushbutton1 is pressed.
//        // if it is, the buttonState is HIGH:
//        // we also ensure tha the other button is not pushed to avoid conflict
//        if (button1State == HIGH && button2State == LOW) { // this is in
//          // turn relay1 on:
//         // positionInches = positionInches - copyCount;
//          digitalWrite(relay1Pin, LOW);   //this is out
//        }
//        // When we let go of the button, turn off the relay
//        else if (digitalRead(relay1Pin) == LOW) {
//          // turn relay1 off:
//          digitalWrite(relay1Pin, HIGH);
//        }
//  
//        // repeat the same procedure for the second pushbutton
//        if (button1State == LOW && button2State == HIGH) {     //this is in
//          // turn relay2 on:
//          //positionInches = positionInches + copyCount;
//          digitalWrite(relay2Pin, LOW);
//        }
//        // When we let go of the button, turn off the relay
//        else if (digitalRead(relay2Pin) == LOW) {
//          // turn relay2 off:
//          digitalWrite(relay2Pin, HIGH);
//        }
}

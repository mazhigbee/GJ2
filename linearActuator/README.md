## Ginger Judge 2.0 Linear Actuator
 This serves as a guide on how the steering of the boat functions and interfaces with other components of the project. This guide was origally written by Mazlin Higbee(Endicott College '19). If you have questions you can reach me at mazlinhigbee@gmail.com. But please read this doc in its completion first.  # WiringBelow is an image on the wiring for the entire system. This includes interfacing with relays,pixhawk and arduino.![](https://lh3.googleusercontent.com/-5UB_njH1Ojd8QvtMfxcc3Gk6tAhd1oK7tWiWLsEHX0j2Ck1ZPZA59tHCpnO-WRuMsry1znu0lhlhw "Wiring Diagram")
 
 ## Relays
 It is important that you wire everything correctly. In the finished boat the connections between the relay and the actuator are encased in a *CAT5* cable. Both **signal** wires (yellow and blue labeled as actuator in/out) run from the **center** of the relay. **+12V** runs to the left most pin on the relay and **GND** runs to the left most pin.  **IT IS IMPORTANT TO NOTE THAT THE LOGIC OF THE RELAYS IS INVERSED.** You will notice that all of the **digitalWrites** in code are inversed to handle this.
 
 ## Arduino
 
 The Arduino is the brain of this system. It takes input from the pixhawk on a PWM signal. Ranges **1100-1900.** The code for this is *linearActuator.ino*.  We take input from the pixhawk, naturalize the values to the range the linear actuator potentiometer understands. As long as your pixhawk output range is 1100-1900 you won't need to change the naturalzation. I followed [this guide](https://create.arduino.cc/projecthub/robotgeek-projects-team/control-a-large-linear-actuator-with-arduino-8a3953) to build out my code for our purpose.

 
 **The code provides a serial output that notes the following.**
 
 |Value|  Meaning|
 |--|--|
 |pix val|  literal value from pixhawk pwm read|
 | PosIn |The current position of the linear actuator  |
 |Desired|Where the actuator wants to be |
 
 ## Steering System
The sterring system uses pullys and a rope to move the rudder back and forth.
As the actuator moves out the loop moves one way and vice versa.
![enter image description here](https://lh3.googleusercontent.com/VLN18DkDw9t8LMzJ1jkc4Fu4ZDT7_FYRN4YeXd_O3HFZmfibBWhqXFCbyK2Weyrkic3udETX_WzbMw)


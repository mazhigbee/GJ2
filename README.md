<!DOCTYPE html>
<html>

<head>
  <meta charset="utf-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>GJ2</title>
  <link rel="stylesheet" href="https://stackedit.io/style.css" />
</head>

<body class="stackedit">
  <div class="stackedit__html"><h2 id="ginger-judge-2.0-linear-actuator">Ginger Judge 2.0 Linear Actuator</h2>
<p>This serves as a guide on how the steering of the boat functions and interfaces with other components of the project. This guide was origally written by Mazlin Higbee(Endicott College '19). If you have questions you can reach me at <a href="mailto:mazlinhigbee@gmail.com">mazlinhigbee@gmail.com</a>. But please read this doc in its completion first.  # WiringBelow is an image on the wiring for the entire system. This includes interfacing with relays,pixhawk and arduino.<img src="https://lh3.googleusercontent.com/-5UB_njH1Ojd8QvtMfxcc3Gk6tAhd1oK7tWiWLsEHX0j2Ck1ZPZA59tHCpnO-WRuMsry1znu0lhlhw" alt="" title="Wiring Diagram"></p>
<h2 id="relays">Relays</h2>
<p>It is important that you wire everything correctly. In the finished boat the connections between the relay and the actuator are encased in a <em>CAT5</em> cable. Both <strong>signal</strong> wires (yellow and blue labeled as actuator in/out) run from the <strong>center</strong> of the relay. <strong>+12V</strong> runs to the left most pin on the relay and <strong>GND</strong> runs to the left most pin.  <strong>IT IS IMPORTANT TO NOTE THAT THE LOGIC OF THE RELAYS IS INVERSED.</strong> You will notice that all of the <strong>digitalWrites</strong> in code are inversed to handle this.</p>
<h2 id="arduino">Arduino</h2>
<p>The Arduino is the brain of this system. It takes input from the pixhawk on a PWM signal. Ranges <strong>1100-1900.</strong> The code for this is <em>linearActuator.ino</em>.  We take input from the pixhawk, naturalize the values to the range the linear actuator potentiometer understands. As long as your pixhawk output range is 1100-1900 you won’t need to change the naturalzation. I followed <a href="https://create.arduino.cc/projecthub/robotgeek-projects-team/control-a-large-linear-actuator-with-arduino-8a3953">this guide</a> to build out my code for our purpose.</p>
<p><strong>The code provides a serial output that notes the following.</strong></p>

<table>
<thead>
<tr>
<th>Value</th>
<th>Meaning</th>
</tr>
</thead>
<tbody>
<tr>
<td>pix val</td>
<td>literal value from pixhawk pwm read</td>
</tr>
<tr>
<td>PosIn</td>
<td>The current position of the linear actuator</td>
</tr>
<tr>
<td>Desired</td>
<td>Where the actuator wants to be</td>
</tr>
</tbody>
</table><h2 id="steering-system">Steering System</h2>
<p>The sterring system uses pullys and a rope to move the rudder back and forth.<br>
As the actuator moves out the loop moves one way and vice versa.<br>
<img src="https://lh3.googleusercontent.com/VLN18DkDw9t8LMzJ1jkc4Fu4ZDT7_FYRN4YeXd_O3HFZmfibBWhqXFCbyK2Weyrkic3udETX_WzbMw" alt="enter image description here"></p>
</div>
</body>

</html>

This folder contains codes written for a clap following robot based on Arduino. 

The robot has to have 3 sound sensors, each of which has to be placed at the vertices of an equilateral triangle of side ~30cm and attached to the interrupt pins of the arduino.

The robot also needs to have position encoders attached to the wheels to accurately turn to appropriate angles/directions. 

The robot calculates the approximate angle/direction of the clap by noting the time of arrival of the clap sound at each of the sensors and using a trivial triangulation algorithm based on the differences in this time. After calculating the approximate angle to turn, the robot can easily turn to this angle with the help of the position encoders attached to the wheels.

This directory contains codes and files from the Gesture Controlled Robotics Workshop conducted by RoboCET during July 2015 at Mar Baselios College of Engineering, Trivandrum.

In the Workshop, students were taught to build a small robot car that could be controlled remotely by their hand gestures.

The components of the project were:

Receiver Side
-------------
1. A small robot car with two 150RPM DC motors attached to the wheels at the rear, a castor wheel at the front and a custom made motor driver PCB.
2. An nRF2401 radio transceiver module for communication.
3. An Atmel Atmega328 microcontroller with Arduino bootloader.
4. Li-ion batteries.
5. A custom PCB to hold the microcontroller, nRF module and supply signals to the motor driver board on the robot car.

Transmitter Side
----------------
1. An nRF2401 radio transceiver module for communication.
2. An Atmel Atmega328 microcontroller with Arduino bootloader.
3. An ADXL335 accelerometer module to decode gestures (left, right, front, back, stop)
4. A 9V battery.
5. A custom PCB to hold the above modules and microcontroller.
6. A plastic board and velcro to hold the board and strap it to the user's arm.

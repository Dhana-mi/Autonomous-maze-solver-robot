# Autonomous-maze-solver-robot
Arduino based robot that uses three ultra-sonic sensors and two dc motors to solve any given maze.



Algorithm:

![image](https://user-images.githubusercontent.com/103918812/230790262-0e9afe62-ffdf-4611-b4ec-ae32612b259f.png)



Arduino Code Explanation:

First, we define the pins for the ultrasonic sensors and the DC motors interfaced to the Arduino UNO pins and the L298n Motor Driver respectively.
We setup the pin configurations with regard to the input and output. The trigger pins of the ultrasonic sensors are set as output and echo pins as input. All the motor driver pins as output initially.
For enable pins (EnA and EnB) of the motor driver should be set to the PWM pins for working of DC motor.
We define the functions for front, left and right distances and then we find the median of the respective distances and note them down.
Using those distances, we write the movement functions according to the left-wall following algorithm. 
We execute these movement functions when certain distance conditions are met and the robot solves the maze.

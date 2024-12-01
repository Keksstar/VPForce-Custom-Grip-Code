# Two Nano Configuration
Uses two Arduino Nanos to achieve up to 32 buttons and 4 axes. Different code for each board, can be used with or without axes but not individually. If making a button only stick with this option, select "Generic Grip" in the VPF configurator. If axes are to be connected select "WinWing Adapter" in the VPF configurator. I have had best results with this using the 5V clock signal option in the VPF Configurator advanced options. 

# DISCLAIMER
All code should be used at your own risk. I do not accept responsibilty for damages or loss due to implementation of this code. I am not a software engineer, so there are more than likely ways that this code can be improved. Please feel free to make suggestions for improvements but as long as things are working as intended I may reserve the right to keep things as is.

# NOTE
I have seen some 3rd party Nanos with ICSP headers that do not match the pinout of genuine Nanos. Verify connections with a multimeter before using these pins for programming or power. I have illustrated power/ground using only the edge pins for this reason. Using the ICSP pins may make wiring easier, but they must be verified prior to use. 

![image](../images/GenuineNanoPinout.jpg)

# Two Board Wiring Diagram
![image](../images/TwoNanoWiringDiagram.jpg)

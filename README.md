# VPForce-Custom-Grip-Code
Various methods to make custom grips compatible with VPForce boards for use with VPF Rhino or DIY options. Updated from legacy code to use Arduino Nano for access to cheap clones and better input configuration. 

# DISCLAIMER
All code should be used at your own risk. I do not accept responsibilty for damages or loss due to implementation of this code. I am not a software engineer, so there are more than likely ways that this code can be improved. Please feel free to make suggestions for improvements but as long as things are working as intended I may reserve the right to keep things as is.

# One Nano Configuration
Uses one Arduino Nano to achieve 16 buttons and 2 axes. If making a button only stick with this option, select "Generic Grip" in the VPF configurator. If axes are to be connected select "WinWing Adapter" in the VPF configurator. Replaces legacy "Arduino Only" code. 

# Two Nano Configuration
Uses two Arduino Nanos to achieve 32 buttons and 4 axes. Each board can be used with or without axes but the boards can not be used on their own and must be paired together as shown in the wiring diagram. If making a button only stick with this option, select "Generic Grip" in the VPF configurator. If axes are to be connected select "WinWing Adapter" in the VPF configurator. 

# Arduino with Shift Register
UPDATE IN PROGRESS TO USE LATEST WinWing ADAPTER CODE. 
<!--Use the files in "Arduino+Shift-Register" if you have connected a shift register in series with your Arduino to expand the inputs. This was orignally designed for the VPForce Shift Register board but should work with other shift registers that use CD4021B shift registers or SN74HC165 shift registers with an inverted latch signal. Please review the connection diagrams of those chips prior to connection to verify proper circuit configurations.-->


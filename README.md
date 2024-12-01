# VPForce-Custom-Grip-Code
Various methods to make custom grips compatible with VPForce boards for use with VPF Rhino or DIY options. Updated from legacy code to use Arduino Nano for access to cheap clones and better input configuration. 

# DISCLAIMER
All code should be used at your own risk. I do not accept responsibilty for damages or loss due to implementation of this code. I am not a software engineer, so there are more than likely ways that this code can be improved. Please feel free to make suggestions for improvements but as long as things are working as intended I may reserve the right to keep things as is.

# One Nano Configuration
Uses one Arduino Nano to achieve 16 buttons and 2 axes. If making a button only stick with this option, select "Generic Grip" in the VPF configurator. If axes are to be connected select "WinWing Adapter" in the VPF configurator. Replaces legacy "Arduino Only" code. Pay attention to SPI interrupt routine comments if only using one of the two axes, you should change the code per the comments on the unused axis. 

# Two Nano Configuration
Uses two Arduino Nanos to achieve 32 buttons and 4 axes. Each board can be used with or without axes but the boards can not be used on their own and must be paired together as shown in the wiring diagram. If making a button only stick with this option, select "Generic Grip" in the VPF configurator. If axes are to be connected select "WinWing Adapter" in the VPF configurator. Pay attention to SPI interrupt routine comments if only using one of the two axes on either board, you should change the code per the comments on the unused axis. 

# Arduino with Shift Register
UPDATE IN PROGRESS TO USE LATEST WinWing ADAPTER CODE. I currently do not have the ability to test this because my shift register boards are in use on other projects. I will update this as I find time, but the code will likely be untested and not guaranteed to work. I believe when using the Nano in tandem with the shift register, you can add additional buttons wired to the Nano to use up to 48 total buttons of the Winwing adapter profile. However, due to the limitations on the input pins for the Nano, using 48 buttons with a 32bit shift register will only leave 3 axis inputs open. If you need 4 axis, you are limited to 47 buttons. You can also just use the nano to handle axis data and not connect any buttons to the Nano using either the 48+3 or 47+4 options. The code for this configuration is similar to the other two configurations but not an exact copy. Contact me on the VPF discord knowledge base thread on axis data for custom grips and I will try to help you. 

<!--Use the files in "Arduino+Shift-Register" if you have connected a shift register in series with your Arduino to expand the inputs. This was orignally designed for the VPForce Shift Register board but should work with other shift registers that use CD4021B shift registers or SN74HC165 shift registers with an inverted latch signal. Please review the connection diagrams of those chips prior to connection to verify proper circuit configurations.-->


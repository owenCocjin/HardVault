# HardVault
> Pics, files, and schematics on my PPM project

## About
I never save my passwords when a browser asks me to because if I don't constantly type it in I'll forget it. I don't want to use a password manager because if I have to login on a different machine I won't have access to the manager (don't quote me on this). My solution was to make my own <b>P</b>hysical <b>P</b>assword <b>M</b>anager that I can carry anywhere!

This device is motion controlled. To navigate the menu, you tilt the device then click a button. By default the device hides the passwords. This is because you can plus the device into a computer (or potentially a phone) and write the password straight to the form.



## Schematics/Pics
> The "Schematics" directory has all the files from KiCAD.

![ppm guts](https://github.com/owenCocjin/HardVault/blob/master/Pics/hardware.jpg "PPM Hardware")

![ppm everything](https://github.com/owenCocjin/HardVault/blob/master/Pics/disassembled.jpg "PPM disassembled")

![ppm shell](https://github.com/owenCocjin/HardVault/blob/master/Pics/case_layered.jpg)

![ppm schematic](https://github.com/owenCocjin/HardVault/blob/master/Pics/ppm_schematic.png "Circuit Schematic")

## Current Drawbacks/Future Updates
> There are still a couple things I'd like to address, probably in the far future:
- There is currently no login page (just a demo). The goal is to make a "something you do" password. This would be a sequence of directional tilts made by tilting the device then clicking the button. The password would also be used to encrypt the passwords, which are currently plaintext stored in the flash code of the arduino.
	- This page will also address failed logins
- The passwords are all hard-coded in plaintext in the arduino's code. I want to move these somewhere else. There is potential to add an EEPROM or another storage medium to save these passwords.
- To change passwords you need to edit the source code. Preferably, this could be done through serial after the user logs into the device.
- Currently, the device is powered via usb. If you can't plug the device in, it becomes just a waste of plastic! I need to add battery power, which means re-design the CAD, add wiring (literally just wires to the arduino GND and RAW), and add a power switch. 

## Straight Up Fixin'
- The top & bottom cases don't fit well. This is [probably] because the `ProMicroRest` on the top case is too long.
- The code is kinda nasty! in the `isr_core()` function there are 4 `if` statements?!?! Gross. Turn that into an array of functions instead. Yummy!

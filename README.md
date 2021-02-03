# HardVault
> Pics, files, and schematics on my PPM project

## About
I never save my passwords when a browser asks me to because if I don't constantly type it in I'll forget it. I don't want to use a password manager because if I have to login on a different machine I won't have access to the manager (don't quote me on this). My solution was to make my own __P__hysical __P__assword __M__anager that I can carry anywhere!

This device is motion controlled. To navigate the menu, you tilt the device then click a button. By default the device hides the passwords. This is because you can plus the device into a computer (or potentially a phone) and write the password straight to the form.



## Schematics
> The "Schematics" directory has all the files from KiCAD.

[ppm schematic](https://github.com/owenCocjin/HardVault/blob/master/Pics/ppm.svg "Circuit Schematic")

## Current Drawbacks/Future Updates
> There are still a couple things I'd like to address, probably in the far future:
- There is currently no login page (just a demo). The goal is to make a "something you do" password. This would me a sequence of directional tilts made by tilting the device then clicking the button. The password would also be used to encrypt the passwords, which are currently plaintext stored in the flash code of the arduino.
	- This page will also address failed logins
- The passwords are all hard-coded in plaintext in the arduino's code. I want to move these somewhere else. There is potential to add an EEPROM or another storage medium to save these passwords.
- To change passwords you need to edit the source code. Preferably, this could be done through serial after the user logs into the device.

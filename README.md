# HardVault
> Pics, files, and schematics on my PPM project

## About
I never save my passwords when a browser asks me to because if I don't constantly type it in I'll forget it. I don't want to use a password manager because if I have to login on a different machine I won't have access to the manager (don't quote me on this). My solution was to make my own <b>P</b>hysical <b>P</b>assword <b>M</b>anager that I can carry anywhere!

This device is motion controlled. To navigate the menu, you tilt the device then click a button. By default the device hides the passwords. This is because you can plug the device into a computer (or potentially a phone) and write the password straight to the form.

## Schematics/Pics
> The "Schematics" directory has all the files from KiCAD.

![ppm guts](https://github.com/owenCocjin/HardVault/blob/master/Pics/hardware.jpg "PPM Hardware")

![ppm everything](https://github.com/owenCocjin/HardVault/blob/master/Pics/disassembled.jpg "PPM disassembled")

![ppm shell](https://github.com/owenCocjin/HardVault/blob/master/Pics/case_layered.jpg)

![ppm schematic](https://github.com/owenCocjin/HardVault/blob/master/Pics/ppm_schematic.png "Circuit Schematic")

## Security
Right now, there is no security whatsoever on the HardVault. This will be fixed incrementally:
1. Prevent access via login page
2. Expand password complexity capabilities (see below)
3. Encrypt passwords via login password (or other means)
4. Secure the arduino from reading so no one can take the compiled code (and passwords) off of it

To calculate the number of possibilities of a password, you would do:
```
# of possible characters ^ # of characters in the password
```
We currently have 4 possible chars (up, down, left, right), and an _unlimited_ number of password chars. a practical amount would be between 4-8. You can only do 4 button presses per second because of the button debouncing. Therefore to calculate how long it would take to bruteforce a password, you would use:
```
# of directions ^ # of chars * (debounce time * # of chars)
    ---- Or more formally ----
x^y*(d*y)
where x=# of directions, y=# of characters, and d=debounce time
```
There are a couple different methods to increasing this time:
- Use 8 directions instead of 4, which can be implemented through single vs long clicks.
- Increase the debounce time.
- Add a failed login timeout. This will add `timeout*total passwords` more time to the bruteforcing time, making the equation:
```
x^y*(d*y)+t*(x^y)
```

Below is a chart of the bruteforce attempt times:
| # of Directions | # of Chars | Debounce Time | Max Crack Time |
| --- | --- | --- | --- |
| 4 | 4 | 25ms | 4m15s |
| 4 | 6 | 25ms | 1h42m |
| 4 | 8 | 25ms | 36h24m |
| 8 | 4 | 25ms | 1h8m |
| 8 | 6 | 25ms | 4d13h |
| 8 | 8 | 25ms | 1y23d |
| 4 | 4 | 35ms | 5m58s |
| 4 | 6 | 35ms | 2h23m |
| 4 | 8 | 35ms | 2d3h |
| 8 | 4 | 35ms | 1h35m |
| 8 | 6 | 35ms | 6d9h |
| 8 | 8 | 35ms | 1y178d |

Here is a table comparing with vs without failed login timeouts (with 25ms debounce time):
| # of Directions | # of Chars | Failed Login T/O | Max Crack Time |
| --- | --- | --- | --- |
| 4 | 4 | 0s | 4m15s |
| 4 | 6 | 0s | 1h42m |
| 4 | 8 | 0s | 36h24m |
| 4 | 4 | 1.5s | 10m40s |
| 4 | 6 | 1.5s | 3h24m |
| 4 | 8 | 1.5s | 2d15m |
| 4 | 4 | 3s | 17m4s |
| 4 | 6 | 3s | 5h7m |
| 4 | 8 | 3s | 3d19h |

Overall, using more directions is vastly better than any of the other options, but if for whatever reason this isn't possible, the other options provide better security.

- Fastest performance: 4 dirs, 4 chars, 0 FLT/O, 25ms Debounce
- Best overall: 4 dirs, 6 chars, 1.5s FLT/O, 35ms Debounce
- Best ssecurity: 8 dirs, 8 chars, 3s FLT/O, 35ms Debounce

---

Another security vector to watch is reverse engineering the device. If the device were stolen, ripping the compiled code (and the passwords) is trivial, as long as the attacker can read/analyze assembly. On its own, this will most likely deter many people from stealing the passwords. Regardless, to remediate this flaw, you can set a "security bit" on the arduino which prevents the code from being read. This may or may not permanently lock the device, so either the source code must be flawless, or an alternative method must be used to store the passwords (to allow modifying passwords).

Instead of potentially permanently locking the arduino, we can "encrypt" the passwords, most likely via the login password. Even if the data were stolen, the attacker must now figure out how to decrypt the data.

## Current Drawbacks/Future Updates
> There are still a couple things I'd like to address, probably in the far future:
- There is currently no login page (just a demo). The goal is to make a "something you do" password. This would be a sequence of directional tilts made by tilting the device then clicking the button. The password would also be used to encrypt the passwords, which are currently plaintext stored in the flash code of the arduino.
	- This page will also address failed logins
- The passwords are all hard-coded in plaintext in the arduino's code. I want to move these somewhere else. There is potential to add an EEPROM or another storage medium to save these passwords.
- To change passwords you need to edit the source code. Preferably, this could be done through serial after the user logs into the device.
- Currently, the device is powered via usb. If you can't plug the device in, it becomes just a waste of plastic! I need to add battery power, which means re-design the CAD, add wiring (literally just wires to the arduino GND and RAW), and add a power switch.
- The USB port is pretty vulnerable to wear n' tear. During the build I had it almost rip off the arduino! Luckily it was a quick (non-SMD) soldering job. Might need to fix it to prevent future breaks.
- Even if the data can be encrypted, the login password must be stored in plaintext (unless I can figure out how to hash it)

## Straight Up Fixin'
- The top & bottom cases don't fit well. This is [probably] because the `ProMicroRest` on the top case is too long.
- The code is kinda nasty! in the `isr_core()` function there are 4 `if` statements?!?! Gross. Turn that into an array of functions instead. Yummy!

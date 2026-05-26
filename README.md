# Important

Caution! this is not a professional project. Anything you do with this firmware is at your own risk. In any case, use a quick fuse in the power supply to minimize the risk of destroying the controller, battery or motor!

Please read and reread the [wiki](https://github.com/stancecoke/BMSBattery_S_controllers_firmware/wiki).

## Preface

Many thanks to the team of the Forumscontroller, Main functions are from [there](https://github.com/jenkie/Arduino-Pedelec-Controller)!

This is the maintained fork of [casainho's project(not maintained)](https://github.com/OpenSource-EBike-firmware/BMSBattery_S_controllers_firmware)

## About the project

This firmware replaces the closed source one on Kunteng sine wave controllers. It enables you to change basically anything about the way the controller reacts to inputs (throttle, PAS, torque sensor, brake, displays) and handles different modes/states concerning  power output.
[A graphical tool](https://github.com/stancecoke/BMSBattery_S_controllers_firmware/wiki/04-The-Java-Tool) is available, which allows the use of the firmware even for less experienced Windows users without programming knowledge. With the [BluOsec android app](https://github.com/stancecoke/BMSBattery_S_controllers_firmware/wiki/05-The-BluOSEC-Android-App) you can control the assist level and set many parameters at runtime.  [Download it by clicking this link](https://github.com/Xnyle/bluosec-apk/raw/master/BluOsec-release.apk).

### Help out yo

 If you want something added / changed that isn't already implemented / beta / buggy, you have to get involved yourself. This is a hobbyists project and there is no one else to blame than yourself if something isn't working as desired ;-)

### What works  

* Sine wave control with simplified FOC  
* Overvoltage (regeneration) and undervoltage protection
* Motor stop while braking
* Driving modes:  
    * PAS sensor with torque simulation and reverse step detection
    * Throttle (also as override)
    * Torque sensor  
    * Recuperation via analog "thumb brake" signal or digitally by brake switch  
    * Start-up support in torque sensor mode  
    * Pushing aid
    * Block commutation during start-up (only if you have o motor without "weird" angle definitions.
* Displays:
    * Kunteng LCD3 / LCD5 (C/P parameters mapped differently)
    * BluOsec App as Display / as Trip monitor / for on the fly configuration  
    * Kingmeter J-LCD and Forerider App (not tested for a long time now)

### What doesn't

* You debug it thoroughly
* You tell us / patch it yourself ;-)

## For further reading

The documentation on the project, aka wiki, can be found [here](https://github.com/stancecoke/BMSBattery_S_controllers_firmware/wiki)  

The corresponding thread in the german Pedelecforum [can be found here](https://www.pedelecforum.de/forum/index.php?threads/custom-rom-f%C3%BCr-kunteng-s06s-kt36-controller.50061/)  

## Want to help

There is always things to improve, don't hesitate to get involved if you have improvements in mind.

## Pre requisits

    You will need an ebike with a Kunteng controller, there are two types available. Models with *SVPR* in the model name these work without modification. The other type is *ZWSRM* these are square wave controllers that will need a current sensor, look for (Allegro ACS711 or ACS712) inserting on to the empty pads on the board. Then removing the existing solder bridging blob. Then this software will work.


## Build instructions on Linux

1. First download and install https://stm8-binutils-gdb.sourceforge.io/

2. Point the environment variable to the source directory of binutils. like below.

    export STM8BINUTILS=/home/username/stm8-binutils-gdb-sources/binutils-2.30/binutils/

3. Install SDCC (Small device C Compiler)

    sudo apt install sdcc git minicom

4. clone this repo and enter into it.

    git clone https://github.com/JamesCordell/BMSBattery_S_controllers_firmware_ng
    cd BMSBattery_S_controllers_firmware_ng

5. Read the config.h and adjust as appropriate.

6. Select the relevant make file for your operating system.
    
    mv Makefile_linux Makefile

7. Compile

   make unlock    # This step will remove the existing from the stm8 chip, after this it is not possible to restore the original software

   make clean

   make all

   make flash     # You will need a stm8 flash usb key for this step.

8. Login and view if the software is running. You will need a serial adapter for this step.

   minicom -D /dev/ttyUSB0 -s 9600


# MySensors Ethernet gateway firmware
This repository includes the firmware for MySensors Ethernet gateway. The
firmware is designed for [IBoard](http://wiki.iteadstudio.com/IBoard). For
building the firmware, the use of [PlatformIO](http://platformio.org)
tool is assumed.

## Getting the source
Used libraries are added in this repository as git submodules. Before building
the firmware it is important to update the git submodules by running:
```
git submodule update --init --recursive
```

## Building the firmware
Before building the firmware it is important to prepare all the libraries
into the proper directory structure as expected by PlatformIO. Also it is
important to replace default settings of some of the libraries with the
project specific ones. This can be done easily just by running:
```
sh prep.sh
```
This script will take care of preparing the libraries for PlatformIO. If you
changed any of the project specific configuration files, it is important to run
this script again before the build.

Building is easy as running a single command:
```
platformio run
```
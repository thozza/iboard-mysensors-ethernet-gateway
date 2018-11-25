[![Build Status](https://travis-ci.org/thozza/iboard-mysensors-ethernet-gateway.svg?branch=master)](https://travis-ci.org/thozza/iboard-mysensors-ethernet-gateway)

# MySensors Ethernet gateway firmware
This repository includes the firmware for MySensors Ethernet gateway. The
firmware is designed for [IBoard](http://wiki.iteadstudio.com/IBoard). For
building the firmware, the use of [PlatformIO](http://platformio.org)
tool is assumed.

Code expects MySensors library version **2.3.0**.

## Building the firmware
Building is easy as running a single command:
```
platformio run
```
PlatformIO will take care of downloading MySensors library itself.

## Uploading the firmware
Run:
```
platformio run --target upload
```
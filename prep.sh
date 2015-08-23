#!/bin/bash

# Script preparing the environment for platformIO run

# create lib/ directory if not present
if [ ! -d "lib" ]; then
    mkdir "lib" && echo "Creating lib/ directory"
fi

# -------------------------------------------------------------------
# MySensors preparations
#MY_SENSORS_GIT_LOCATION="MySensors-upstream-git/libraries/MySensors"
MY_SENSORS_GIT_LOCATION="MySensors-thozza-git/libraries/MySensors"
MY_SENSORS_LIB_LOCATION="lib/MySensors"
MY_CONFIG_NAME="MyConfig.h"

# clean the MySensors from lib/
rm -rf $MY_SENSORS_LIB_LOCATION && echo "Removing $MY_SENSORS_LIB_LOCATION"
cp -r $MY_SENSORS_GIT_LOCATION $MY_SENSORS_LIB_LOCATION && echo "Copying $MY_SENSORS_GIT_LOCATION to $MY_SENSORS_LIB_LOCATION"

# delete unused stuff
rm -rf "$MY_SENSORS_LIB_LOCATION/examples"

if [ -f "src/$MY_CONFIG_NAME" ]; then
    echo "Using project specific $MY_CONFIG_NAME from src/"
    cp "src/$MY_CONFIG_NAME" $MY_SENSORS_LIB_LOCATION && echo "Copying $MY_CONFIG_NAME"
else
    echo "No project specific configuration $MY_CONFIG_NAME found, using the default one"
fi

# -------------------------------------------------------------------
# DigitalIO preparations
DIGITALIO_GIT_LOCATION="DigitalIO-upstream-git/DigitalIO"
DIGITALIO_LIB_LOCATION="lib/DigitalIO"

# clean the DigitalIO from lib/
rm -rf $DIGITALIO_LIB_LOCATION && echo "Removing $DIGITALIO_LIB_LOCATION"
cp -r $DIGITALIO_GIT_LOCATION $DIGITALIO_LIB_LOCATION && echo "Copying $DIGITALIO_GIT_LOCATION to $DIGITALIO_LIB_LOCATION"

# delete unused stuff
rm -rf "$DIGITALIO_LIB_LOCATION/examples"


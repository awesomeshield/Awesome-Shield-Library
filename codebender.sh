#!/bin/bash

# Save current directory
OLDPWD=$(pwd)

# Delete the old copy of the Awesome folder

# Move into lib and zip the Awesome folder
cd lib
zip -r ~/Downloads/Awesome.zip Awesome

# Move back into main directory
cd $OLDPWD

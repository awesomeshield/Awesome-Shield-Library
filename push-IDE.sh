#!/bin/sh

# recusively copy the WC copy to the IDE Library folder
cp -R -p /Volumes/BOOSTER/Dropbox/WC/awesome-board/lib/Awesome /Users/Chris/Documents/Arduino/libraries/

# zip -R Awesome /Users/Chris/Documents/Arduino/libraries/Awesome
# compress the library
#tar -zcvf Awesome.zip /Users/Chris/Documents/Arduino/libraries/Awesome/

# move the library back to downloads
# mv /Users/Chris/Documents/Arduino/libraries/Awesome/Awesome.zip /Users/Chris/Downloads

echo "Finished"

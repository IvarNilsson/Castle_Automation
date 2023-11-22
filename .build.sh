BOLD=$(tput bold)
UNDERLINE=$(tput smul)
RESET=$(tput sgr0)

echo #new line
echo "${BOLD}--- Begin compile and flash ${UNDERLINE}$1${RESET}"
echo #new line

# make temp dir for project to be run
mkdir run
mkdir run/$1

# add project file
cp src/$1.cpp run/$1
mv run/$1/$1.cpp run/$1/$1.ino

cp src/$2.cpp run/$1
#mv run/$1/$2.cpp run/$1/$2.ino

#arduino-cli compile --fqbn esp32:esp32:nodemcu-32s run/$1/$1.ino
#arduino-cli upload -p /dev/ttyUSB0 --fqbn esp32:esp32:nodemcu-32s run/$1/$1.ino
arduino-cli compile --fqbn esp32:esp32:esp32wrover run/$1/$1.ino --build-property build.partitions=min_spiffs --build-property upload.maximum_size=1966080
arduino-cli upload -p /dev/ttyUSB0 --fqbn esp32:esp32:esp32wrover run/$1/$1.ino 


rm -rf run/*
rmdir run

echo #new line
echo "${BOLD}--- Done programing ${UNDERLINE}$1${RESET}"

echo #new line
echo "${BOLD}--- Starting Serial Monitor${RESET}"
echo "${BOLD}---------------------------${RESET}"
echo #new line
echo #new line

stty -F /dev/ttyUSB0 raw 115200
cat /dev/ttyUSB0

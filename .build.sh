echo begin compile and flash $1

mkdir run
mkdir run/$1

cp src/$1.cpp run/$1
mv run/$1/$1.cpp run/$1/$1.ino

arduino-cli compile --fqbn esp32:esp32:nodemcu-32s run/$1/$1.ino
arduino-cli upload -p /dev/ttyUSB0 --fqbn esp32:esp32:nodemcu-32s run/$1/$1.ino

rm -rf run/*
rmdir run

echo Done! $1

BOLD=$(tput bold)
UNDERLINE=$(tput smul)
RESET=$(tput sgr0)

echo
echo "${BOLD}Begin add_lib ${UNDERLINE}$1${RESET}"
echo

# add lib
mkdir /home/$USER/Arduino/libraries/$1
cp src/$1/$1.cpp /home/$USER/Arduino/libraries/$1
cp src/$1/$1.h   /home/$USER/Arduino/libraries/$1

echo
echo "${BOLD}Done! ${UNDERLINE}$1${RESET}"
echo
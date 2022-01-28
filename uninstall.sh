#!/bin/sh
#Installer for C-Chess

##COLORS
greenColour="\e[0;32m\033[1m"
redColour="\e[0;31m\033[1m"
blueColour="\e[0;34m\033[1m"
yellowColour="\e[0;33m\033[1m"
purpleColour="\e[0;35m\033[1m"
turquoiseColour="\e[0;36m\033[1m"
grayColour="\e[0;37m\033[1m"
endColour="\033[0m\e[0m"

echo -e "${greenColour}[*] Script for uninstalling the app${endColour}"

#!Verifies if running as root
if [[ $(whoami) != "root" ]]
then
  echo -e "${redColour}[-] Must run as root${endColour}"
  exit 1
else
  rm /bin/C-Chess
fi

for user in $(ls /home/)
do
  if [[ $user != "lost+found" ]]
  then
    echo -e "${blueColour}[=] Deleting config file for $user${endColour}"
    rm /home/$user/.config/C-Chess.config
  fi
done

echo -e "${turquoiseColour}[^] Finished script${endColour}"

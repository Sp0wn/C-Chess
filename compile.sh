#!/bin/sh

greenColour="\e[0;32m\033[1m"
redColour="\e[0;31m\033[1m"
blueColour="\e[0;34m\033[1m"
yellowColour="\e[0;33m\033[1m"
purpleColour="\e[0;35m\033[1m"
turquoiseColour="\e[0;36m\033[1m"
grayColour="\e[0;37m\033[1m"
endColour="\033[0m\e[0m"

HOME=$(pwd)

echo -e "${greenColour}[*] Script for compiling the app${endColour}"

for obj in $(ls)
do
  dir="$(file $obj | cut -d " " -f 2)"
  if [[ $dir == "directory" ]]
  then
    echo -e "${yellowColour}[+] Checking in $obj${endColour}"
    cd $obj
    for files in $(ls)
    do
      source="$(echo $files | cut -d "." -f 2)"
      if [[ $source == "c" ]]
      then
        echo -e "${blueColour}[>] Compiling $files${endColour}"
      fi
    cd $HOME
    done
  fi
done

echo -e "${turquoiseColour}[^] Finished setup${endColour}"

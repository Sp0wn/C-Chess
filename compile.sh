#!/bin/sh
#Autocompiler for C-Chess

##COLORS
greenColour="\e[0;32m\033[1m"
redColour="\e[0;31m\033[1m"
blueColour="\e[0;34m\033[1m"
yellowColour="\e[0;33m\033[1m"
purpleColour="\e[0;35m\033[1m"
turquoiseColour="\e[0;36m\033[1m"
grayColour="\e[0;37m\033[1m"
endColour="\033[0m\e[0m"

##ENVS
HOME=$(pwd)

##VARS
compiled=()

echo -e "${greenColour}[*] Script for compiling the app${endColour}"

#!Searches for all the directories
for obj in $(ls)
do
  #!Checks if object is a directory
  dir="$(file $obj | cut -d " " -f 2)"
  if [[ $dir == "directory" ]]
  then
    echo -e "${yellowColour}[+] Checking in $obj${endColour}"
    cd $obj
    #!Searches for C code in the listed directory
    for files in $(ls)
    do
      #!Checks if file is a .c
      source="$(echo $files | cut -d "." -f 2)"
      if [[ $source == "c" ]]
      then
        echo -e "${blueColour}[>] Compiling $files${endColour}"
        clang -c -w $files
        #!Tracks .o file
        compiled+=("$obj/$(echo $files | tr ".c" ".o")")
      fi
    done
  fi
  cd $HOME
done

echo -e "${yellowColour}[+] Checking in /${endColour}"
echo -e "${blueColour}[>] Compiling main.c${endColour}"
clang -c -w main.c
compiled+=("main.o")

echo -e "${purpleColour}[&] Making binary${endColour}"
clang ${compiled[*]} -o C-Chess

echo -e "${turquoiseColour}[^] Finished setup${endColour}"

#!/bin/bash
#!/usr/bin/g++

g++ $1.cpp -o $1.elf -std=c++2a -O2 -Wall -Wextra -fsanitize=address,undefined
if [ $? -eq 0 ]; then
    echo -e "\033[32m Compiling Done :) \033[0m"
    ./$1.elf
else
    echo -e "\033[31m Compiling Failed :( \033[0m"
fi

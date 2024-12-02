#!/bin/bash
#!/usr/bin/g++

g++ $1.cpp -o $1.elf -Wall -Wextra -fsanitize=address,undefined
echo -e "\033[32m Compiling Done :) \033[0m"
./$1.elf

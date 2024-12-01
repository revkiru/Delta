#!/bin/bash
#!/usr/bin/g++

g++ $1.cpp -o $1.elf -Wall -Wextra -fsanitize=address,undefined
./$1.elf

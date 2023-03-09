# MASK
BIT II project. Refactored by myself 2023 March, mostly done by myself.

## Cli based program for
- hiding message inside png/jpg without damaging images
- retriving message properly from png/jpg. PNG function has header checker.
- hiding your password and id inside text file
- encrypts your password, can be decrypted by this program or your brain if you think properly ;)
- can store more than 1 password in same file. It has a parser for that

## Installation
` gcc mask.c mask_image.c mask_passwd.c -o mask `

## Usage
I've used linux getopts for cli usage so I guess its self explanatory once you run the program

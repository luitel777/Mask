#ifndef __MASK_C__
#define __MASK_C__
#include <stdio.h>
#include <getopt.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <errno.h>
#include <unistd.h>

#define ENCRYPTION 5
#define BUFFER 8
#define MESSAGE 1024

void show();
void save();
void mask_image();
void mask_passwd();

#endif

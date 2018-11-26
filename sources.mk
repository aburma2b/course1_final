#******************************************************************************
# Copyright (C) 2017 by Alex Fosdick - University of Colorado
#
# Redistribution, modification or use of this software in source or binary
# forms is permitted as long as the files maintain this copyright. Users are 
# permitted to modify this and use it to learn about the field of embedded
# software. Alex Fosdick and the University of Colorado are not liable for any
# misuse of this material. 
#
#*****************************************************************************

#This file was modified by Ankush Burman for a coursera course assignment
#Oct 30, 2018

#This switch defaults sources and includes for msp432 if no platform or any 
#other platform other than host is provided.

#Only two .o and .d files are generated if platform is host because
#there are only two sources for it.

#Five .o and .d files are generated when the platform is set to MSP432

ifeq ($(PLATFORM), HOST)

 SOURCES =      ./main.c \
                ./memory.c

 INCLUDES =     -I../include/common

else

 SOURCES =      ./main.c \
                ./memory.c \
                ./interrupts_msp432p401r_gcc.c \
                ./startup_msp432p401r_gcc.c \
                ./system_msp432p401r.c

 INCLUDES =     -I../include/common \
                -I../include/msp432 \
                -I../include/CMSIS
endif




#*****************************************************************************
# Copyright (C) 2017 by Alex Fosdick - University of Colorado
#
# Redistribution, modification or use of this software in source or binary
# forms is permitted as long as the files maintain this copyright. Users are 
# permitted to modify this and use it to learn about the field of embedded
# software. Alex Fosdick and the University of Colorado are not liable for any
# misuse of this material. 
#
#*****************************************************************************

#------------------------------------------------------------------------------
# Makefile completed by Ankush Burman on Nov 2, 2018 to compile and make 
# an executable by using make. Rules and recipes with verbose comments 
# are defined in this file.
#
# ****THE ARM TOOLCHAIN OR THE ARM-NONE-LINUX-GNEUBI TOOLCHAIN MUST BE
#       INSTALLED FOR MAKE TO WORK WITH THE platform SET TO DEFAULT****
#
# Use: make [TARGET] [PLATFORM-OVERRIDES]
#
# Build Targets:
#      .o files - Object files generated after compilation
#      .i files - Preprocessor files generated after preprocessing
#      .asm files - By using objdump utility human readable assembly \
#       files are generated
#       clean - Deletes all generated files
#       compile-all - Compiles the source code without linking
#       build - Builds the whole project
#
# Platform Overrides:
#      PLATFORM - Helps chose the target machine the project is being \
#      compiled for. By default the platform is set to MSP432.
#
#------------------------------------------------------------------------------
include sources.mk

# Platform Overrides
#Defualts to the host platform
#For MSP432 use "PLATFORM=MSP432"
#Eg.: make build PLATFORM=MSP432
PLATFORM = HOST 

# Architectures Specific Flags
LINKER_FILE = -T ./msp432p401r.lds 
CPU = cortex-m4
FPU = fpv4-sp-d16
ARCH = thumb
SPECS = nosys.specs

#Sets verbose option. Defualts to no.
#To use: VERBOSE=YES
#Eg.: make build PLATFORM=HOST VERBOSE=YES
VERBOSE = NO

#Final target file name
TARGET = COURSE1

# Compiler Flags and Defines
#Defaults to all the flags for the MSP432 platform
#unless host is speicified as the platform
ifeq ($(PLATFORM), HOST)
 CC = gcc 
 LDFLAGS = -Wl,-Map=$(TARGET).map -O0
 CFLAGS = -Wall -Werror -g -std=c99
 CPPFLAGS = -D$(PLATFORM) $(INCLUDES) -D$(TARGET) -MD
 OBJECTDUMP = objdump
 SIZE = size
else
 CC = arm-none-eabi-gcc
 LD = arm-none-eabi-ld
 LDFLAGS = -Wl,-Map=$(TARGET).map $(LINKER_FILE) -O0
    
 CFLAGS = -Wall -Werror -g -std=c99 -mcpu=$(CPU) \
 -m$(ARCH) -march=armv7e-m -mfloat-abi=hard \
 -mfpu=$(FPU) --specs=$(SPECS)
    
 CPPFLAGS = -D$(PLATFORM) $(INCLUDES) -D$(TARGET) -MD
 OBJECTDUMP = arm-none-eabi-objdump
 SIZE = arm-none-eabi-size
endif

ifeq ($(VERBOSE), YES)
 CPPFLAGS += -DVERBOSE
endif

#Goes through all the files ending in .c 
#in the sources list, takes their filename 
#and makes a .o file out of them. 
#Note to self: There must be no space after 
#the 'SOURCES' and between .c. There must also 
#be no spaces b/w .c,=,and .o
OBJS := $(SOURCES:.c=.o)

#The rule tells make that all files ending with
#.i depend on all .c files. Whatever .o file 
#is being generated needs an existing .c file
#with the same name as the .o file being generated.
#The recipe uses the specified compiler to generate 
#.i files by using the -E flag. The -E flag tells gcc to 
#stop after the preprocessing stage and to not run
#compiler proper. The output is in the form of .i files,
#preprocessed source code. Since only the preprocessor is
#run, only preprocessor flags are used to keep recipe simple.
%.i : %.c  
	$(CC) -E $(CPPFLAGS) $^ -o $@

#Tells make that all files ending with a .o
#are dependent on .i files. Whatever .o 
#file being generated needs an existing .i file
#with the same name as the .o file. 
#The recipe runs gcc till the compile or assemble
#stage with the use of the -c flag. The output is 
#in the form of .o files. Since .o files depend on
#.i files, make knows to run the previous rule/recipe
#automatically to generate said .i files to be used
#for this rule/recipe. Therefore this recipe can be
#run without any .i files existing and make will 
#automatically generate .i files based on the rules.
%.o : %.i 
	$(CC) -c $(CFLAGS) $^ -o $@

#Tells make .asm files can be dependent on .o files
#This rule allows the generation of .asm files
#based on .o files. E.g. if make main.asm is issued
#as a command. Make knows that main.c exists->.i depends on .c
#->.o depends on .i. It will run the whole chain to generate
#necessary intermediate files to make this rule work. This works
#because of the previous rule definitions.
#Uses the GNU Bin tool objdump. The -S flag intermixes source 
#code with assembly. -d flag disassembles sections which are
#expected to contain instructions. > operator tells objdump
#to take the input from the left side, process it, and put
#the result into the file on the right.
%.asm : %.o 
	$(OBJECTDUMP) -S -d $^ > $@

#Same thing as above expect takes files with .out
#extension as input. To generate assembly from final
#executable. The executable must exist for this 
#rule/recipe to be run because I did not create
#explicit rule chain for the .out file. Therefore
#build needs to be run before this rule can be used.
%.asm : %.out
	$(OBJECTDUMP) -S -d $^ > $@

#Phony rule to stop everything before the linking
#stage and after the compile stage. This is simple.
#The rule says that this command depends on all obj 
#files. So when this is run make generates all .o
#files by using the previously defined rule chain.
#This is possible because of the -c flag in the .o 
#rule. Which stops the build process after the 
#assembler stage and before linking.
.PHONY : compile-all
compile-all: $(OBJS)    

#Completely builds the project. The rule depends on
# .out file. If .out file does not exist then make
#runs the rule to generate a .out file. The recipe
#uses the appropriate size tool to print code size
#details after build is completed.
.PHONY : build
build: $(TARGET).out
	$(SIZE) $^

#.out is the target, which depends on all .o files.
#Make generates .o files and stores them in the same folder
#because of the OBJS variable defined above.
$(TARGET).out : $(OBJS)
	$(CC) $(CPPFLAGS) $(CFLAGS) $(LDFLAGS) $^ -o $@

#Simple clean rule. This rule was made to remove all
#generated files to clean up the folder a bit. It
#uses the built in CLI command rm with the file flag -f.
#The targets are all files with the extensions in the list.
.PHONY : clean
clean:
#	rm -f ./src/{*.o,*.i,*.asm,*.out,*.map,*.d} 
	find . -maxdepth 2 -name "*.o" -type f -delete
	find . -maxdepth 2 -name "*.i" -type f -delete
	find . -maxdepth 2 -name "*.asm" -type f -delete
	find . -maxdepth 2 -name "*.out" -type f -delete
	find . -maxdepth 2 -name "*.map" -type f -delete
	find . -maxdepth 2 -name "*.d" -type f -delete









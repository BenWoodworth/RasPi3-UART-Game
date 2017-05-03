SOURCE_FILES := $(wildcard source/*.c*) \
                $(wildcard source/*/*.c*) \
                $(wildcard source/*/*/*.c*) \
                $(wildcard source/*/*/*/*.c*)

DIR_INCLUDE := include/
DIR_BUILD := build/
DIR_OUTPUT := bin/

BASE_ARGS := $(SOURCE_FILES)
BASE_ARGS += -I $(DIR_INCLUDE)
BASE_ARGS += -Wall -Werror -pedantic -pedantic-errors
BASE_ARGS += -ffreestanding


## GCC ##
GCC_ARGS := $(BASE_ARGS)
GCC_ARGS += -o $(DIR_OUTPUT)gcc/game.exe
GCC_ARGS += -D INJECT_GCC


## RasPi3 ##	
RASPI3_LINKER := kernel_c.ld
RASPI3_BOOT := boot.s
			
RASPI3_ARGS := $(BASE_ARGS)
RASPI3_ARGS += -o $(DIR_OUTPUT)raspi3/kernel7.img
RASPI3_ARGS += -D INJECT_RASPI3
RASPI3_ARGS += -std=c++11

RASPI3_ARGS += -O2 -march=armv8-a -mtune=cortex-a53 -DPI2


## Targets ##
all: gcc raspi3

gcc:
	@echo Compiling with GCC...
	@g++ $(GCC_ARGS)

gcc-ben:
	@echo Compiling with GCC for C++11...
	@g++ $(GCC_ARGS) -std=c++11

gcc-dan:
	@echo Compiling with GCC for C++0x with ncurses...
	@g++ $(GCC_ARGS) -std=c++0x -lncurses

gcc-lab:
	@echo Compiling with GCC for C++0x...
	@g++ $(GCC_ARGS) -std=c++0x

raspi3:
	@echo Compiling for RasPi3...
	@arm-none-eabi-g++ $(RASPI3_ARGS)

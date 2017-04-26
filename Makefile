SOURCE_FILES := $(wildcard source/*.c*) \
                $(wildcard source/*/*.c*)
DIR_INCLUDE := include
DIR_BUILD := build
DIR_OUTPUT := bin

RASPI3_KERNEL := kernel_c.ld
RASPI3_BOOT := boot.s

GCC_ARGS := $(SOURCE_FILES) \
			-I $(DIR_INCLUDE) \
			-o $(DIR_OUTPUT)/gcc/game \
			-D INJECT_GCC \
			-Wall

all: gcc raspi3

gcc:
	@echo Compiling with GCC...
	@g++ $(GCC_ARGS)

gcc-0x:
	@echo Compiling with GCC for C++0x...
	@g++ $(GCC_ARGS) -std=c++0x

gcc-11:
	@echo Compiling with GCC for C++11...
	@g++ $(GCC_ARGS) -std=c++11

raspi3:
	@echo Compiling for RasPi3...
	@echo RasPi3 target not yet implemented!

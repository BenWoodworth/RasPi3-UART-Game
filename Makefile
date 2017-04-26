SOURCE_FILES := $(wildcard source/*.c*) \
                $(wildcard source/*/*.c*)
DIR_INCLUDE := include
DIR_BUILD := build
DIR_OUTPUT := bin

RASPI3_KERNEL := kernel_c.ld
RASPI3_BOOT := boot.s

all: gcc raspi3

gcc:
	@echo Compiling for GCC 11...

	@g++ $(SOURCE_FILES) \
	-I $(DIR_INCLUDE) \
	-o $(DIR_OUTPUT)/gcc/game.exe \
	-std=c++11 \
	-D INJECT_GCC

gcc-legacy:
	@echo Compiling for GCC 0X...

	@g++ $(SOURCE_FILES) \
	-I $(DIR_INCLUDE) \
	-o $(DIR_OUTPUT)/gcc/game.exe \
	-std=c++0X \
	-D INJECT_GCC

raspi3:
	@echo Compiling for RasPi3...
	@echo RasPi3 target not yet implemented!

SOURCE_CORE := $(wildcard source/*.c*)
SOURCE_CORE += $(wildcard source/core/*.c*)
SOURCE_CORE += $(wildcard source/core/*/*.c*)
SOURCE_CORE += $(wildcard source/core/*/*/*.c*)

SOURCE_GCC := $(SOURCE_CORE)
SOURCE_GCC += $(wildcard source/gcc/*.c*)
SOURCE_GCC += $(wildcard source/gcc/*/*.c*)
SOURCE_GCC += $(wildcard source/gcc/*/*/*.c*)

SOURCE_RASPI3 := $(SOURCE_CORE)
SOURCE_RASPI3 += $(wildcard source/raspi3/*.c*)
SOURCE_RASPI3 += $(wildcard source/raspi3/*/*.c*)
SOURCE_RASPI3 += $(wildcard source/raspi3/*/*/*.c*)

DIR_INCLUDE_CORE := include/core/
DIR_INCLUDE_GCC := include/raspi3/
DIR_INCLUDE_RASPI3 := include/raspi3/

DIR_OUTPUT := output/
DIR_OUTPUT_GCC := $(DIR_OUTPUT)gcc/
DIR_OUTPUT_RASPI3 := $(DIR_OUTPUT)raspi3/

GCC_ARGS := $(SOURCE_GCC)
GCC_ARGS += -I $(DIR_INCLUDE_CORE)
GCC_ARGS += -I $(DIR_INCLUDE_GCC)
GCC_ARGS += -o $(DIR_OUTPUT_GCC)game.exe
GCC_ARGS += -D INJECT_GCC
GCC_ARGS += -Wall

RASPI3_KERNEL := kernel_c.ld
RASPI3_BOOT := boot.s

all: gcc raspi3

gcc:
	@echo Compiling with GCC...
	@g++ $(GCC_ARGS)

gcc-ben:
	@echo Compiling with GCC for C++11...
	@g++ $(GCC_ARGS) -std=c++11

gcc-dan:
	@echo Compiling with GCC for C++0x, nothing else for now...
	@g++ $(GCC_ARGS) -std=c++0x

gcc-lab:
	@echo Compiling with GCC for C++0x...
	@echo (Make sure "C:\MinGW\bin" is in your PATH)
	@C:/MinGW/bin/g++ $(GCC_ARGS) -std=c++0x

raspi3:
	@echo Compiling for RasPi3...
	@echo RasPi3 target not yet implemented!

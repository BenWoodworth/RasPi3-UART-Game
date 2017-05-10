SOURCE_CORE := $(wildcard source/*.c*)
SOURCE_CORE += $(wildcard source/core/*.c*)
SOURCE_CORE += $(wildcard source/core/*/*.c*)
SOURCE_CORE += $(wildcard source/core/*/*/*.c*)

SOURCE_GCC := $(SOURCE_CORE)
SOURCE_GCC += $(wildcard source/gcc/*.c*)
SOURCE_GCC += $(wildcard source/gcc/*/*.c*)
SOURCE_GCC += $(wildcard source/gcc/*/*/*.c*)

SOURCE_PI3 := $(SOURCE_CORE)
SOURCE_PI3 += $(wildcard source/pi3/*.c*)
SOURCE_PI3 += $(wildcard source/pi3/*/*.c*)
SOURCE_PI3 += $(wildcard source/pi3/*/*/*.c*)

DIR_OUTPUT := bin/
DIR_OUTPUT_GCC := $(DIR_OUTPUT)gcc/
DIR_OUTPUT_PI3 := $(DIR_OUTPUT)pi3/

DIR_INCLUDE := include/

BASE_FLAGS := -I $(DIR_INCLUDE)
BASE_FLAGS += -Wall -Werror -pedantic -pedantic-errors
BASE_FLAGS += -ffreestanding


## GCC Args ##
GCC_ARGS := $(BASE_FLAGS)
GCC_ARGS += $(SOURCE_GCC)
GCC_ARGS += -o $(DIR_OUTPUT_GCC)game.exe
GCC_ARGS += -D INJECT_GCC


## Pi3 Args ##	
PI3_LINKER := source/pi3/kernel_c.ld
PI3_BOOT := source/pi3/boot.s

PI3_ARGS := $(BASE_FLAGS)
PI3_ARGS += $(SOURCE_PI3)
PI3_ARGS += -o $(DIR_OUTPUT_PI3)game
PI3_ARGS += -D INJECT_PI3


## Targets ##
all: gcc pi3

gcc:
	@echo Compiling with GCC...
	@g++ $(GCC_ARGS)

gcc-ben:
	@echo Compiling with GCC for C++11...
	@g++ $(GCC_ARGS) -std=c++11

gcc-ben-pi3:
	@echo Compiling with GCC for PI3 C++0x...
	@g++ $(PI3_ARGS) -std=c++0x

gcc-dan:
	@echo Compiling with GCC for C++0x, nothing else for now...
	@g++ $(GCC_ARGS) -std=c++0x

gcc-lab:
	@echo Compiling with GCC for C++0x...
	@echo (Make sure "C:\MinGW\bin" is in your PATH)
	@C:/MinGW/bin/g++ $(GCC_ARGS) -std=c++0x

pi3:
	@echo Compiling for Pi3...
	@arm-none-eabi-g++ $(PI3_ARGS)

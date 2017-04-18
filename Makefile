SOURCE_FILES := $(wildcard source/*.c*) $(wildcard source/*/*.c*)
DIR_INCLUDE := include
DIR_BUILD := build
DIR_OUTPUT := bin

RASPI3_KERNEL := kernel_c.ld
RASPI3_BOOT := boot.s

gcc:
	@g++ $(SOURCE_FILES) \
	-I $(DIR_INCLUDE) \
	-o $(DIR_OUTPUT)/gcc/game.exe \
	-D INJECT_GCC

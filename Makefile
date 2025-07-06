#------------------------------
# Directories
#------------------------------
TOOLS_DIR := /home/terence/dev/tools
MSPGCC_ROOT_DIR := $(TOOLS_DIR)/msp430-gcc
MSPGCC_BIN_DIR := $(MSPGCC_ROOT_DIR)/bin
MSPGCC_INCLUDE_DIR := $(MSPGCC_ROOT_DIR)/include

BUILD_DIR := build/output
OBJ_DIR := $(BUILD_DIR)/obj
BIN_DIR := $(BUILD_DIR)/bin

TI_CCS_DIR := $(TOOLS_DIR)/ccs2020/ccs
DEBUG_BIN_DIR := $(TI_CCS_DIR)/ccs_base/DebugServer/bin
DEBUG_DRIVERS_DIR := $(TI_CCS_DIR)/ccs_base/DebugServer/drivers

#------------------------------
# Toolchain & Tools
#------------------------------
CC := $(MSPGCC_BIN_DIR)/msp430-elf-gcc
RM := rm -rf
DEBUG := LD_LIBRARY_PATH=$(DEBUG_DRIVERS_DIR) $(DEBUG_BIN_DIR)/mspdebug
CPPCHECK := cppcheck
FORMAT := clang-format
SIZE = $(MSPGCC_BIN_DIR)/msp430-elf-size

#------------------------------
# Files & Sources
#------------------------------
TARGET := $(BIN_DIR)/output.elf

SOURCES := \
  src/main.c \
  src/drivers/led.c \
  src/drivers/mcu_init.c \
	src/drivers/isr.c \
	src/common/assert_handler.c 

OBJECT_NAMES := $(notdir $(SOURCES:.c=.o))
OBJECTS := $(patsubst %,$(OBJ_DIR)/%,$(OBJECT_NAMES))

vpath %.c src src/drivers src/common

#------------------------------
# Preprocessor Defines
#------------------------------
DEFINES :=

#------------------------------
# Compilation Flags
#------------------------------
MCU := msp430g2553
WFLAGS := -Wall -Wextra -Werror -Wshadow
CFLAGS := -mmcu=$(MCU) $(WFLAGS) -fshort-enums -I$(MSPGCC_INCLUDE_DIR) $(DEFINES) -Isrc -Og -g
LDFLAGS := -mmcu=$(MCU) $(DEFINES) -L$(MSPGCC_INCLUDE_DIR)

#------------------------------
# Default Target
#------------------------------
all: $(TARGET)

#------------------------------
# Link Target
#------------------------------
$(TARGET): $(OBJECTS)
	@mkdir -p $(dir $@)
	$(CC) $(LDFLAGS) $^ -o $@

#------------------------------
# Compile Objects
#------------------------------
$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

#------------------------------
# Utility Targets
#------------------------------
.PHONY: all clean flash cppcheck format

clean:
	$(RM) $(BUILD_DIR)

flash: $(TARGET)
	$(DEBUG) tilib "prog $(TARGET)"

cppcheck:
	$(CPPCHECK) $(SOURCES)

format:
	$(FORMAT) -i $(SOURCES)

size: $(TARGET)
	@$(SIZE) $(TARGET)


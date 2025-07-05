# Directories

TOOLS_DIR = /home/terence/dev/tools
MSPGCC_ROOT_DIR = $(TOOLS_DIR)/msp430-gcc
MSPGCC_BIN_DIR = $(MSPGCC_ROOT_DIR)/bin
MSPGCC_INCLUDE_DIR = $(MSPGCC_ROOT_DIR)/include
INCLUDE_DIRS = $(MSPGCC_INCLUDE_DIR)
LIB_DIRS = $(MSPGCC_INCLUDE_DIR)

BUILD_DIR = build
OBJ_DIR = $(BUILD_DIR)/obj
BIN_DIR = $(BUILD_DIR)/bin

# Toolchain 
CC = $(MSPGCC_BIN_DIR)/msp430-elf-gcc
RM = rm -rf

# Full path to mspdebug with rf2500 backend
DEBUG_BIN_DIR = $(TOOLS_DIR)/ccs2020/ccs/ccs_base/DebugServer/bin
DEBUG_DRIVERS_DIR = $(TOOLS_DIR)/ccs2020/ccs/ccs_base/DebugServer/drivers
DEBUG = LD_LIBRARY_PATH=$(DEBUG_DRIVERS_DIR) $(DEBUG_BIN_DIR)/mspdebug

# MCU & FLAGS
MCU = msp430g2553
WFLAGS = -Wall -Wextra -Werror -Wshadow
CFLAGS = -mmcu=$(MCU) $(WFLAGS) $(addprefix -I,$(INCLUDE_DIRS)) -Og -g
LDFLAGS = -mmcu=$(MCU) $(addprefix -L,$(LIB_DIRS))

# FILES
TARGET = $(BIN_DIR)/output
SOURCES = main.c test.c
OBJECT_NAMES = $(SOURCES:.c=.o)
OBJECTS = $(patsubst %,$(OBJ_DIR)/%,$(OBJECT_NAMES))

# Build rules
$(TARGET): $(OBJECTS)
	@mkdir -p $(dir $@)
	$(CC) $(LDFLAGS) $^ -o $@

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c -o $@ $<

# Phonies
.PHONY: all clean flash

all: $(TARGET)

clean:
	$(RM) $(BUILD_DIR)

flash: $(TARGET)
	$(DEBUG) tilib "prog $(TARGET)"



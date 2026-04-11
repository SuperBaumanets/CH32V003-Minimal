# target
TARGET = firmware

#######################################
# paths
#######################################
# Build path
BUILD_DIR = build

# Out files
BUILD_ELF = $(BUILD_DIR)/$(TARGET).elf
BUILD_BIN = $(BUILD_DIR)/$(TARGET).bin
BUILD_DUMP = $(BUILD_DIR)/$(TARGET).elf.dump
BUILD_MAP = $(BUILD_DIR)/$(TARGET).map

######################################
# source
######################################
# C sources
C_SOURCES =  \
src/main.c 

# ASM sources
ASM_SOURCES =  \
startup.S

# binaries
PREFIX = riscv64-elf-
CC = $(PREFIX)gcc
CP = $(PREFIX)objcopy
DP = $(PREFIX)objdump
BIN = $(CP) -O binary -S 
DUMP = $(DP) -S -d -h

# programmer
PROGRAMMER = wlink

#######################################
# CFLAGS
#######################################
# arch
ARCH = -march=rv32emc

# abi
ABI = -mabi=ilp32e

# compile gcc flags
CFLAGS = $(ARCH) $(ABI) -nostdlib -g

CFLAGS += -Iinclude -Os -Wall -Wextra

#######################################
# LDFLAGS
#######################################
# link script
LDSCRIPT = ch32v003f4p6.ld

LIBS = -nostdlib 

LDFLAGS = $(ARCH) $(ABI) -T $(LDSCRIPT) -nostartfiles $(LIBS) -Wl,-Map=$(BUILD_MAP)

#######################################
# build the application
#######################################
# list of С
OBJECTS = $(addprefix $(BUILD_DIR)/,$(notdir $(C_SOURCES:.c=.o)))
vpath %.c $(sort $(dir $(C_SOURCES)))
# list of ASM 
OBJECTS += $(addprefix $(BUILD_DIR)/,$(notdir $(ASM_SOURCES:.S=.o)))
vpath %.s $(sort $(dir $(ASM_SOURCES)))

$(BUILD_DIR)/%.o: %.c | $(BUILD_DIR) 
	$(CC) -c $(CFLAGS) $< -o $@

$(BUILD_DIR)/%.o: %.S | $(BUILD_DIR)
	$(CC) -c $(CFLAGS) $< -o $@


$(BUILD_ELF): $(OBJECTS)
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@
	
$(BUILD_BIN): $(BUILD_ELF) | $(BUILD_DIR)
	$(BIN) $< $@

$(BUILD_DUMP): $(BUILD_ELF) | $(BUILD_DIR)
	$(DUMP) $(BUILD_ELF) > $(BUILD_DUMP)
	
# Create build directory
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Default target
all: $(BUILD_BIN) $(BUILD_DUMP)

#######################################
# program
#######################################
# Flash to device
flash: $(BUILD_BIN)
	$(PROGRAMMER) flash $< --address 0x08000000

#######################################
# clean up
#######################################
clean:
	rm -rf $(BUILD_DIR)

.PHONY: all flash clean
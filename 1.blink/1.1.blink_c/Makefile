# Tools
CC = riscv64-elf-gcc
OBJCOPY = riscv64-elf-objcopy
OBJDUMP = riscv64-elf-objdump
FLASH = wlink

# Flags
ARCH = rv32emc
ABI = ilp32e
CFLAGS = -march=$(ARCH) -mabi=$(ABI) -nostdlib -g
CFLAGS += -Iinclude -Os -Wall -Wextra
LDFLAGS = -T lib/ch32v003f4p6.ld -nostartfiles -Wl,-Map=$(BUILD_DIR)/$(TARGET).map

# Files and directories
TARGET = firmware
SRC_DIR = src
BUILD_DIR = build

# Output files
ELF = $(BUILD_DIR)/$(TARGET).elf
BIN = $(BUILD_DIR)/$(TARGET).bin
DUMP = $(BUILD_DIR)/$(TARGET).elf.dump
MAP = $(BUILD_DIR)/$(TARGET).map

# Default target
all: $(BIN) $(MAP)

# Create build directory
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Build firmware directly from main.c
$(BIN) $(MAP): $(SRC_DIR)/main.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $(ELF) $<
	$(OBJCOPY) -O binary $(ELF) $@
	$(OBJDUMP) -S -d -h $(ELF) > $(DUMP)

# Flash to device
flash: $(BIN)
	$(FLASH) flash $< --address 0x08000000

# Clean build artifacts and remove build directory
clean:
	rm -rf $(BUILD_DIR)

.PHONY: all flash clean
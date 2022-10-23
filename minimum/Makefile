TOOLCHAIN_PREFIX=arm-none-eabi-
CC=$(TOOLCHAIN_PREFIX)gcc
OBJCOPY=$(TOOLCHAIN_PREFIX)objcopy
OBJDUMP=$(TOOLCHAIN_PREFIX)objdump

PROJECT=blinky
BUILD_DIR=build

LINKER_SCRIPT=flash.ld

CPPFLAGS=
CFLAGS=-Wall \
       -mcpu=cortex-m4 \
       -mthumb \
       -ggdb3 \
       -std=c11 \
       -ffreestanding \
       -ffunction-sections \
       -fdata-sections

LDFLAGS=-nostartfiles \
	-T $(LINKER_SCRIPT) \
	-Wl,-Map=$(BUILD_DIR)/$(PROJECT).map \
	-Wl,--gc-sections

SOURCES = main.c startup.c
OBJECTS = $(addprefix $(BUILD_DIR)/, $(SOURCES:.c=.o))

$(info OBJECTS = $(OBJECTS))
VPATH = src/

$(BUILD_DIR)/$(PROJECT): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@
	$(OBJDUMP) -DS $@ > $@.lst
	$(OBJCOPY) -O binary $@ $@.bin

$(BUILD_DIR)/%.o: %.c | $(BUILD_DIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

$(BUILD_DIR):
	mkdir $(BUILD_DIR)

clean:
	-rm $(BUILD_DIR)/* >/dev/null 2>&1


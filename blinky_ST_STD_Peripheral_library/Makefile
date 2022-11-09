
TOOLCHAINi_PREFIX=arm-none-eabi-
CC=$(TOOLCHAINi_PREFIX)gcc
LD=$(CC)
OBJCOPY=$(TOOLCHAINi_PREFIX)objcopy
OBJDUMP=$(TOOLCHAINi_PREFIX)objdump

PROJECT=blinky
BUILD_DIR=build

ST_STD_PERIPH_LIB = lib/STM32F4xx_StdPeriph_Driver
CMSIS_PATH = lib/CMSIS

LINKER_SCRIPT = startup/flash.ld

SOURCES = src/main.c startup/startup.c
SOURCES += $(addprefix $(ST_STD_PERIPH_LIB)/src/, \
	   stm32f4xx_gpio.c \
	   stm32f4xx_rcc.c \
	   stm32f4xx_usart.c \
	   )

#$(info SOURCES=$(SOURCES))
OBJECTS = $(SOURCES:.c=.o)
$(info OBJECTS = $(OBJECTS))

CFLAGS=-Wall \
       -mcpu=cortex-m4 \
       -mthumb \
       -ggdb3 \
       -std=c11 \
       -ffunction-sections \
       -fdata-sections

LDFLAGS=-nostartfiles \
        -T $(LINKER_SCRIPT) \
        -Wl,-Map=$(BUILD_DIR)/$(PROJECT).map \
	-Wl,--start-group -lc -lm -Wl,--end-group


CPPFLAGS += -Iinclude -I$(CMSIS_PATH)/Include/ -I$(CMSIS_PATH)/Device/ST/STM32F4xx/Include/ -I$(ST_STD_PERIPH_LIB)/inc/ -I.
CPPFLAGS += -DSTM32F40_41xxx -DUSE_STDPERIPH_DRIVER -DHSE_VALUE=8000000

#LDFLAGS = -T$(LINKER_SCRIPT) -nostartfiles -Wl,-Map="$(TARGET).map" -mthumb -Wl,--start-group -lc -lm -Wl,--end-group

all: $(BUILD_DIR)/$(PROJECT)

$(BUILD_DIR)/$(PROJECT): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@
	$(OBJDUMP) -DS $@ > $@.lst
	$(OBJCOPY) -O binary $@ $@.bin

%.o: %.c | $(BUILD_DIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

$(BUILD_DIR):
	mkdir $(BUILD_DIR)

clean:
	-rm $(BUILD_DIR)/* $(OBJECTS) >/dev/null 2>&1


.PRECIOUS: %.o


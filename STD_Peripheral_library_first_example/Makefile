TOOLCHAIN_PREFIX=arm-none-eabi-
CC=$(TOOLCHAIN_PREFIX)gcc
OBJCOPY=$(TOOLCHAIN_PREFIX)objcopy
OBJDUMP=$(TOOLCHAIN_PREFIX)objdump

ST_STD_PERIPH = ../lib/STM32F4xx_StdPeriph_Driver
CMSIS = ../lib/CMSIS

PROJECT=blinky
BUILD_DIR=build

LINKER_SCRIPT=startup/flash.ld

SOURCES = src/main.c \
	  src/syscalls.c \
	  startup/startup.c

SOURCES += $(addprefix $(ST_STD_PERIPH)/src/, \
	   stm32f4xx_gpio.c \
	   stm32f4xx_rcc.c \
	   stm32f4xx_usart.c \
	   )

OBJECTS = $(SOURCES:.c=.o)

CFLAGS=-Wall \
       -mcpu=cortex-m4 \
       -mthumb \
       -ggdb3 \
       -std=c11 \
       -ffreestanding \
       -ffunction-sections \
       -fdata-sections

CPPFLAGS= -Iinclude \
	  -I$(CMSIS)/Include/ \
	  -I$(CMSIS)/Device/ST/STM32F4xx/Include/ \
	  -I$(ST_STD_PERIPH)/inc/ \

CPPFLAGS += -DSTM32F40_41xxx -DUSE_STDPERIPH_DRIVER
LDFLAGS=-nostartfiles \
	-T $(LINKER_SCRIPT) \
	-Wl,-Map=$(BUILD_DIR)/$(PROJECT).map \
	-Wl,--gc-sections


$(info OBJECTS = $(OBJECTS))

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


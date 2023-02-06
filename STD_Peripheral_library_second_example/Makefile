TOOLCHAIN_PREFIX=arm-none-eabi-
CC=$(TOOLCHAIN_PREFIX)gcc
OBJCOPY=$(TOOLCHAIN_PREFIX)objcopy
OBJDUMP=$(TOOLCHAIN_PREFIX)objdump

ST_STD_PERIPH = ../lib/STM32F4xx_StdPeriph_Driver
CMSIS = ../lib/CMSIS

PROJECT=read
BUILD_DIR=build

LINKER_SCRIPT=startup/flash.ld

SOURCES = src/main.c \
		  src/syscalls.c \
		  src/system_stm32f4xx.c \
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

CPPFLAGS=-Iinclude \
		 -I$(CMSIS)/Include/ \
		 -I$(CMSIS)/Device/ST/STM32F4xx/Include/ \
		 -I$(ST_STD_PERIPH)/inc/ \

CPPFLAGS += -DSTM32F40_41xxx -DUSE_STDPERIPH_DRIVER -DHSE_VALUE=8000000

LDFLAGS=-nostartfiles \
        -mcpu=cortex-m4 \
       	-mthumb \
		-T $(LINKER_SCRIPT) \
		-Wl,-Map=$(BUILD_DIR)/$(PROJECT).map \
		-Wl,--gc-sections

DEPFILES = $(OBJECTS:%.o=%.d)

all: $(BUILD_DIR)/$(PROJECT)

$(BUILD_DIR)/$(PROJECT): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@
	$(OBJDUMP) -DS $@ > $@.lst
	$(OBJCOPY) -O binary $@ $@.bin

%.o: %.c | $(BUILD_DIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) -MD -MP -MF $*.d -c $< -o $@

$(BUILD_DIR):
	mkdir $(BUILD_DIR)

clean: clean_dependencies
	-rm $(BUILD_DIR)/* $(OBJECTS) >/dev/null 2>&1

clean_dependencies:
	-rm $(DEPFILES)

-include $(DEPFILES)

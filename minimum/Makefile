
TOOLCHAINi_PREFIX=arm-none-eabi-
CC=$(TOOLCHAINi_PREFIX)gcc
LD=$(CC)
OBJCOPY=$(TOOLCHAINi_PREFIX)objcopy
OBJDUMP=$(TOOLCHAINi_PREFIX)objdump

ST_STD_PERIPH_LIB = ../lib/STM32F4xx_StdPeriph_Driver
CMSIS_PATH = ../lib/CMSIS

TARGET=main

SOURCES = main.c startup.c
SOURCES += $(addprefix $(ST_STD_PERIPH_LIB)/src/, \
	   stm32f4xx_gpio.c \
	   stm32f4xx_rcc.c \
	   )

$(info SOURCES=$(SOURCES))
OBJECTS = $(SOURCES:.c=.o)


CFLAGS = -Wall -g -mcpu=cortex-m4 -mthumb -O0
#CFLAGS = -Wall -g -mcpu=cortex-m4 --specs=nano.specs -mthumb -O0
CFLAGS += -I$(CMSIS_PATH)/Include/ -I$(CMSIS_PATH)/Device/ST/STM32F4xx/Include/ -I$(ST_STD_PERIPH_LIB)/inc/ -I.
CFLAGS += -DSTM32F40_41xxx -DUSE_STDPERIPH_DRIVER -DHSE_VALUE=8000000

LINKER_SCRIPT = flash.ld
LDFLAGS = -T$(LINKER_SCRIPT) -nostartfiles -mcpu=cortex-m7 -Wl,-Map="$(TARGET).map" --specs=nano.specs -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
#LDFLAGS = -T$(LINKER_SCRIPT) -nostartfiles -mcpu=cortex-m7 --specs=nosys.specs -Wl,-Map="$(TARGET).map" --specs=nano.specs -mthumb -Wl,--start-group -lc -lm -Wl,--end-group

all: $(TARGET).elf $(TARGET).bin $(TARGET).diss

%.bin: %.elf
	$(OBJCOPY) -O binary $< $@

%.diss: %.elf
	$(OBJDUMP) -D $< > $@

%.elf: $(OBJECTS)
	$(LD) $(LDFLAGS) -o $@ $(OBJECTS)

%.o: %.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -c -o $@ $<

clean:
	-rm -rf $(TARGET).elf $(TARGET).bin $(TARGET).map $(TARGET).diss $(OBJECTS)

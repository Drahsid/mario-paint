BASENAME  = mario-paint

BUILD_DIR = build
ASM_DIRS  = asm
BIN_DIRS  = assets
SRC_DIR   = src
SRC_DIRS  = $(SRC_DIR)
TOOLS_DIR = tools
ASM_PROCESSOR_DIR := $(TOOLS_DIR)/asm-processor

S_FILES   = $(foreach dir,$(ASM_DIRS),$(wildcard $(dir)/*.s))
C_FILES   = $(foreach dir,$(SRC_DIRS),$(wildcard $(dir)/*.c))
BIN_FILES = $(foreach dir,$(BIN_DIRS),$(wildcard $(dir)/*.bin))
O_FILES = $(foreach file,$(S_FILES),$(BUILD_DIR)/$(file).o) \
           $(foreach file,$(C_FILES),$(BUILD_DIR)/$(file).o) \
           $(foreach file,$(BIN_FILES),$(BUILD_DIR)/$(file).o)


TARGET = $(BUILD_DIR)/$(BASENAME)
LD_SCRIPT = $(BASENAME).ld

CROSS = mips-linux-gnu-
AS = $(CROSS)as
CPP = cpp
LD = $(CROSS)ld
OBJDUMP = $(CROSS)objdump
OBJCOPY = $(CROSS)objcopy
PYTHON = python3
CC = $(TOOLS_DIR)/ido_recomp/linux/7.1/cc

OPT_FLAGS = -O2
MIPSISET = -mips2 -o32
INCLUDE_CFLAGS = -I . -I include
ASFLAGS = -EB -mtune=vr4300 -march=vr4300 -mabi=32 -I include
OBJCOPYFLAGS = -O binary

# Files requiring pre/post-processing
GREP := grep -rl
GLOBAL_ASM_C_FILES := $(shell $(GREP) GLOBAL_ASM $(SRC_DIR) </dev/null 2>/dev/null)
GLOBAL_ASM_O_FILES := $(foreach file,$(GLOBAL_ASM_C_FILES),$(BUILD_DIR)/$(file).o)

CFLAGS = -G0 -Xfullwarn -Xcpluscomm -signed -nostdinc -non_shared -Wab,-r4300_mul
CFLAGS += -D_LANGUAGE_C -D_FINALROM -DF3DEX_GBI -DWIN32
# ignore compiler warnings about anonymous structs
CFLAGS += -woff 649,838
CFLAGS += $(INCLUDE_CFLAGS)
CC_CHECK = gcc -fsyntax-only -fsigned-char -m32 -std=gnu99 -Wall -Wextra -Wno-format-security -Wno-unknown-pragmas -Wno-main -DAVOID_UB -D_LANGUAGE_C -D_FINALROM -DF3DEX_GBI -DWIN32 $(INCLUDE_CFLAGS)

LDFLAGS = -T $(LD_SCRIPT) -Map $(TARGET).map -T undefined_syms_auto.txt -T undefined_funcs_auto.txt -T undefined_funcs.txt -T undefined_syms.txt --no-check-sections

### Targets

default: all

all: dirs $(TARGET).z64dd check

check: $(TARGET).z64dd
	sha1sum $<
	sha1sum --check checksum.sha1

dirs:
	$(foreach dir,$(SRC_DIRS) $(ASM_DIRS) $(BIN_DIRS),$(shell mkdir -p $(BUILD_DIR)/$(dir)))

nuke:
	rm -rf asm
	rm -rf assets
	rm -rf build
	rm -f *auto.txt

context:
	rm -f ctx.c ctx_includes.c
	find include/ src/ -type f -name "*.h" | sed -e 's/.*/#include "\0"/' > ctx_includes.c
	$(PYTHON) tools/m2ctx.py ctx_includes.c

clean:
	rm -rf build

extract_rom:
	$(PYTHON) $(TOOLS_DIR)/extract_ndd.py $(TARGET).ndd $(TARGET).z64dd

setup:
	$(PYTHON) $(TOOLS_DIR)/splat/split.py $(BASENAME).yaml

### Recipes

$(TARGET).elf: $(O_FILES)
	@$(LD) $(LDFLAGS) -o $@

$(GLOBAL_ASM_O_FILES): $(BUILD_DIR)/%.c.o: %.c
	$(PYTHON) $(ASM_PROCESSOR_DIR)/asm_processor.py $(OPT_FLAGS) $< > $(BUILD_DIR)/$<
	@$(CC_CHECK) -MMD -MP -MT $@ -MF $(BUILD_DIR)/$*.d $<
	$(CC) -c -32 $(CFLAGS) $(OPT_FLAGS) $(MIPSISET) -o $@ $(BUILD_DIR)/$<
	$(PYTHON) $(ASM_PROCESSOR_DIR)/asm_processor.py $(OPT_FLAGS) $< --post-process $@ --assembler "$(AS) $(ASFLAGS)" --asm-prelude $(ASM_PROCESSOR_DIR)/prelude.inc

$(BUILD_DIR)/%.c.o: %.c
	@$(CC_CHECK) -MMD -MP -MT $@ -MF $(BUILD_DIR)/$*.d $<
	$(CC) -c $(CFLAGS) $(OPT_FLAGS) $(MIPSISET) -o $@ $<

$(BUILD_DIR)/%.s.o: %.s
	$(AS) $(ASFLAGS) -o $@ $<

$(BUILD_DIR)/%.bin.o: %.bin
	$(LD) -r -b binary -o $@ $<

$(TARGET).z64dd: $(TARGET).elf
	$(OBJCOPY) $(OBJCOPYFLAGS) $< $@

### Settings
.SECONDARY:
.PHONY: all clean default
SHELL = /bin/bash -e -o pipefail

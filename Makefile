SRC = src
ASM = asm
OBJ = obj
INC = include
LIB = lib
BIN = bin

CC = aarch64-linux-gnu

LDFLAGS = -T link/linker.ld

ASMFLAGS = -I$(INC)

CFLAGS = -nostartfiles
CFLAGS += -ffreestanding
CFLAGS += -O0
CFLAGS += -nostdlib
CFLAGS += -lgcc
CFLAGS += -Wall
CFLAGS += -I$(INC)

src_files = $(wildcard $(SRC)/*.c)
asm_files = $(wildcard $(ASM)/*.S)

TARGET = $(BIN)/kernel8.img
TARGET_ELF = $(BIN)/kernel8.elf

all:$(TARGET)

clean:
	rm -rf $(OBJ)/*.o
	rm -rf $(OBJ)/*.d
	rm $(BIN)/kernel8.elf
	rm $(BIN)/kernel8.img

$(OBJ)/%_c.o: $(SRC)/%.c
	$(CC)-gcc $(CFLAGS) -MMD -c $< -o $@

$(OBJ)/%_s.o: $(ASM)/%.S
	$(CC)-gcc $(ASMFLAGS) -MMD -c $< -o $@


OBJ_FILES = $(src_files:$(SRC)/%.c=$(OBJ)/%_c.o)
OBJ_FILES += $(asm_files:$(ASM)/%.S=$(OBJ)/%_s.o)

DEP_FILES = $(OBJ_FILES:%.o=%.d)
-include $(DEP_FILES)

$(TARGET_ELF):$(OBJ_FILES)
	$(CC)-ld $(LDFLAGS) -o $@ $^

$(TARGET):$(TARGET_ELF)
	$(CC)-objcopy $< -O binary $(TARGET)

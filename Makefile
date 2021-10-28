rwildcard =  $(foreach d,$(wildcard $1*),$(call rwildcard,$d/,$2) $(filter $(subst *,%,$2),$d))
ASM := rgbasm
LINKER := rgblink
FIX := rgbfix
BGB := ~/sources/bgb/bgb.exe
BUILD_DIR := build
PROJECT_NAME ?= metallurgic-nightshades
OUTPUT := $(BUILD_DIR)/$(PROJECT_NAME)
SRC_DIR := src
INC_DIR := include/
SRC_ASM := $(call rwildcard, $(SRC_DIR)/, *.s)
OBJ_FILES := $(addprefix $(BUILD_DIR)/obj/, $(SRC_ASM:src/%.s=%.o))
OBJ_DIRS := $(addprefix $(BUILD_DIR)/obj/, $(dir $(SRC_ASM:src/%.s=%.o)))
ASMFLAGS := -p0 -v -i $(INC_DIR)
LINKERFLAGS := -m $(OUTPUT).map -n $(OUTPUT).sym -d
FIXFLAGS := -v -p0

.PHONY: all run clean

all: fix

run:
	wine $(BGB) $(OUTPUT).gb
	    
fix: build
	$(FIX) $(FIXFLAGS) $(OUTPUT).gb

build: $(OBJ_FILES)
	$(LINKER) -o $(OUTPUT).gb $(LINKERFLAGS) $(OBJ_FILES)
		 
$(BUILD_DIR)/obj/%.o : src/%.s | $(OBJ_DIRS)
	$(ASM) -o $@ $(ASMFLAGS) $<

$(OBJ_DIRS): 
	mkdir -p $@

clean:
	rm -rf $(BUILD_DIR)

print-%  : ; @echo $* = $($*)

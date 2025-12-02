EXE := day1

CC := clang
CFLAGS := -std=c99 -W -Wall -Wpedantic -Wno-comment -Wcomma -Wdeclaration-after-statement -Wdocumentation -Wdocumentation-pedantic -Wdouble-promotion -Wempty-translation-unit -Wflexible-array-extensions -Wfloat-conversion -Wfloat-equal -Wfor-loop-analysis -Wformat-non-iso -Wformat-pedantic -Wgcc-compat -Wimplicit -Winfinite-recursion -Wnewline-eof -Wpadded -Wpoison-system-directories -Wstring-concatenation -Wswitch-enum -Wunaligned-access -Wuninitialized -Wunreachable-code-aggressive -Wunused-label -Wvariadic-macros -Wvla
CPPFLAGS = -MMD -MP -I $(INCLUDE_DIR)
LDFLAGS = -lnori -L $(LIBRARY_DIR)

SANFLAGS := -fsanitize=address,undefined
MAKEFLAGS := --no-print-directory

SRC_DIR := src
BUILD_DIR := .build
INCLUDE_DIR := include
LIBRARY_DIR := lib

SRC = $(wildcard $(SRC_DIR)/*.c)
OBJ = $(SRC:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)
DEP = $(OBJ:%.o=%.d)

all: debug

$(EXE): $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(@D)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<

-include $(DEP)

clean:
	rm -f $(OBJ) $(DEP)

fclean: clean
	rm -f $(EXE)

debug: CFLAGS += -g3 $(SANFLAGS)
debug: LDFLAGS += $(SANFLAGS)
debug: $(EXE)

release: CFLAGS += -O2 -DNDEBUG
release: fclean $(EXE)

.PHONY: clean fclean test
.SILENT:

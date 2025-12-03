EXE := day2

CC := gcc
CFLAGS := -std=c99 -Wc90-c99-compat -Wleading-whitespace=spaces -Wall -Wextra -Wpedantic -Wdouble-promotion -Wformat -Wformat-overflow=2 -Wformat-truncation=2 -Wformat-signedness -Wnull-dereference -Wstrict-overflow=4 -Wtrailing-whitespace -Wfloat-equal -Wshadow -Wunsafe-loop-optimizations -Wcast-qual -Wconversion -Wstrict-prototypes -Wold-style-definition -Wdeprecated-non-prototype -Wmissing-parameter-name -Wmissing-prototypes -Wmissing-variable-declarations -Wpadded -Wredundant-decls -Wvla -Wflex-array-member-not-at-end
CPPFLAGS = -MMD -MP -I $(INCLUDE_DIR)
LDFLAGS = -lm -lnori -L $(LIBRARY_DIR)

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

debug: CFLAGS += -g3 -Og $(SANFLAGS)
debug: LDFLAGS += $(SANFLAGS)
debug: $(EXE)

release: CFLAGS += -O2 -DNDEBUG
release: fclean $(EXE)

.PHONY: clean fclean test
# .SILENT:

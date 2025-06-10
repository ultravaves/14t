CC = gcc
CFLAGS = -Wall -Wextra -Werror -fsanitize=address -fsanitize=leak -fsanitize=undefined \
         -fsanitize=unreachable -pedantic -std=c11
SRC1 = state_sort.c
SRC2 = state_search.c
SRC3 = clear_state.c

OBJ1 = $(patsubst %.c,%.o,$(SRC1))
OBJ2 = $(patsubst %.c,%.o,$(SRC2))
OBJ3 = $(patsubst %.c,%.o,$(SRC3))

BUILD = ../build

Q1 = $(BUILD)/Quest_1
Q2 = $(BUILD)/Quest_2
Q3 = $(BUILD)/Quest_3

.PHONY: all clean rebuild clean_all state_sort state_search clear_state

all: state_sort state_search clear_state

state_sort: $(Q1)
$(Q1): $(OBJ1)
	$(CC) $(CFLAGS) $^ -o $@

state_search: $(Q2)
$(Q2): $(OBJ2)
	$(CC) $(CFLAGS) $^ -o $@

clear_state:  $(Q3)
$(Q3): $(OBJ3)
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -f *.o

clean_all: clean
	rm -rf $(BUILD)/*

rebuild: clean all
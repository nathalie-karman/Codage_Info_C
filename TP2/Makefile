CC	= gcc
CFLAGS	= -Wall -g
LINKER	= gcc
LFLAGS	= -Wall -lm

SRC	= $(wildcard *.c)
OBJ	= $(SRC:.c=.o)
EXEC	= prog

all: $(EXEC)

prog: $(OBJ)
	$(LINKER) $^ -o $@ $(LFLAGS)

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)

# Nettoyage

.PHONY: clean
clean:
	rm *.o

.PHONY: remove
remove: clean
	rm $(EXEC)

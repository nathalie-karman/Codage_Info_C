CC	= gcc
CFLAGS	= -Wall -g
LINKER	= gcc
LFLAGS	= -Wall -lm

SRC	= agent_life_cycle.c desetalement.c etalement.c hadamard.c hdbn.c message.c 
#codage_arithmetique.c
OBJ	= $(SRC:.c=.o)
EXEC	= test_etalement chaine_transmission

all: $(EXEC)

test_etalement: $(OBJ) test_etalement.o
	$(LINKER) $^ -o $@ $(LFLAGS)
	
chaine_transmission: $(OBJ) chaine_transmission.o
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

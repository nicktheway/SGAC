CC=gcc
FLAGS=-std=c11 -Wall -O3

DEPS = pool.h cell.h
_OBJ = pool.o cell.o genetic.o

ODIR=obj
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

# Commands
MKDIR = mkdir -p

# Rules
$(ODIR)/%.o: %.c $(DEPS) | $(ODIR)
	$(CC) -c -o $@ $< $(FLAGS)

all: $(OBJ)
	$(CC) -o genetic $^ $(FLAGS)

.PHONY: clean purge

clean:
	rm -rf $(ODIR)

purge: clean
	rm -f genetic


$(ODIR):
	$(MKDIR) $(ODIR)
IDIR = ../include
CC=gcc
CFLAGS=-I$(IDIR)

ODIR = obj
LDIR = ../lib

LIBS =

_DEPS = libro.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = libro.o lista.o main.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

lista-enlazada: $(OBJ) 
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~

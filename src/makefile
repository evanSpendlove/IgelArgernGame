IDIR =../include
CC=gcc
CFLAGS=-I$(IDIR)

ODIR=obj
LDIR =../lib



_DEPS = game.h gameIO.h gameSetup.h initialTokens.h random.h save.h stackMethods.h testPrintColours.h tokenMethods.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = game.o gameIO.o gameSetup.o initialTokens.o random.o save.o stackMethods.o testPrintColours.o tokenMethods.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))


$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

main: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 
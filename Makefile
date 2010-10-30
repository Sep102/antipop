CC = cc
CFLAGS = -O3 
LIBS = -framework AudioToolbox -framework CoreFoundation -framework IOKit
OBJECTS = antipopd.o
BINDIR = antipop/root/Extra/bin
PRODUCT = $(BINDIR)/antipopd

# Targets
##
all:	antipopd
antipopd:	$(OBJECTS)
	mkdir -p $(BINDIR)
	$(CC) -o $(PRODUCT) $(OBJECTS) $(LIBS)
antipopd.o:	antipopd.c
	$(CC) $(CFLAGS) -c antipopd.c
clean:
	rm -rf $(OBJECTS) antipop/root/Extra/bin

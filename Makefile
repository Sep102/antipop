CC = cc
CFLAGS = -O3 
LIBS = -framework AudioToolbox -framework CoreFoundation -framework IOKit
OBJECTS = antipopd.o

# Targets
##
all:	antipopd
antipopd:	$(OBJECTS)
	$(CC) -o bin/antipopd $(OBJECTS) $(LIBS)
antipopd.o:	antipopd.c
	$(CC) $(CFLAGS) -c antipopd.c

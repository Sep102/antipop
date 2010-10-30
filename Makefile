CC = cc
CFLAGS = -O3 
LIBS = -framework AudioToolbox -framework CoreFoundation -framework IOKit
OBJECTS = antipopd.o

# Targets
##
all:	antipopd
antipopd:	$(OBJECTS)
	mkdir -p antipop/root/Extra/bin
	$(CC) -o antipop/root/Extra/bin/antipopd $(OBJECTS) $(LIBS)
antipopd.o:	antipopd.c
	$(CC) $(CFLAGS) -c antipopd.c
clean:
	rm -rf $(OBJECTS) antipop/root/Extra/bin

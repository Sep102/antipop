VERSION=9

CC = cc
CFLAGS = -Os
LIBS = -framework AudioToolbox -framework CoreFoundation -framework IOKit
OBJECTS = antipopd.o
BINDIR = antipop/root/Extra/bin
PKG = antipop-v$(VERSION).pkg

# Targets
##
.PHONY:all
all: $(PKG)

$(PKG): antipopd
	pkgbuild --version $(VERSION) --install-location '/' \
--identifier com.sep102.antipop --scripts scripts/ --root antipop $@

antipopd: $(OBJECTS)
	mkdir -p $(BINDIR)
	$(CC) -o $(BINDIR)/$@ $(OBJECTS) $(LIBS)
antipopd.o: antipopd.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJECTS) $(BINDIR) $(PKG)


# Use ?= to allow overriding from the env or command-line, e.g.
#
#	make CXXFLAGS="-O3 -fPIC" install
#
# Package managers will override many of these variables automatically, so
# this is aimed at making it easy to create packages (Debian packages,
# FreeBSD ports, MacPorts, pkgsrc, etc.)

CXX ?=		c++
CXXFLAGS ?=	-Wall
DESTDIR ?=	stage
PREFIX ?=	/usr/local
MKDIR ?=	mkdir
INSTALL ?=	install -c
STRIP ?=	strip

BIN =	interval_tree_test rectangle_tree_test

all: ${BIN}

interval_tree_test: interval_tree_test.cpp IntervalTree.h
	${CXX} ${CXXFLAGS} interval_tree_test.cpp -std=c++0x -o interval_tree_test

rectangle_tree_test: rectangle_tree_test.cpp RectangleTree.h IntervalTree.h
	${CXX} ${CXXFLAGS} rectangle_tree_test.cpp -std=c++0x -o rectangle_tree_test

install: all
	${MKDIR} -p ${DESTDIR}${PREFIX}/bin
	${MKDIR} -p ${DESTDIR}${PREFIX}/include/intervaltree
	for $$bin in ${BIN}; do ${INSTALL} $$bin ${DESTDIR}${PREFIX}/bin; done
	${INSTALL} IntervalTree.h ${DESTDIR}${PREFIX}/include/intervaltree
	${INSTALL} RectangleTree.h ${DESTDIR}${PREFIX}/include/intervaltree

install-strip: install
	for $$bin in ${BIN}; do ${STRIP} ${DESTDIR}${PREFIX}/bin/$$bin; done

.PHONY: clean

clean:
	rm -rf ${BIN} ${DESTDIR}

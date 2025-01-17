# Construct the Ragnarok base system
# $Ragnarok: Makefile,v 1.2 2025/01/13 16:36:00 lecorbeau Exp $

MAKE = make -C

SUBDIRS	= bin usr

all: 
	for _dir in ${SUBDIRS}; do \
		${MAKE} $$_dir; \
		done

install:
	for _dir in ${SUBDIRS}; do \
		${MAKE} $$_dir install; \
		done

clean:
	for _dir in ${SUBDIRS}; do \
		${MAKE} $$_dir clean; \
		done

deb: all
	mkdir -p ${DESTDIR}
	cp -r DEBIAN/ ${DESTDIR}/
	/usr/bin/dpkg-deb -b ${DESTDIR} .

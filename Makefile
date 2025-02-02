# Construct the Ragnarok base system
# $Ragnarok: Makefile,v 1.3 2025/02/02 15:43:05 lecorbeau Exp $

MAKE	= make -C
SUBDIRS	= bin usr

PKG	= openbsd-utils
VERSION	= 01
PKGDIR	= ${PKG}_${VERSION}_amd64

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
	mkdir -p ${PKGDIR}
	cp -r DEBIAN/ ${PKGDIR}/
	/usr/bin/dpkg-deb -b ${PKGDIR} .

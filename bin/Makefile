# Makefile for /bin dir
# $Ragnarok: Makefile,v 1.6 2025/01/27 18:22:05 lecorbeau Exp $

MAKE	= make -C

# There will be many directories
SUBDIRS	= cat cp date echo ln ls mkdir mv pwd rm rmdir sleep test

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

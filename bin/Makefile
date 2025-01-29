# Makefile for /bin dir
# $Ragnarok: Makefile,v 1.7 2025/01/29 16:58:08 lecorbeau Exp $

MAKE	= make -C

# There will be many directories
SUBDIRS	= cat cp date echo expr ln ls mkdir mv pwd rm rmdir sleep test

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

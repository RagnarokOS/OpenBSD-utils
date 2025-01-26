# Makefile for /bin dir
# $Ragnarok: Makefile,v 1.5 2025/01/26 20:36:30 lecorbeau Exp $

MAKE	= make -C

# There will be many directories
SUBDIRS	= cat cp date echo ln ls mkdir mv pwd rm rmdir

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

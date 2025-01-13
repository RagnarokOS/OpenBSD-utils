# Makefile for /bin dir
# $Ragnarok: Makefile,v 1.2 2025/01/13 16:19:39 lecorbeau Exp $

MAKE	= make -C

# There will be many directories
SUBDIRS	= cat cp date echo ls mv rm rmdir

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

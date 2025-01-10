# Makefile for /bin dir
# $Ragnarok: Makefile,v 1.1 2025/01/10 18:57:58 lecorbeau Exp $

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

# If we're building deb packages
deb:
	for _dir in ${SUBDIRS}; do \
		${MAKE} $$_dir deb; \
		done

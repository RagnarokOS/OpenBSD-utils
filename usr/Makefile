# Construct the Ragnarok base system
# $Ragnarok: Makefile,v 1.1 2025/01/13 16:33:20 lecorbeau Exp $

MAKE = make -C

SUBDIRS	= bin

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

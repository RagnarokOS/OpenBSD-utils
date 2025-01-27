# Makefile for usr/bin
# $Ragnarok: Makefile,v 1.1 2025/01/27 18:22:41 lecorbeau Exp $

MAKE	= make -C

SUBDIRS	= apply arch banner cut basename dirname nl printf true

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

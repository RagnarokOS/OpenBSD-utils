# Makefile for usr/bin
# $Ragnarok: Makefile,v 1.17 2024/02/19 17:36:08 lecorbeau Exp $

MAKE	= make -C

SUBDIRS	= apply arch banner cut basename dirname nl printf

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

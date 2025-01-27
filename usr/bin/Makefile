# Makefile for usr/bin
# $Ragnarok: Makefile,v 1.2 2025/01/27 18:52:29 lecorbeau Exp $

MAKE	= make -C

SUBDIRS	= apply arch banner comm cut basename \
	  dirname false nl printf true

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

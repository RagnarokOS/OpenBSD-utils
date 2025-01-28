# Makefile for usr/bin
# $Ragnarok: Makefile,v 1.3 2025/01/28 18:07:01 lecorbeau Exp $

MAKE	= make -C

SUBDIRS	= apply arch banner comm csplit cut basename \
	  dirname false nl printf true uname wc

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

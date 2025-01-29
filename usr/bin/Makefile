# Makefile for usr/bin
# $Ragnarok: Makefile,v 1.5 2025/01/29 16:57:30 lecorbeau Exp $

MAKE	= make -C

SUBDIRS	= apply arch banner cal comm csplit cut basename \
	  dirname expand false fmt fold nl printf true uname wc

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

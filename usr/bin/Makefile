# Makefile for usr/bin
# $Ragnarok: Makefile,v 1.7 2025/01/30 19:38:37 lecorbeau Exp $

MAKE	= make -C

SUBDIRS	= apply arch banner cal comm csplit cut basename \
	  dirname env expand false fmt fold join nl paste \
	  printf teetrue uname uniq wc

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

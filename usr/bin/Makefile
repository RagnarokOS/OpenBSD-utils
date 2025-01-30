# Makefile for usr/bin
# $Ragnarok: Makefile,v 1.8 2025/01/30 19:44:21 lecorbeau Exp $

MAKE	= make -C

SUBDIRS	= apply arch banner cal comm csplit cut basename \
	  dirname env expand false fmt fold join nl paste \
	  printf teetrue uname uniq wc yes

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

# Construct the Ragnarok base system
# $Ragnarok$

MAKE = make -C

SUBDIRS	= lib bin usr

all: 
	for _dir in ${SUBDIRS}; do \
		${MAKE} $$_dir; \
		done


# Makefile for OpenBSD's who(1)
# $Ragnarok: Makefile,v 1.1 2023/10/20 16:14:12 lecorbeau Exp $

include ${TOPDIR}/usr/share/mk/progs.mk

CC ?=		${CC}
CFLAGS ?=	${O_FLAG} -pipe ${HARDENING_CPPFLAGS} ${HARDENING_CFLAGS} ${OBSD_INC}
LDFLGAS +=	${HARDENING_LDFLAGS}
LIBS	=	${OBSD_LIB}

PREFIX ?=	/usr
MANDIR ?=	/usr/share/man

PROG =	who
OBJS =	who.o

all: ${OBJS}
	${CC} ${LDFLAGS} -o ${PROG} ${OBJS} ${LIBS}

install:
	install -d ${DESTDIR}/usr/bin ${DESTDIR}/usr/share/man/man1
	install -c -s -m 555 ${PROG} ${DESTDIR}/usr/bin
	install -c -m 444 ${PROG}.1 ${DESTDIR}/usr/share/man/man1

clean:
	rm -f ${PROG} ${OBJS}

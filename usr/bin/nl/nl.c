/*	$OpenBSD: nl.c,v 1.8 2022/12/04 23:50:49 cheloha Exp $ */
/*	$NetBSD: nl.c,v 1.11 2011/08/16 12:00:46 christos Exp $	*/

/*-
 * Copyright (c) 1999 The NetBSD Foundation, Inc.
 * All rights reserved.
 *
 * This code is derived from software contributed to The NetBSD Foundation
 * by Klaus Klein.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE NETBSD FOUNDATION, INC. AND CONTRIBUTORS
 * ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
 * TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE FOUNDATION OR CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#include <err.h>
#include <errno.h>
#include <limits.h>
#include <locale.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <wchar.h>

typedef enum {
	number_all,		/* number all lines */
	number_nonempty,	/* number non-empty lines */
	number_none,		/* no line numbering */
	number_regex		/* number lines matching regular expression */
} numbering_type;

struct numbering_property {
	const char * const	name;		/* for diagnostics */
	numbering_type		type;		/* numbering type */
	regex_t			expr;		/* for type == number_regex */
};

/* line numbering formats */
#define FORMAT_LN	"%-*d"	/* left justified, leading zeros suppressed */
#define FORMAT_RN	"%*d"	/* right justified, leading zeros suppressed */
#define FORMAT_RZ	"%0*d"	/* right justified, leading zeros kept */

#define FOOTER		0
#define BODY		1
#define HEADER		2
#define NP_LAST		HEADER

/* Note: in OpenBSD, this is defined in limits.h. However, in Ragnarok
 * it is used only for nl, so we'll define it here. Leaving this note
 * just in case we need to move it to openbsd.h in the future. */
#define NL_TEXTMAX	255

static struct numbering_property numbering_properties[NP_LAST + 1] = {
	{ "footer",	number_none,	{ 0, 0, 0, 0 } },
	{ "body",	number_nonempty, { 0, 0, 0, 0 } },
	{ "header",	number_none,	{ 0, 0, 0, 0 } },
};

void		filter(void);
void		parse_numbering(const char *, int);
__dead void	usage(void);

/*
 * Delimiter characters that indicate the start of a logical page section.
 */
static char delim[2 * MB_LEN_MAX];
static int delimlen;

/*
 * Configurable parameters.
 */

/* line numbering format */
static const char *format = FORMAT_RN;

/* increment value used to number logical page lines */
static int incr = 1;

/* number of adjacent blank lines to be considered (and numbered) as one */
static unsigned int nblank = 1;

/* whether to restart numbering at logical page delimiters */
static int restart = 1;

/* characters used in separating the line number and the corrsp. text line */
static const char *sep = "\t";

/* initial value used to number logical page lines */
static int startnum = 1;

/* number of characters to be used for the line number */
/* should be unsigned but required signed by `*' precision conversion */
static int width = 6;


int
main(int argc, char *argv[])
{
	int c;
	size_t clen;
	char delim1[MB_LEN_MAX] = { '\\' }, delim2[MB_LEN_MAX] = { ':' };
	size_t delim1len = 1, delim2len = 1;
	const char *errstr;

	(void)setlocale(LC_ALL, "");

	while ((c = getopt(argc, argv, "pb:d:f:h:i:l:n:s:v:w:")) != -1) {
		switch (c) {
		case 'p':
			restart = 0;
			break;
		case 'b':
			parse_numbering(optarg, BODY);
			break;
		case 'd':
			clen = mbrlen(optarg, MB_CUR_MAX, NULL);
			if (clen == (size_t)-1 || clen == (size_t)-2)
				errc(EXIT_FAILURE, EILSEQ, NULL);
			if (clen != 0) {
				memcpy(delim1, optarg, delim1len = clen);
				clen = mbrlen(optarg + delim1len,
				    MB_CUR_MAX, NULL);
				if (clen == (size_t)-1 || clen == (size_t)-2)
					errc(EXIT_FAILURE, EILSEQ, NULL);
				if (clen != 0) {
					memcpy(delim2, optarg + delim1len,
					    delim2len = clen);
					if (optarg[delim1len + clen] != '\0') {
						errx(EXIT_FAILURE,
						    "invalid delimiter: %s",
						    optarg);
					}
				}
			}
			break;
		case 'f':
			parse_numbering(optarg, FOOTER);
			break;
		case 'h':
			parse_numbering(optarg, HEADER);
			break;
		case 'i':
			incr = strtonum(optarg, INT_MIN, INT_MAX, &errstr);
			if (errstr)
				errx(EXIT_FAILURE, "increment value is %s: %s",
				    errstr, optarg);
			break;
		case 'l':
			nblank = strtonum(optarg, 0, UINT_MAX, &errstr);
			if (errstr)
				errx(EXIT_FAILURE,
				    "blank line value is %s: %s",
				    errstr, optarg);
			break;
		case 'n':
			if (strcmp(optarg, "ln") == 0) {
				format = FORMAT_LN;
			} else if (strcmp(optarg, "rn") == 0) {
				format = FORMAT_RN;
			} else if (strcmp(optarg, "rz") == 0) {
				format = FORMAT_RZ;
			} else
				errx(EXIT_FAILURE,
				    "illegal format -- %s", optarg);
			break;
		case 's':
			sep = optarg;
			break;
		case 'v':
			startnum = strtonum(optarg, INT_MIN, INT_MAX, &errstr);
			if (errstr)
				errx(EXIT_FAILURE,
				    "initial logical page value is %s: %s",
				    errstr, optarg);
			break;
		case 'w':
			width = strtonum(optarg, 1, INT_MAX, &errstr);
			if (errstr)
				errx(EXIT_FAILURE, "width is %s: %s", errstr,
				    optarg);
			break;
		default:
			usage();
			/* NOTREACHED */
		}
	}
	argc -= optind;
	argv += optind;

	switch (argc) {
	case 0:
		break;
	case 1:
		if (strcmp(argv[0], "-") != 0 &&
		    freopen(argv[0], "r", stdin) == NULL)
			err(EXIT_FAILURE, "%s", argv[0]);
		break;
	default:
		usage();
		/* NOTREACHED */
	}

	/* Generate the delimiter sequence */
	memcpy(delim, delim1, delim1len);
	memcpy(delim + delim1len, delim2, delim2len);
	delimlen = delim1len + delim2len;

	/* Do the work. */
	filter();

	exit(EXIT_SUCCESS);
}

void
filter(void)
{
	char *buffer;
	size_t buffersize;
	ssize_t linelen;
	int line;		/* logical line number */
	int section;		/* logical page section */
	unsigned int adjblank;	/* adjacent blank lines */
	int donumber = 0, idx;

	adjblank = 0;
	line = startnum;
	section = BODY;

	buffer = NULL;
	buffersize = 0;
	while ((linelen = getline(&buffer, &buffersize, stdin)) > 0) {
		for (idx = FOOTER; idx <= NP_LAST; idx++) {
			/* Does it look like a delimiter? */
			if (delimlen * (idx + 1) > linelen)
				break;
			if (memcmp(buffer + delimlen * idx, delim,
			    delimlen) != 0)
				break;
			/* Was this the whole line? */
			if (buffer[delimlen * (idx + 1)] == '\n') {
				section = idx;
				adjblank = 0;
				if (restart)
					line = startnum;
				goto nextline;
			}
		}

		switch (numbering_properties[section].type) {
		case number_all:
			/*
			 * Doing this for number_all only is disputable, but
			 * the standard expresses an explicit dependency on
			 * `-b a' etc.
			 */
			if (buffer[0] == '\n' && ++adjblank < nblank)
				donumber = 0;
			else
				donumber = 1, adjblank = 0;
			break;
		case number_nonempty:
			donumber = (buffer[0] != '\n');
			break;
		case number_none:
			donumber = 0;
			break;
		case number_regex:
			donumber =
			    (regexec(&numbering_properties[section].expr,
			    buffer, 0, NULL, 0) == 0);
			break;
		}

		if (donumber) {
			(void)printf(format, width, line);
			line += incr;
			(void)fputs(sep, stdout);
		} else {
			(void)printf("%*s", width, "");
		}
		(void)fwrite(buffer, linelen, 1, stdout);

		if (ferror(stdout))
			err(EXIT_FAILURE, "output error");
nextline:
		;
	}

	if (ferror(stdin))
		err(EXIT_FAILURE, "input error");

	free(buffer);
}

/*
 * Various support functions.
 */

void
parse_numbering(const char *argstr, int section)
{
	int error;
	char errorbuf[NL_TEXTMAX];

	switch (argstr[0]) {
	case 'a':
		numbering_properties[section].type = number_all;
		break;
	case 'n':
		numbering_properties[section].type = number_none;
		break;
	case 't':
		numbering_properties[section].type = number_nonempty;
		break;
	case 'p':
		/* If there was a previous expression, throw it away. */
		if (numbering_properties[section].type == number_regex)
			regfree(&numbering_properties[section].expr);
		else
			numbering_properties[section].type = number_regex;

		/* Compile/validate the supplied regular expression. */
		if ((error = regcomp(&numbering_properties[section].expr,
		    &argstr[1], REG_NEWLINE|REG_NOSUB)) != 0) {
			(void)regerror(error,
			    &numbering_properties[section].expr,
			    errorbuf, sizeof(errorbuf));
			errx(EXIT_FAILURE,
			    "%s expr: %s -- %s",
			    numbering_properties[section].name, errorbuf,
			    &argstr[1]);
		}
		break;
	default:
		errx(EXIT_FAILURE,
		    "illegal %s line numbering type -- %s",
		    numbering_properties[section].name, argstr);
	}
}

__dead void
usage(void)
{
	(void)fprintf(stderr, "usage: nl [-p] [-b type] [-d delim] [-f type] "
	    "[-h type] [-i incr] [-l num]\n\t[-n format] [-s sep] "
	    "[-v startnum] [-w width] [file]\n");
	exit(EXIT_FAILURE);
}

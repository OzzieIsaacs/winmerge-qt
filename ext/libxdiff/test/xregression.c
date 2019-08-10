/*
 *  LibXDiff by Davide Libenzi ( File Differential Library )
 *  Copyright (C) 2003  Davide Libenzi
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2.1 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 *  Davide Libenzi <davidel@xmailserver.org>
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <math.h>
#include "xdiff.h"
#include "xtestutils.h"



static void *wrap_malloc(void *priv, unsigned int size) {

	return malloc(size);
}


static void wrap_free(void *priv, void *ptr) {

	free(ptr);
}


static void *wrap_realloc(void *priv, void *ptr, unsigned int size) {

	return realloc(ptr, size);
}


int main(int argc, char *argv[]) {
	int i, chmax = 64;
	long size = 1024 * 100;
	double rmod = 0.1;
	xpparam_t xpp;
	xdemitconf_t xecfg;
	bdiffparam_t bdp;
	memallocator_t malt;

	malt.priv = NULL;
	malt.malloc = wrap_malloc;
	malt.free = wrap_free;
	malt.realloc = wrap_realloc;
	xdl_set_allocator(&malt);

	xpp.flags = 0;
	xecfg.ctxlen = 3;
	bdp.bsize = 16;

	for (i = 1; i < argc; i++) {
		if (!strcmp(argv[i], "--size")) {
			if (++i < argc)
				size = atol(argv[i]);
		} else if (!strcmp(argv[i], "--rmod")) {
			if (++i < argc)
				rmod = atof(argv[i]);
		} else if (!strcmp(argv[i], "--ctxlen")) {
			if (++i < argc)
				xecfg.ctxlen = atol(argv[i]);
		} else if (!strcmp(argv[i], "--chmax")) {
			if (++i < argc)
				chmax = atoi(argv[i]);
		}
	}

	srand(time(NULL));
	for (i = 0;; i++) {
		fprintf(stderr, "Running TEXT test : %d ... ", i);
		if (xdlt_auto_regress(&xpp, &xecfg, size, rmod, chmax) < 0) {

			fprintf(stderr, "FAIL\n");
			break;
		} else {

			fprintf(stderr, "OK\n");
		}

		fprintf(stderr, "Running BIN  test : %d ... ", i);
		if (xdlt_auto_binregress(&bdp, size, rmod, chmax) < 0) {

			fprintf(stderr, "FAIL\n");
			break;
		} else {

			fprintf(stderr, "OK\n");
		}

		fprintf(stderr, "Running RBIN  test : %d ... ", i);
		if (xdlt_auto_rabinregress(size, rmod, chmax) < 0) {

			fprintf(stderr, "FAIL\n");
			break;
		} else {

			fprintf(stderr, "OK\n");
		}

		fprintf(stderr, "Running MBIN  test : %d ... ", i);
		if (xdlt_auto_mbinregress(&bdp, size, rmod, chmax, 32) != 0) {

			fprintf(stderr, "FAIL\n");
			break;
		} else {

			fprintf(stderr, "OK\n");
		}
	}

	return 0;
}


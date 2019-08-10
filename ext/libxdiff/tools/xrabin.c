/*
 *  xrabin by Davide Libenzi (Rabin's polynomial generator)
 *  Copyright (C) 2006  Davide Libenzi
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 *  Davide Libenzi <davidel@xmailserver.org>
 *
 *
 *  Hints, ideas and code for the implementation came from:
 *
 *  Rabin's original paper: http://www.xmailserver.org/rabin.pdf
 *  Chan & Lu's paper:      http://www.xmailserver.org/rabin_impl.pdf
 *  Broder's paper:         http://www.xmailserver.org/rabin_apps.pdf
 *  LBFS source code:       http://www.fs.net/sfswww/lbfs/
 *  Geert Bosch's post:     http://marc.theaimsgroup.com/?l=git&m=114565424620771&w=2
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>



#if defined(WIN32)
#define strtoll _strtoi64
#endif


#if !defined(XRAB_WORD_TYPE)
#if defined(WIN32)
#define XRAB_WORD_TYPE __int64

#else /* #if defined(WIN32) */
#define XRAB_WORD_TYPE long long

#endif /* #if defined(WIN32) */
#endif /* #if !defined(XRAB_WORD_TYPE) */

#if !defined(XRAB_WORD_PFMT)
#if defined(WIN32)
#define XRAB_WORD_PFMT "0x%I64x"

#else /* #if defined(WIN32) */
#define XRAB_WORD_PFMT "0x%llx"

#endif /* #if defined(WIN32) */
#endif /* #if !defined(XRAB_WORD_PFMT) */

#define XPLYW_BITS (sizeof(xply_word) * 8)
#define XPLYW_MSB ((xply_word) 1 << (sizeof(xply_word) * 8 - 1))



typedef unsigned XRAB_WORD_TYPE xply_word;




static int xrab_isprime(int n) {

	if (n > 3) {
		if (n & 1) {
			int i, hn = n / 2;

			for (i = 3; i < hn; i += 2)
				if (!(n % i))
					return 0;
		} else
			return 0;
	}

	return 1;
}

static int xrab_fls(xply_word v) {
	int r, s;
	xply_word mask = ~(((xply_word) 1 << (XPLYW_BITS / 2)) - 1);

	if (v == 0)
		return 0;
	for (r = XPLYW_BITS, s = r / 2; s != 0;) {
		if ((v & mask) == 0) {
			v <<= s;
			r -= s;
		}
		s /= 2;
		mask <<= s;
	}

	return r;
}

static xply_word xrab_polymod(xply_word nh, xply_word nl, xply_word d) {
	int i, k = xrab_fls(d) - 1;

	d <<= (XPLYW_BITS - 1) - k;
	if (nh) {
		if (nh & XPLYW_MSB)
			nh ^= d;
		for (i = XPLYW_BITS - 2; i >= 0; i--)
			if (nh & ((xply_word) 1) << i) {
				nh ^= d >> (XPLYW_BITS - 1) - i;
				nl ^= d << i + 1;
			}
	}
	for (i = XPLYW_BITS - 1; i >= k; i--)
		if (nl & ((xply_word) 1 << i))
			nl ^= d >> (XPLYW_BITS - 1) - i;

	return nl;
}

static xply_word xrab_polygcd(xply_word x, xply_word y) {

	for (;;) {
		if (!y)
			return x;
		x = xrab_polymod(0, x, y);
		if (!x)
			return y;
		y = xrab_polymod(0, y, x);
	}
}

static void xrab_polymult(xply_word *php, xply_word *plp, xply_word x,
			  xply_word y) {
	int i;
	xply_word ph = 0, pl = 0;

	if (x & 1)
		pl = y;
	for (i = 1; i < XPLYW_BITS; i++)
		if (x & (((xply_word) 1) << i)) {
			ph ^= y >> (XPLYW_BITS - i);
			pl ^= y << i;
		}
	if (php)
		*php = ph;
	if (plp)
		*plp = pl;
}

static xply_word xrab_polymmult(xply_word x, xply_word y, xply_word d) {
	xply_word h, l;

	xrab_polymult(&h, &l, x, y);

	return xrab_polymod(h, l, d);
}

static int xrab_polyirreducible(xply_word f) {
	xply_word u = 2;
	int i, m = (xrab_fls(f) - 1) >> 1;

	for (i = 0; i < m; i++) {
		u = xrab_polymmult(u, u, f);
		if (xrab_polygcd(f, u ^ 2) != 1)
			return 0;
	}

	return 1;
}

static void xrab_rndgen(xply_word *f) {
	unsigned int i;
	xply_word g;

	for (i = 0, g = 0; i < sizeof(xply_word); i++)
		g ^= (g << 11) + (unsigned int) rand() + (g >> 7);
	*f = g;
}

static int xrab_polygen(int degree, xply_word *ply) {
	xply_word msb, mask, f;

	if (degree <= 0 || degree >= XPLYW_BITS)
		return -1;
	msb = ((xply_word) 1) << degree;
	mask = msb - 1;
	srand(time(NULL));
	do {
		xrab_rndgen(&f);
		f = (f & mask) | msb;
	} while (!xrab_polyirreducible(f));
	*ply = f;

	return 0;
}

static int xarb_calc_tu(xply_word poly, int size, xply_word *t, xply_word *u) {
	int j, xshift, shift;
	xply_word t1, ssh;

	xshift = xrab_fls(poly) - 1;
	shift = xshift - 8;
	if (shift < 0)
		return -1;
	t1 = xrab_polymod(0, ((xply_word) 1) << xshift, poly);
	for (j = 0; j < 256; j++)
		t[j] = xrab_polymmult(j, t1, poly) | ((xply_word) j << xshift);
	for (j = 1, ssh = 1; j < size; j++)
		ssh = (ssh << 8) ^ t[ssh >> shift];
	for (j = 0; j < 256; j++)
		u[j] = xrab_polymmult(j, ssh, poly);

	return 0;
}

int main(int ac, char **av) {
	int i, size = 20, degree = 0, shift;
	xply_word ply = 0, t[256], u[256];

	for (i = 1; i < ac; i++) {
		if (strcmp(av[i], "-s") == 0) {
			if (++i < ac)
				size = atol(av[i]);
		} else if (strcmp(av[i], "-p") == 0) {
			if (++i < ac)
				ply = (xply_word) strtoll(av[i], NULL, 16);
		} else if (strcmp(av[i], "-d") == 0) {
			if (++i < ac)
				degree = atol(av[i]);
		}
	}
	if (degree && (degree < 8 || degree >= XPLYW_BITS)) {
		fprintf(stderr, "degree (%d) out of bound for the poly word size (8..%u)\n",
			degree, XPLYW_BITS);
		return 1;
	}
	if (degree == 0)
		for (degree = XPLYW_BITS - 1; !xrab_isprime(degree); degree--);
	if (ply == 0 && xrab_polygen(degree, &ply) < 0)
		return 2;
	shift = (xrab_fls(ply) - 1) - 8;
	fprintf(stderr, "found poly = " XRAB_WORD_PFMT "  (shift %d)\n",
		ply, shift);
	if (xarb_calc_tu(ply, size, t, u) < 0)
		return 3;

	fprintf(stdout, "#if defined(XRABPLY_TYPE%d)\n\n", XPLYW_BITS);
	fprintf(stdout, "#if !defined(XV%d)\n", XPLYW_BITS);
	fprintf(stdout, "#define XV%d(v) ((xply_word) v ## ULL)\n", XPLYW_BITS);
	fprintf(stdout, "#endif\n\n");
	fprintf(stdout, "#define XRAB_ROOTPOLY XV%d(" XRAB_WORD_PFMT ")\n\n",
		XPLYW_BITS, ply);
	fprintf(stdout, "#define XRAB_SHIFT %d\n", shift);
	fprintf(stdout, "#define XRAB_WNDSIZE %d\n\n", size);
	fprintf(stdout, "typedef unsigned XRABPLY_TYPE%d xply_word;\n\n", XPLYW_BITS);
	fprintf(stdout, "static const xply_word T[256] = {\n");
	for (i = 0; i < 256; i++) {
		if (i) {
			fputs(",", stdout);
			if (i % 4 == 0)
				fputs("\n\t", stdout);
			else
				fputs(" ", stdout);
		} else
			fputs("\t", stdout);
		fprintf(stdout, "XV%d(" XRAB_WORD_PFMT ")", XPLYW_BITS, t[i]);
	}
	fprintf(stdout, "\n};\n\n");

	fprintf(stdout, "static const xply_word U[256] = {\n");
	for (i = 0; i < 256; i++) {
		if (i) {
			fputs(",", stdout);
			if (i % 4 == 0)
				fputs("\n\t", stdout);
			else
				fputs(" ", stdout);
		} else
			fputs("\t", stdout);
		fprintf(stdout, "XV%d(" XRAB_WORD_PFMT ")", XPLYW_BITS, u[i]);
	}
	fprintf(stdout, "\n};\n\n");

	fprintf(stdout, "#endif /* if defined(XRABPLY_TYPE%d) */\n\n", XPLYW_BITS);

	return 0;
}


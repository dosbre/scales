#define _XOPEN_SOURCE

#include <stdio.h>
#include <stdlib.h>

#include "scales.h"

#define length(a) (sizeof(a) / sizeof(a[0]))

void fb_print(int strings, int *tunning, int frets, int capo,
							int scale, int tone)
{
	int s;		/* string	*/
	int f;		/* fret		*/

	for (s = 0; s < strings; s++) {
		int n = tunning[s];	/* note */

		for (f = 0; f < frets + 1; f++, n++) {
			if (n >= NNOTES)
				n %= NNOTES;

			if (f >= capo && inscale(n, scale, tone))
				printf("-%2s-|", notes[n]);
			else
				printf("----|");

			if (!f || f == capo)
				putchar('|');
		}
		putchar('\n');
	}
}

int tunestr(int *tune, const char *tunning)
{
	const char *p;
	int s;		/* string */

	s = 0;

	if (*tunning == '0' || (s = atoi(tunning)))
		p = tunnings[s].tunning;
	else
		p = tunning;

	s = 0;

	while (*p && s < MAX_STRING) {
		switch (*p++) {
		case 'A': tune[s++] = A; break;
		case 'B': tune[s++] = B; break;
		case 'C': tune[s++] = C; break;
		case 'D': tune[s++] = D; break;
		case 'E': tune[s++] = E; break;
		case 'F': tune[s++] = F; break;
		case 'G': tune[s++] = G; break;
		case '#':
			if (!s)
				continue;
			tune[s - 1]++;
			break;
		case 'b':
			if (!s)
				continue;
			tune[s - 1]--;
			break;
		default:
			fprintf(stderr, "invalid tune %c\n", *--p);
			exit(EXIT_FAILURE);
		}
	}
	return s;
}

/*
 */
int aton(const char *c)
{
	int n = -1;

	switch (*c++) {
	case 'A': n = A; break;
	case 'B': n = B; break;
	case 'C': n = C; break;
	case 'D': n = D; break;
	case 'E': n = E; break;
	case 'F': n = F; break;
	case 'G': n = G; break;
	default: return -1;
	}
	if (*c == '#')
		n++;
	else if (*c == 'b')
		n--;
	return n < 0 ? n + NNOTES : n;
}

int tune_table(void)
{
	int i;

	for (i = 0; i < length(tunnings); ++i)
		printf("%d: %s\n", i, tunnings[i].name);
	return i;
}

int scale_table(void)
{
	int i;

	for (i = 0; i < length(scales); ++i)
		printf("%d: %s\n", i, scales[i].name);
	return i;
}

int main(int argc, char *argv[])
{
	int t[MAX_STRING] = { E, B, G, D, A, E };	/* tunning	*/
	int s = 6;					/* strings	*/
	int f = 12;					/* frets	*/
	int c = 0;					/* capo		*/
	int m = 0;					/* mode (scale)	*/
	int n = C;					/* tone		*/
	int opt;

	while ((opt = getopt(argc, argv, "t:s:f:c:m:n:h")) != -1) {
		switch (opt) {
		case 't':
			if (*optarg == '?')
				return tune_table();
			s = tunestr(t, optarg);
			break;
		case 's':
			if ((s = atoi(optarg)) > MAX_STRING) {
				fprintf(stderr, "max strings %d\n",
								MAX_STRING);
				return -1;
			}
			break;
		case 'f': f = atoi(optarg); break;
		case 'c': c = atoi(optarg); break;
		case 'm':
			if (*optarg == '?')
				return scale_table();
			if ((m = atoi(optarg)) > sizeof(scales)) {
				fprintf(stderr, "invalid scale\n");
				return -1;
			}
			break;
		case 'n':
			if ((n = aton(optarg)) < 0) {
				fprintf(stderr, "invalid tone %s\n", optarg);
				return -1;
			}
			break;
		case 'h':
		default:
			fprintf(stderr, "Usage: %s [-s strings] [-f frets] "
					"[-c capo] [-t tunning]\n", argv[0]);
			return -1;
		}
	}

	if (f < c) {
		fprintf(stderr, "nothing to print\n");
		return -1;
	}

	printf("Scale: %s\t Tone: %s\n\n", scales[m].name, notes[n]);
	fb_print(s, t, f, c, scales[m].bit, n);

	return 0;
}


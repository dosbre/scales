enum note { A, BF, B, C, CS, D, EF, E, F, FS, G, GS };

enum enharmonic { AS = BF, DF = CS, DS = EF, GF = FS, AF = GS };

char *notes[] = {
	"A", "Bb", "B", "C", "C#", "D", "Eb", "E", "F", "F#", "G", "G#"
};

#define NNOTES (sizeof(notes) / sizeof(notes[0]))

/*
 *  0  1  2  3 | 4  5  6  7 | 8  9 10 11
 * ======================================
 *  A Bb  B  C |C#  D Eb  E | F F#  G G#
 * Bb  B  C C# | D Eb  E  F | F#  G G# A
 *  B  C C#  D |Eb  E  F F# | G G#  A Bb
 *  C C#  D Eb | E  F F#  G |G#  A Bb  B
 * C#  D Eb  E | F F#  G G# | A Bb  B  C
 *  D Eb  E  F |F#  G G#  A |Ab  B  C C#
 * Eb  E  F F# | G G#  A Ab | B  C C#  D
 *  E  F F#  G |G#  A Ab  B | C C#  D Eb
 *  F F#  G G# | A Ab  B  C |C#  D Eb  E
 * F#  G G#  A |Ab  B  C C# | D Eb  E  F
 *  G G#  A Ab | B  C C#  D |Eb  E  F F#
 * G#  A Ab  B | C C#  D Eb | E  F F#  G
 *
 *  C C#  D Eb | E  F F#  G |G#  A Bb  B
 *  1  0  1  0 | 1  1  0  1 | 0  1  0  1
 */
#define inscale(note, scale, tone) (((scale) << ((tone) > (note) ? (note) - (tone) + NNOTES : (note) - (tone)) & 0x800) > 0)

int _scales[] = {
	0xfff,		/* Chrommatic		*/
	0xad5,		/* Diatonic Major	*/
	0xb5a,		/* Diatonic Minor	*/
	0xb59,		/* Harmonic Minor	*/
	0xa94,		/* Pentatonic Major	*/
	0x951,		/* Pentatonic Minor	*/
	0xa52,		/* Pentatonic Egyptian, Suspended	*/
	0x94a,		/* Pentatonic Blues Minor, Man Gong	*/
	0xa58		/* Pentatonic Blues Major, Ritusen	*/
};
enum _scale {
	CHROMATIC,
	DIATONIC_MAJOR,
	DIATONIC_MINOR,
	PENTATONIC_MAJOR,
	PENTATONIC_MINOR,
	PENTATONIC_SUSPENDED,
	PENTATONIC_BLUES_MAJOR,
	PENTATONIC_BLUES_MINOR
};

struct scales {
	const char *name;
	unsigned int bit;
} scales[] = {
	{ "Chromatic",		0xfff },
	{ "Diatonic Major",	0xad5 },
	{ "Diatonic Minor",	0xb5a },
	{ "Harmonic Minor",	0xb59 },
	{ "Pentatonic Major",	0xa94 },
	{ "Pentatonic Minor",	0x951 },
	{ "Pentatonic Suspended",	0xa52 },	/* Egyptian	*/
	{ "Pentatonic Blues Minor",	0x94a },	/* Man Gong	*/
	{ "Pentatonic Blues Major",	0xa58 }		/* Ritusen	*/
};

#define MAX_STRING 7

struct tunnings {
	const char *name;
	const char *tunning;
} tunnings[] = {
	{ "Standard",	"EBGDAE" },
	{ "Drop",	"EBGDAD" },
	{ "DDrop",	"DBGDAD" },
	{ "Open",	"EAEC#AE" }
};

/*
 * c = note
 * b = scale[x]
 * a = tone
 *
 * RETURNS
 * 1 if <note> is in <tone> <scale>, or 0
 *//*
#define inscale(a, b, c) ((b << ((a) > (c) ? (c) - (a) + NNOTES : (c) - (a) ) & 0x800) > 0)
*/

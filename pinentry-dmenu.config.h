/* See LICENSE file for copyright and license details. */
/* Default settings; can be overriden by command line. */

static int bottom = 0;
static int embedded = 0;
static int minpwlen = 32;
static int mon = -1;

static const int barpadding = 6;
static const int fontoffset = -1;
static const char *asterisk = "*";
static const char *fonts[] = {
	"Inconsolata LGC:style=Bold:size=9.5:antialias=true:hinting=true"
};
static const char *prompt = NULL;
static const char col_gray1[]   = "#14161b";
static const char col_gray3[]   = "#c5c8c6";
static const char col_cyan[]    = "#2d2f31";
static const char *colors[SchemeLast][4] = {
	[SchemePrompt] = { col_gray3, col_gray1 },
	[SchemeNormal] = { col_gray3, col_gray1 },
	[SchemeSelect] = { col_gray3, col_cyan },
	[SchemeDesc]   = { col_gray3, col_gray1 }
};

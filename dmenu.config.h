/* See LICENSE file for copyright and license details. */
/* Default settings; can be overriden by command line. */

static int topbar = 1;                      /* -b  option; if 0, dmenu appears at bottom     */
static const int barpadding = 6;
/* -fn option overrides fonts[0]; default X11 font or font set */
static const char *fonts[] = {
	"Inconsolata LGC:style=Bold:size=9.5:antialias=true:hinting=true"
};
static const int fontoffset    = -1;
static const char *prompt      = NULL;      /* -p  option; prompt to the left of input field */

static const char col_gray1[]       = "#1d1f21";
static const char col_gray2[]       = "#ff0000";
static const char col_gray3[]       = "#c5c8c6";
static const char col_gray4[]       = "#00ff00";
static const char col_cyan[]        = "#2d2f31";
static const char *colors[SchemeLast][2] = {
	/*               fg         bg       */
	[SchemeNorm] = { col_gray3, col_gray1 },
	[SchemeSel]  = { col_gray3, col_cyan  },
	[SchemeOut]  = { "#000000", "#00ffff" },
};
/* -l option; if nonzero, dmenu uses vertical list with given number of lines */
static unsigned int lines      = 0;

/*
 * Characters not considered part of a word while deleting words
 * for example: " /?\"&[]"
 */
static const char worddelimiters[] = " ";

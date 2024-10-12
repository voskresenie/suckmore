/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 6;        /* border pixel of windows */
static const unsigned int snap      = 4;        /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "Inconsolata LGC:style=Bold:size=9.5:antialias=true:hinting=true" };
static const int fontoffset         = -1;       /* adjust spacing between characters */
// font spacing may be able to be fixed with something like this --
//      "c-fixed-medium-r-semicondensed--13-100-100-100-c-60-iso8859-1:size=11";
static const char dmenufont[]       = "Inconsolata LGC:style=Bold:size=9.5:antialias=true:hinting=true";
// static const char col_gray1[]       = "#1d1f21";    /* termbg */
static const char col_gray1[]       = "#14161b";    /* termbg */
static const char col_gray2[]       = "#ff0000";    /* unused */
static const char col_gray3[]       = "#c5c8c6";
static const char col_gray4[]       = "#00ff00";    /* unused */
static const char col_cyan[]        = "#2d2f31";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray1 },
	[SchemeSel]  = { col_gray3, col_gray1, col_cyan  },
};

/* BEGIN rebirth */
//static const char statedir          = "${XDG_STATE_HOME:-$HOME/.local/state}/dwm";
/* END rebirth */
/* BEGIN grid */
static const unsigned int cellwidth   = 7;
static const unsigned int cellheight  = 18;
static const unsigned int gridwidth   = 12; /* was 6 */
static const unsigned int gridheight  = 9;  /* was 6 */
#define XINC  ((gridwidth < 3) ? 1 : ((gridwidth  % 3) == 0 ? gridwidth  / 3 : gridwidth  / 4))
#define YINC  ((gridwidth < 3) ? 1 : ((gridheight % 3) == 0 ? gridheight / 3 : gridheight / 4))
/*      3   4   # /
 *  01  0   0   1 1
 *  02  0   0   1 2
 *  03  1   0   1 3
 *  04  1   1   1 4
 *  05  1   1   1 5
 *  06  2   1   2 3
 *  07  2   1   1 7
 *  08  2   2   2 4
 *  09  3   2   3 3
 *  10  3   2   2 5
 *  11  3   2   2 5
 *  12  4   3   4 3
 *  13  4   3   3 4
 *  14  4   3   3 4
 *  15  5   3   5 3
 *  16  5   4   4 4
 *  *  *  *  *  *  */
/* END grid */

/* tagging */
// static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9",
//                               "!", "@", "#", "$", "%", "^", "&", "*", "-", "+" };
static const char *tags[] = { "#", "1", "2", "3", "4", "5", "6", "7", "8", "9", "!!", "%", "$" };
								// "!", "@", "#", "%", "&", "*", "-", "+" };

#define SMWIN 4,3
#define MDWIN 4,6
#define LGWIN 6,9
#define XLWIN 8,9
#define FULL  gridwidth,gridheight
static const Rule rules[] = {
	/* xprop(1):
	 *  WM_CLASS(STRING) = instance, class
	 *  WM_NAME(STRING) = title
	 **/
	/* BEGIN grid */
    /* get class/instance/title from `xprop WM_CLASS WM_NAME` */
    /* TODO: make case insensitive if text here is all lowercase */
	/* class        instance        title                           tags mask     x,y,w,h     isfloating   monitor */
	{ "tty",        NULL,           NULL,                           0,            0,0,SMWIN,  0,           -1 },    /* tty is the custom title I've assigned to alacritty */
	{ "firefox",    "Navigator",    NULL,                           0,            0,0,MDWIN,  0,           -1 },    /* browser */
	{ "librewolf",  "Navigator",    NULL,                           0,            0,0,MDWIN,  0,           -1 },    /* browser */
	{ "firefox",    "Places",       NULL,                           0,            0,0,MDWIN,  0,           -1 },    /* bookmark manager */
	{ "librewolf",  "Places",       NULL,                           0,            0,0,MDWIN,  0,           -1 },    /* bookmark manager */
	{ "LibreWolf",  "Navigator",    NULL,                           0,            0,0,MDWIN,  0,           -1 },    /* browser */
	{ "LibreWolf",  "Places",       NULL,                           0,            0,0,MDWIN,  0,           -1 },    /* bookmark manager */
	{ "feh",        NULL,           NULL,                           0,            0,0,MDWIN,  1,           -1 },
	{ "krita",      NULL,           NULL,                           0,            0,0,LGWIN,  0,           -1 },
	{ "gimp",       NULL,           NULL,                           0,            0,0,LGWIN,  1,           -1 },
	{ NULL,         NULL,           "Bitwarden Password Manager",   0,            0,0,SMWIN,  1,           -1 },
	/* END grid */
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

#define GRIDTILE    &layouts[0]
#define TILE        &layouts[1]
#define NOTILE      &layouts[2]
#define MONOCLE     &layouts[3]
static const Layout layouts[] = {
	/* symbol     arrange function */
	/* BEGIN grid */
	{ "|||",      gridtile },
	/* END grid */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* BEGIN grid */
#define GRIDKEYS(KEY,X,Y) \
	{ MODKEY,                       KEY,      gridmove,       {.v = (int []){ XINC*X, YINC*Y } } }, \
	{ MODKEY|ControlMask,           KEY,      gridmove,       {.v = (int []){ X, Y } } }, \
	{ MODKEY|ShiftMask,             KEY,      gridresize,     {.v = (int []){ XINC*X, YINC*Y } } }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      gridresize,     {.v = (int []){ X, Y } } },
/* BEGIN grid */

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
/* consider replacing with rofi */
static const char *dmenucmd[] = { "dmenu_run", "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray3, NULL };
static const char *termcmd[]  = { "alacritty", NULL };

/* list of keys may be found in <X11/keysymdef.h> */
/* Keys to consider using for bindings:
 *   XK_BackSpace
 *   XK_Delete
 *   XK_Escape
 *
 * Potential tags
 *  `    1    2    3    4    5    6    7    8    9    0    [    ]    |
 *    '    ,    .    p    y    f    g    c    r    l    /    =    \  |
 *    a    o    e    u    i    d    h    t    n    s    -            |
 *    ;    q    j    k    x    b    m    w    v    z                 |
 */
static const Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },
	/* BEGIN rebirth */
//	{ MODKEY,                       XK_s,      savestate,      {0} },
//	{ MODKEY,                       XK_o,      loadstate,      {0} },
	/* END rebirth */
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	//{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = TILE} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = NOTILE} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = MONOCLE} },
	/* BEGIN grid */
	{ MODKEY,                       XK_g,      setlayout,      {.v = GRIDTILE} },
	/* END grid */
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
//	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
//	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
//	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
//	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	/* BEGIN grid */
	GRIDKEYS(                       XK_Up,                      0, -1)
	GRIDKEYS(                       XK_Down,                    0,  1)
	GRIDKEYS(                       XK_Left,                   -1,  0)
	GRIDKEYS(                       XK_Right,                   1,  0)
	/* END grid */
	/* BEGIN shift */
	{ MODKEY,                       XK_comma,  shiftview,      {.i = -1 } },
	{ MODKEY,                       XK_period, shiftview,      {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  shifttag,       {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, shifttag,       {.i = +1 } },
	/* END shift */
	TAGKEYS(                        XK_1,                      1)
	TAGKEYS(                        XK_2,                      2)
	TAGKEYS(                        XK_3,                      3)
	TAGKEYS(                        XK_4,                      4)
	TAGKEYS(                        XK_5,                      5)
	TAGKEYS(                        XK_6,                      6)
	TAGKEYS(                        XK_7,                      7)
	TAGKEYS(                        XK_8,                      8)
	TAGKEYS(                        XK_9,                      9)
	TAGKEYS(                        XK_a,                      0)
	TAGKEYS(                        XK_o,                      10)
	TAGKEYS(                        XK_e,                      11)
	TAGKEYS(                        XK_u,                      12)
//	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
	{ MODKEY|ShiftMask,             XK_Delete, quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = NOTILE} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};


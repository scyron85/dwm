/* See LICENSE file for copyright and license details. */

/* constants */
#define TERMINAL "st"
#define TERMCLASS "St"

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int swallowfloating    = 0;        /* 1 means swallow floating windows by default */
static const int showbar            = 1;        /* 0 means no bar */
static const unsigned int gappih    = 10;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 10;       /* vert inner gap between windows */
static const unsigned int gappoh    = 10;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 10;       /* vert outer gap between windows and screen edge */
static const int smartgaps          = 0;        /* 1 means no outer gap when there is only one window */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "xos4 Terminus:style=Regular:size=16" , "siji:size=16:antialias=true:autohint=true"};
static const char dmenufont[]       = "xos4 Terminus:style=Regular:size=16";
static char normbgcolor[]           = "#1f1f1f";
static char normbordercolor[]       = "#1f1f1f";
static char normfgcolor[]           = "#c0b18b";
static char selfgcolor[]            = "#d17b49";
static char selbordercolor[]        = "#4d4d4d";
static char selbgcolor[]            = "#1f1f1f";
static char *colors[][3] = {
       /*               fg           bg           border   */
       [SchemeNorm] = { normfgcolor, normbgcolor, normbordercolor },
       [SchemeSel]  = { selfgcolor,  selbgcolor,  selbordercolor  },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };



static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class     instance  title           tags mask  isfloating  isterminal  noswallow  monitor */
	{ "Gimp",    NULL,     NULL,           0,         1,          0,           0,        -1 },
	{ "Firefox", NULL,     NULL,           1 << 8,    0,          0,          -1,        -1 },
	{ "St",      NULL,     NULL,           0,         0,          1,           0,        -1 },
	{ NULL,      NULL,     "Event Tester", 0,         0,          0,           1,        -1 }, /* xev */
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
#include "vanitygaps.c"
static const Layout layouts[] = {
	/* symbol     arrange function */
        { "[]=",	tile },			/* Default: Master on left, slaves on right */
	{ "TTT",	bstack },		/* Master on top, slaves on bottom */

	{ "[@]",	spiral },		/* Fibonacci spiral */
	{ "[\\]",	dwindle },		/* Decreasing in size right and leftward */

	{ "H[]",	deck },			/* Master on left, slaves in monocle-like mode on right */
 	{ "[M]",	monocle },		/* All windows on top of eachother */

	{ "|M|",	centeredmaster },		/* Master in middle, slaves on sides */
	{ ">M>",	centeredfloatingmaster },	/* Same but master floats */

        { "HHH",        gaplessgrid },

        { "><>",	NULL },			/* no layout function means floating behavior */
	{ NULL,		NULL },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbgcolor, "-sf", selfgcolor, NULL };
static const char *termcmd[]  = { "st", NULL };

#include <X11/XF86keysym.h>
#include "shiftview.c"

static Key keys[] = {
	/* modifier                     key                     function        argument */
	{ MODKEY,                       XK_p,                   spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_Return,              spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_b,                   togglebar,      {0} },
	{ MODKEY,                       XK_j,                   focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,                   focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,                   incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,                   incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,                   setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,                   setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_Return,              zoom,           {0} },
	{ MODKEY,                       XK_Tab,                 view,           {0} },
	{ MODKEY,                       XK_c,                   killclient,     {0} },
	{ MODKEY,                       XK_t,                   setlayout,      {.v = &layouts[0]} },
	{ MODKEY|ShiftMask,             XK_t,                   setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_y,                   setlayout,      {.v = &layouts[2]} },
	{ MODKEY|ShiftMask,             XK_y,                   setlayout,      {.v = &layouts[3]} },
	{ MODKEY,                       XK_u,                   setlayout,      {.v = &layouts[4]} },
	{ MODKEY|ShiftMask,             XK_u,                   setlayout,      {.v = &layouts[5]} },
	{ MODKEY,                       XK_o,                   setlayout,      {.v = &layouts[6]} },
	{ MODKEY|ShiftMask,             XK_o,                   setlayout,      {.v = &layouts[7]} },
	{ MODKEY|ShiftMask,             XK_i,                   setlayout,      {.v = &layouts[8]} },
	{ MODKEY,                       XK_space,               setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,               togglefloating, {0} },
	{ MODKEY,			XK_f,		        togglefullscr,	{0} },
	{ MODKEY,                       XK_0,                   view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,                   tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,               focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period,              focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,               tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period,              tagmon,         {.i = +1 } },
	{ MODKEY,			XK_g,		        shiftview,	{ .i = -1 } },
	{ MODKEY,			XK_semicolon,		shiftview,	{ .i =  1 } },
        { MODKEY,			XK_minus,               incrgaps,       {.i = +3 } },
	{ MODKEY,			XK_equal,               incrgaps,       {.i = -3 } },
	{ MODKEY|ShiftMask,		XK_equal,               togglegaps,	   {0} },
	{ MODKEY|ShiftMask,		XK_minus,               defaultgaps,	   {0} },
	TAGKEYS(                        XK_1,                                   0)
	TAGKEYS(                        XK_2,                                   1)
	TAGKEYS(                        XK_3,                                   2)
	TAGKEYS(                        XK_4,                                   3)
	TAGKEYS(                        XK_5,                                   4)
	TAGKEYS(                        XK_6,                                   5)
	TAGKEYS(                        XK_7,                                   6)
	TAGKEYS(                        XK_8,                                   7)
	TAGKEYS(                        XK_9,                                   8)
	{ MODKEY|ShiftMask,             XK_q,                   quit,           {0} },

	{ 0,				XK_Print,	spawn,		SHCMD("maimpick") },
	{ ShiftMask,			XK_Print,	spawn,		SHCMD("maim -s pic-selected-$(date '+%y%m%d-%H%M-%S').png") },
	{ MODKEY,			XK_Print,	spawn,		SHCMD("dmenurecord") },
	{ MODKEY|ShiftMask,		XK_Print,	spawn,		SHCMD("dmenurecord kill") },
	{ MODKEY,			XK_Delete,	spawn,		SHCMD("dmenurecord kill") },
	{ MODKEY,			XK_Scroll_Lock,	spawn,		SHCMD("killall screenkey || screenkey &") },

	{ 0, XF86XK_AudioMute,		spawn,		SHCMD("pamixer -t; kill -44 $(pidof dwmblocks)") },
	{ 0, XF86XK_AudioRaiseVolume,	spawn,		SHCMD("pamixer --allow-boost -i 10; kill -44 $(pidof dwmblocks)") },
	{ 0, XF86XK_AudioLowerVolume,	spawn,		SHCMD("pamixer --allow-boost -d 10; kill -44 $(pidof dwmblocks)") },
	{ 0, XF86XK_AudioPrev,		spawn,		SHCMD("mpc prev") },
	{ 0, XF86XK_AudioNext,		spawn,		SHCMD("mpc next") },
	{ 0, XF86XK_AudioPause,		spawn,		SHCMD("mpc pause") },
	{ 0, XF86XK_AudioPlay,		spawn,		SHCMD("mpc play") },
	{ 0, XF86XK_AudioStop,		spawn,		SHCMD("mpc stop") },
	{ 0, XF86XK_AudioRewind,	spawn,		SHCMD("mpc seek -10") },
	{ 0, XF86XK_AudioForward,	spawn,		SHCMD("mpc seek +10") },
	{ 0, XF86XK_AudioMicMute,	spawn,		SHCMD("pactl set-source-mute @DEFAULT_SOURCE@ toggle") },
	{ 0, XF86XK_AudioMedia,		spawn,		SHCMD(TERMINAL " -e ncmpcpp") },
	{ 0, XF86XK_PowerOff,		spawn,		SHCMD("sysact") },
	{ 0, XF86XK_Calculator,		spawn,		SHCMD(TERMINAL " -e bc -l") },
	{ 0, XF86XK_Sleep,		spawn,		SHCMD("sudo -A zzz") },
	{ 0, XF86XK_WWW,		spawn,		SHCMD("$BROWSER") },
	{ 0, XF86XK_DOS,		spawn,		SHCMD(TERMINAL) },
	{ 0, XF86XK_ScreenSaver,	spawn,		SHCMD("slock & xset dpms force off; mpc pause; pauseallmpv") },
	{ 0, XF86XK_TaskPane,		spawn,		SHCMD(TERMINAL " -e htop") },
	{ 0, XF86XK_Mail,		spawn,		SHCMD(TERMINAL " -e neomutt ; pkill -RTMIN+12 dwmblocks") },
	{ 0, XF86XK_MyComputer,		spawn,		SHCMD(TERMINAL " -e ranger") },
	/* { 0, XF86XK_Battery,		spawn,		SHCMD("") }, */
	{ 0, XF86XK_Launch1,		spawn,		SHCMD("xset dpms force off") },
	{ 0, XF86XK_TouchpadToggle,	spawn,		SHCMD("(synclient | grep 'TouchpadOff.*1' && synclient TouchpadOff=0) || synclient TouchpadOff=1") },
	{ 0, XF86XK_TouchpadOff,	spawn,		SHCMD("synclient TouchpadOff=1") },
	{ 0, XF86XK_TouchpadOn,		spawn,		SHCMD("synclient TouchpadOff=0") },
	{ 0, XF86XK_MonBrightnessUp,	spawn,		SHCMD("xbacklight -inc 15") },
	{ 0, XF86XK_MonBrightnessDown,	spawn,		SHCMD("xbacklight -dec 15") },

	{ MODKEY,			XK_F2,		spawn,		SHCMD("bookmarkpick") },
	{ MODKEY,			XK_F3,		spawn,		SHCMD("videopick") },
	{ MODKEY,			XK_F4,		spawn,		SHCMD("video-add") },
	{ MODKEY,			XK_F5,		spawn,		SHCMD("displayselect") },
	{ MODKEY,			XK_F6,		spawn,		SHCMD("dmenumount") },
	{ MODKEY,			XK_F7,		spawn,		SHCMD("dmenuumount") },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
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

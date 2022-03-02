/* See LICENSE file for copyright and license details. */

#include <X11/XF86keysym.h>
#include "fibonacci.c"

//static const char *upvol[]   = { "pactl", "set-sink-volume", "@DEFAULT_SINK@", "+5%",     NULL };
//static const char *downvol[] = { "pactl", "set-sink-volume", "@DEFAULT_SINK@", "-5%",     NULL };
//static const char *mutevol[] = { "pactl", "set-sink-mute",   "@DEFAULT_SINK@", "toggle",  NULL };
//static const char *brightness[] ={"brightnessctl", "set", "6000+", NULL};
//static const char *brightness2[]= {"brightnessctl", "set", "6000-", "--min-value=1", "NULL"};
/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int snap      = 10;       /* snap pixel */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayonleft = 0;   	/* 0: systray in the right corner, >0: systray on left of status text */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        = 1;     /* 0 means no systray */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 0;        /* 0 means bottom bar */
static const char *fonts[]          = { "Font Awesome 5 Brands:size=12" };
static const char dmenufont[]       = "Font Awesome 5 Brands:size=12";
//static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
//static const char col_gray3[]       = "#bbbbbb";
//static const char col_gray4[]       = "#eeeeee";
static const char col_black[]       = "#000000";
static const char col_dark_purple[] = "#6A1A87";
static const char col_white[] 	    = "#FFFFFF";
static const char col_purple[] 	    = "#ab20fd";
//static const char col_cyan[]        = "#005577";
//static const char col_pink[]        = "#f000ff";
static const char col_green_aqua[] = "#00ff9f";
static const char col_aqua[]   	    = "#76FFFD";

static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_aqua, col_black, col_gray2 },
	[SchemeSel]  = { col_white, col_dark_purple, col_aqua},
};

static const char *const autostart[] = {
	"/usr/local/bin/bar.sh", NULL,
	"nm-applet", NULL,
	"sh", "-c", "numlockx &", NULL,
	"/home/agus/.fehbg", NULL,
	"sh", "-c", "setxkbmap us,es -option 'grp:alt_shift_toggle'", NULL,
	NULL /* terminate */
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
//	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
//	{ "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
	{ "galculator",  NULL,       NULL,       0,       1,           -1 },
};


/* layout(s) */
static const float mfact     = 0.62; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[\\]",      dwindle },
	{ "[M]",      monocle },
	{ "[@]",      spiral },
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
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
//static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *dmenucmd[] = { "rofi", "-show", "drun", NULL };
static const char *screenshot[]  = { "gnome-screenshot", "-i", NULL };
static const char *termcmd[]  = { "alacritty", NULL };
static const char *calendar[]  = { "alacritty", "-e", "calendar.sh", NULL }; // Assumes calendar.sh is in /usr/local/bin
static const char *internet[]  = { "chromium", NULL };
static const char *files[]  = { "thunar", NULL };
static const char *calculator[]  = { "galculator", NULL };

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_d,      spawn,          SHCMD("rofi -show drun -run-shell-command" )},
	{ MODKEY,            		XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY|ShiftMask,		XK_s,	   spawn,	   {.v = screenshot } },	
	{ MODKEY,			XK_w,	   spawn,	   {.v = internet} },	
	{ MODKEY,			XK_e,	   spawn,	   {.v = files} },	
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
//	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
//	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_f,      togglefullscr,     {0} },
	{ MODKEY|ShiftMask,		XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_r,      setlayout,      {.v = &layouts[3]} },
	{ MODKEY|ShiftMask,             XK_r,      setlayout,      {.v = &layouts[4]} },
//	{ MODKEY,                       XK_space,  setlayout, 	   {0} },
	{ MODKEY,              		XK_Right,           view_adjacent,  { .i = +1 } },
	{ MODKEY,              		XK_Left,           view_adjacent,  { .i = -1 } },
	{ Mod1Mask,			XK_Shift_L, spawn,	   SHCMD("slp=$(pidof sleep 5); kill $slp") },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_Left,   tagtoleft,      {0} },
	{ MODKEY|ShiftMask,             XK_Right,  tagtoright,     {0} },
	{ 0,            	        XF86XK_AudioMute, spawn, SHCMD("pactl set-sink-mute @DEFAULT_SINK@  toggle;slp=$(pidof sleep 5); kill $slp") },
	{ 0,                       	XF86XK_AudioLowerVolume, 	 spawn, SHCMD("pactl set-sink-volume @DEFAULT_SINK@ -3%;slp=$(pidof sleep 5); kill $slp")},
	{ 0,                       	XF86XK_AudioRaiseVolume, spawn, SHCMD("pactl set-sink-volume @DEFAULT_SINK@ +3%;slp=$(pidof sleep 5); kill $slp") },
  	{ 0,        			XF86XK_MonBrightnessUp,  spawn, SHCMD("brightnessctl set 6000+;slp=$(pidof sleep 5); kill $slp") }, //Install brightnessctl
	{ 0,       			XF86XK_MonBrightnessDown,spawn, SHCMD("brightnessctl set --min-value=1 6000-;slp=$(pidof sleep 5); kill $slp") },
	{ 0,       			XF86XK_AudioPlay,spawn, SHCMD("cmus-remote -u") },
	{ 0,       			XK_Print,spawn, SHCMD("gnome-screenshot") },
	{ 0,       			XF86XK_Calculator,spawn, {.v = calculator} },
	{ MODKEY,       		XK_p,spawn, SHCMD("xrandr --output DP-1 --auto --right-of eDP-1") },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{MODKEY|ShiftMask,             	XK_q,      quit,           {0} },
	};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = calendar} },
	{ ClkStatusText,        0,              Button3,        spawn,          {.v = calendar} },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};


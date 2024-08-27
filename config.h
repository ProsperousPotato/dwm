#include <X11/XF86keysym.h>
/* See LICENSE file for copyright and license details. */

/* Constants */
#define TERMINAL "urxvtc"
#define BROWSER "librewolf-bin"

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 16;       /* snap pixel */
static const int swallowfloating    = 0;        /* 1 means swallow floating windows by default */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "cozette:size=12:autohint=true" };
static const char dmenufont[]       = "cozette:size=12:autohint=true";
static const char col_gray1[]       = "#000000"; // Colour of the background of the bar
static const char col_gray2[]       = "#444444"; // Colour of the border of the inactive window
static const char col_gray3[]       = "#bbbbbb"; // Colour of the foreground of the bar
static const char col_gray4[]       = "#000000"; // Colour of the wallpaper by default
static const char col_cyan[]        = "#bbbbbb"; // Colour of the border of the active window
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" }; // These are what is visually displayed in the bar, you can change them to whatever.

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class         instance          title           tags mask  isfloating  isterminal  noswallow  monitor */
	{ NULL,          "steamwebhelper", NULL,           0,         1,          0,           0,        -1 },
	{ "VirtualBox Machine", NULL,      NULL,           0,         1,          0,           0,        -1 },
	{ "Virt-manager", NULL,      NULL,           0,         1,          0,           0,        -1 },
	{ "qBittorrent", NULL,             NULL,           0,         1,          0,          -1,        -1 },
	{ "St",          NULL,             NULL,           0,         0,          1,           0,        -1 },
	{ "URxvt",       NULL,             NULL,           0,         1,          1,           0,        -1 },
	{ "Nsxiv",       NULL,             NULL,           0,         1,          0,           0,        -1 },
	{ "mpv",         NULL,             NULL,           0,         1,          0,           0,        -1 },
	{ NULL,          NULL,             "Event Tester", 0,         0,          0,           1,        -1 },
};

/* layout(s) */
static const float mfact     = 0.50; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[T]",      tile },    /* first entry is default */
	{ "[F]",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
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
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { TERMINAL, NULL };
static const char *volumeup[] = { "amixer", "sset", "Master", "5%+", NULL };
static const char *volumedown[] = { "amixer", "sset", "Master", "5%-", NULL };
static const char *volumetoggle[] = { "amixer", "sset", "Master", "toggle", NULL };
static const char *mictoggle[] = { "amixer", "sset", "Capture", "toggle", NULL};
static const char *brightnessup[] = { "xbacklight", "-inc", "3", NULL };
static const char *brightnessdown[] = { "xbacklight", "-dec", "3", NULL };
static const char *fasterbrightnessup[] = { "xbacklight", "-inc", "10", NULL };
static const char *fasterbrightnessdown[] = { "xbacklight", "-dec", "10", NULL };
static const char *slock[] = { "slock", NULL };
static const char *browser[] = { BROWSER, NULL };
static const char *steam[] = { "steam", NULL };
static const char *discord[] = { "discord", NULL };


static const Key keys[] = {
	/* modifier                     key           function        argument */
	{ MODKEY,                       XK_d,         spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_space,     spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_b,         togglebar,      {0} },
	{ MODKEY,                       XK_j,         focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,         focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,         incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_u,         incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,         setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,         setmfact,       {.f = +0.05} },
	{ Mod1Mask,                     XK_Tab,       zoom,           {0} },
	{ MODKEY,                       XK_Tab,       view,           {0} },
	{ MODKEY,                       XK_q,         killclient,     {0} },
	{ MODKEY,                       XK_t,         setlayout,      {.v = &layouts[0]} }, 
	{ MODKEY,                       XK_f,         setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,         setlayout,      {.v = &layouts[2]} },
	{ MODKEY|ShiftMask,             XK_Return,    setlayout,      {0} },
	{ MODKEY,                       XK_Return,    togglefloating, {0} },
	{ MODKEY,                       XK_0,         view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,         tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,     focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period,    focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,     tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period,    tagmon,         {.i = +1 } },
	TAGKEYS(                        XK_1,                         0)
	TAGKEYS(                        XK_2,                         1)
	TAGKEYS(                        XK_3,                         2)
	TAGKEYS(                        XK_4,                         3)
	TAGKEYS(                        XK_5,                         4)
	TAGKEYS(                        XK_6,                         5)
	TAGKEYS(                        XK_7,                         6)
	TAGKEYS(                        XK_8,                         7)
	TAGKEYS(                        XK_9,                         8)
	{ MODKEY|ShiftMask,             XK_q,        quit,            {0} },
  /* Non-default commands i.e. commands added in by me and patches */
	{ MODKEY|ShiftMask,             XK_j,                         rotatestack,    {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_k,                         rotatestack,    {.i = -1 } },
    { MODKEY|ShiftMask,             XK_m,                         spawn,          {.v = (const char*[]){ TERMINAL, "-e", "neomutt", NULL } }},
    { MODKEY|ShiftMask,             XK_h,                         spawn,          {.v = (const char*[]){ TERMINAL, "-e", "htop", NULL } }},
    { MODKEY|ShiftMask,             XK_e,                         spawn,          {.v = (const char*[]){ TERMINAL, "-e", "lfub", NULL } }},
	{ MODKEY,                       XK_Print,                     spawn,          SHCMD("scrot -q 100 ~/Pictures/%Y-%m.jpg") },
	{ MODKEY,                       XK_Up,                        spawn,          {.v = volumeup } },
	{ MODKEY,                       XK_Down,                      spawn,          {.v = volumedown } },
	{ MODKEY,                       XK_Right,                     spawn,          {.v = fasterbrightnessup } },
	{ MODKEY,                       XK_Left,                      spawn,          {.v = fasterbrightnessdown } },
	{ MODKEY|ControlMask,           XK_Right,                     spawn,          {.v = brightnessup } },
	{ MODKEY|ControlMask,           XK_Left,                      spawn,          {.v = brightnessdown } },
    { 0,                            XF86XK_AudioRaiseVolume,      spawn,          {.v = volumeup } },
    { 0,                            XF86XK_AudioLowerVolume,      spawn,          {.v = volumedown } },
	{ 0,                            XF86XK_AudioMute,             spawn,          {.v = volumetoggle } },
	{ 0,                            XF86XK_MonBrightnessUp,       spawn,          {.v = fasterbrightnessup } },
	{ 0,                            XF86XK_MonBrightnessDown,     spawn,          {.v = fasterbrightnessdown } },
	{ 0|ControlMask,                XF86XK_MonBrightnessUp,       spawn,          {.v = brightnessup } },
	{ 0|ControlMask,                XF86XK_MonBrightnessDown,     spawn,          {.v = brightnessdown } },
	{ 0,                            XF86XK_AudioMicMute,          spawn,          {.v = mictoggle } },
	{ MODKEY|ShiftMask,             XK_w,                         spawn,          {.v = browser } },
	{ MODKEY|ShiftMask,             XK_s,                         spawn,          {.v = steam } },
	{ MODKEY|ShiftMask,             XK_d,                         spawn,          {.v = discord } },
	{ Mod1Mask|ControlMask,         XK_Delete,                    spawn,          {.v = slock } },
	{ MODKEY|ShiftMask,             XK_v,                         spawn,          SHCMD("~/.local/bin/./bookmarkthis") },
	{ MODKEY,                       XK_v,                         spawn,          SHCMD("setxkbmap gb && xdotool type $(grep -v '^#' ~/.local/bin/bookmarksfile | dmenu -i -l 50)") },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
//	{ ClkTagBar,            0,              Button1,        view,           {0} },
//	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
//	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
//	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};


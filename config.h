/* See LICENSE file for copyright and license details. */

/* Constants */
#define TERMINAL "st"
#define BROWSER "chromium"

/* appearance */
static const unsigned int borderpx  = 3;        /* border pixel of windows */
static const unsigned int snap      = 8;       /* snap pixel */
static const int swallowfloating    = 1;        /* 1 means swallow floating windows by default */
static const char col_gray1[]       = "#000000";
static const char col_gray2[]       = "#000000";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_float[]       = "#191970";
static const char col_cyan[]        = "#bbbbbb";
static const char *colors[][4]      = {
	/*               fg         bg         border     float */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2, col_gray2 },
	[SchemeSel]  = { col_gray1, col_cyan,  col_cyan,  col_float  },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class         instance          title           tags mask  isfloating  isterminal  noswallow  monitor */
    { "steam",       "steamwebhelper", NULL,           0,         1,          0,          0,         -1 },
    { "Steam",       "Steam",          NULL,           0,         1,          0,          0,         -1 },
    { "steam",       "steamwebhelper", "Steam",        0,         0,          0,          0,         -1 },
    { "steam",       NULL,         "Steam Settings",   0,         1,          0,          0,         -1 },
    { "qemu-system-x86_64","qemu-system-x86_64",NULL,  0,         1,          0,          0,         -1 },
    { "Virt-manager",NULL,             NULL,           0,         0,          0,          0,         -1 },
    { "qBittorrent", NULL,             NULL,           0,         1,          0,          0,         -1 },
    { "qBittorrent", "qbittorrent",    NULL,           0,         1,          0,          0,         -1 },
    { "St",          "st",             NULL,           0,         0,          1,          1,         -1 },
    { "stfloat",     NULL,             NULL,           0,         1,          1,          1,         -1 },
    { "mpv",         NULL,             NULL,           0,         1,          0,          0,         -1 },
    { "Nsxiv",       NULL,             NULL,           0,         1,          0,          0,         -1 },
    { "scrcpy",      NULL,             NULL,           0,         1,          0,          0,         -1 },
    { "steam_app_1237950","steam_app_1237950",NULL,    0,         1,          0,          1,         -1 },
    { NULL,          NULL,             "Event Tester", 0,         0,          0,          1,         -1 },
};

/* layout(s) */
static const float mfact     = 0.5; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 0; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ NULL,      tile },    /* first entry is default */
    { NULL,      monocle },
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
static const char *termcmd[]  = { TERMINAL, NULL };

#include "quicksearch.c"
#include <X11/XF86keysym.h>
static const Key keys[] = {
	/* modifier                     key        function        argument */
    { MODKEY,                       XK_space,  spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_d,      spawn,          SHCMD("dmenu_run") },
	{ Mod1Mask,                     XK_space,  spawn,          SHCMD(TERMINAL" -c stfloat") },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_u,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.01} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.01} },
	{ Mod1Mask,                     XK_Tab,    zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY,                       XK_q,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[1]} },
	{ Mod1Mask,                     XK_f,      togglefloating, {0} },
    { MODKEY,                       XK_f,      togglefullscr,  {0} },
	{ MODKEY,                       XK_grave,  view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_grave,  tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	{ MODKEY|ShiftMask,             XK_End,    quit,           {0} },
	{ MODKEY|ShiftMask,             XK_r,      quit,           {1} }, 

	{ MODKEY,                       XK_e,      spawn,          SHCMD(TERMINAL" -e mc --nosubshell") },
	{ Mod1Mask,                     XK_e,      spawn,          SHCMD(TERMINAL" -c stfloat -e mc --nosubshell") },
	{ Mod1Mask,                     XK_m,      spawn,          SHCMD(TERMINAL" -c stfloat -e neomutt") },
	{ Mod1Mask,                     XK_n,      spawn,          SHCMD(TERMINAL" -c stfloat -e newsboat") },
	{ Mod1Mask|ShiftMask,           XK_p,      spawn,          SHCMD(TERMINAL" -c stfloat -e pulsemixer") },
	{ MODKEY,                       XK_Escape, spawn,          SHCMD(TERMINAL" -e htop") },
	{ Mod1Mask,                     XK_Escape, spawn,          SHCMD(TERMINAL" -c stfloat -e htop") },
	{ Mod1Mask,                     XK_t,      spawn,          SHCMD(TERMINAL" -c stfloat -e watch -n 1 transmission-remote -l") },
    { MODKEY,                       XK_x,      spawn,          SHCMD("xkill") },
    { MODKEY,                       XK_s,      spawn,          SHCMD("steam") },
    { MODKEY|ShiftMask,             XK_s,      spawn,          SHCMD("pkill -9 steam") },
    { MODKEY,                       XK_w,      spawn,          SHCMD(BROWSER) },
	{ 0,          XF86XK_AudioRaiseVolume,     spawn,          SHCMD("amixer sset Master 5%+") },
	{ 0,          XF86XK_AudioLowerVolume,     spawn,          SHCMD("amixer sset Master 5%-") },
	{ 0,                   XF86XK_AudioMute,   spawn,          SHCMD("amixer sset Master toggle") },
	{ 0,          XF86XK_MonBrightnessUp,      spawn,          SHCMD("xbacklight -inc 10") },
	{ 0,        XF86XK_MonBrightnessDown,      spawn,          SHCMD("xbacklight -dec 10") },
    { MODKEY,                       XK_Print,  spawn,          SHCMD("maimpick") },

    { ControlMask,                  XK_F1,     spawn,          SHCMD("amixer sset Master toggle") },
	{ ControlMask,                  XK_F2,     spawn,          SHCMD("amixer sset Master 5%-") },
    { ControlMask,                  XK_F3,     spawn,          SHCMD("amixer sset Master 5%+") },

	{ MODKEY,                       XK_p,      quicksearch,    {0} }, 
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
};

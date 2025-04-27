/* See LICENSE file for copyright and license details. */

/* Constants */
#define TERMINAL "st"
#define BROWSER "srch"

/* appearance */
static const unsigned int borderpx  = 3;        /* border pixel of windows */
static const unsigned int snap      = 16;       /* snap pixel */
static const unsigned int minwsz    = 20;       /* Minimum height of a client for smfact */
static const int swallowfloating    = 1;
static const int showbar            = 0;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "Bm437 IBM VGA 8x16:pixelsize=16, fontawesome:size=16" };
static const char dmenufont[]       = "Bm437 IBM VGA 8x16:pixelsize=16, fontawesome:size=16";
static const char col_gray1[]       = "#000000";
static const char col_gray2[]       = "#000000";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
// static const char col_cyan[]        = "#FF8C00"; /* orange */
// static const char col_cyan[]        = "#2f9b85"; /* manjaro green */
static const char col_cyan[]        = "#54487A"; /* gentoo purple */
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
	[SchemeStatus]  = { col_gray3, col_gray1,  "#000000"  }, // Statusbar right {text,background,not used but cannot be empty}
	[SchemeTagsSel]  = { col_gray3, col_cyan,  "#000000"  }, // Tagbar left selected {text,background,not used but cannot be empty}
	[SchemeTagsNorm]  = { col_cyan, col_gray1,   "#000000"  }, // Tagbar left unselected {text,background,not used but cannot be empty}
	[SchemeInfoSel]  = { col_gray3, col_cyan,  "#000000"  }, // infobar middle  selected {text,background,not used but cannot be empty}
	[SchemeInfoNorm]  = { col_cyan, col_gray1,  "#000000"  }, // infobar middle  unselected {text,background,not used but cannot be empty}
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class         instance          title           tags mask  isfloating  isterminal  noswallow  monitor */
	{ "Thunar",      "thunar",         NULL,           0,         1,          0,          0,         -1 },
    { "steam",       "steamwebhelper", NULL,           0,         1,          0,          0,         -1 },
    { "Steam",       "Steam",          NULL,           0,         1,          0,          0,         -1 },
    { "steam",       "steamwebhelper", "Steam",        0,         0,          0,          0,         -1 },
    { "steam",       NULL,         "Steam Settings",   0,         1,          0,          0,         -1 },
    { "qemu-system-x86_64","qemu-system-x86_64",NULL,  0,         1,          0,          0,         -1 },
    { "Virt-manager",NULL,             NULL,           0,         0,          0,          0,         -1 },
    { "qBittorrent", NULL,             NULL,           0,         1,          0,          0,         -1 },
    { "qBittorrent", "qbittorrent",    NULL,           0,         1,          0,          0,         -1 },
    { "St",          "st",             NULL,           0,         0,          1,          1,         -1 },
    { "stfloat",     "st",             NULL,           0,         1,          1,          1,         -1 },
    { "mpv",         NULL,             NULL,           0,         1,          0,          0,         -1 },
    { "Nsxiv",       NULL,             NULL,           0,         1,          0,          0,         -1 },
    { "scrcpy",      NULL,             NULL,           0,         1,          0,          0,         -1 },
    { NULL,          NULL,             "Event Tester", 0,         0,          0,          1,         -1 },
};

/* layout(s) */
static const float mfact     = 0.50; /* factor of master area size [0.05..0.95] */
static const float smfact    = 0.00; /* factor of tiled clients [0.00..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 0; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
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

#include <X11/XF86keysym.h>
static const Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_d,      spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_space,  spawn,          {.v = termcmd } },
	{ MODKEY|ShiftMask,             XK_space,  spawn,          SHCMD(TERMINAL" -e su") },
	{ Mod1Mask,                     XK_space,  spawn,          SHCMD(TERMINAL" -c stfloat") },
	{ Mod1Mask|ShiftMask,           XK_space,  spawn,          SHCMD(TERMINAL" -c stfloat -e su") },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_u,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = -1 } },
	{ MODKEY|ControlMask,           XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY|ControlMask,           XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY|ControlMask,           XK_k,      setsmfact,      {.f = +0.05} },
	{ MODKEY|ControlMask,           XK_j,      setsmfact,      {.f = -0.05} },
    { MODKEY,                       XK_h,      viewprev,       {0} },
    { MODKEY,                       XK_l,      viewnext,       {0} },
    { MODKEY|ShiftMask,             XK_h,      tagtoprev,      {0} },
    { MODKEY|ShiftMask,             XK_l,      tagtonext,      {0} },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ Mod1Mask,                     XK_Tab,    zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY,                       XK_q,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	// { MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	// { MODKEY,                       XK_Return, setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_f,      togglefloating, {0} },
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
	{ MODKEY|ShiftMask,             XK_e,      spawn,          SHCMD(TERMINAL" -c stfloat -e su -c 'mc --nosubshell'") },
	{ MODKEY|ShiftMask,             XK_m,      spawn,          SHCMD(TERMINAL" -e neomutt") },
	{ MODKEY,                       XK_n,      spawn,          SHCMD(TERMINAL" -e newsboat") },
	{ MODKEY,                       XK_Escape, spawn,          SHCMD(TERMINAL" -e gotop") },
	{ Mod1Mask,                     XK_Escape, spawn,          SHCMD(TERMINAL" -c stfloat -e gotop") },
    { MODKEY,                       XK_x,      spawn,          SHCMD("xkill") },
    { MODKEY,                       XK_s,      spawn,          SHCMD("steam") },
    { MODKEY|ShiftMask,             XK_s,      spawn,          SHCMD("pkill -9 steam") },
    { Mod1Mask|ControlMask,         XK_Delete, spawn,          SHCMD("slock") },
    { MODKEY,                       XK_w,      spawn,          SHCMD(BROWSER) },
	{ 0,          XF86XK_AudioRaiseVolume,     spawn,          SHCMD("amixer sset Master 5%+") },
	{ 0,          XF86XK_AudioLowerVolume,     spawn,          SHCMD("amixer sset Master 5%-") },
	{ 0,                   XF86XK_AudioMute,   spawn,          SHCMD("amixer sset Capture Toggle") },
	{ 0,          XF86XK_MonBrightnessUp,      spawn,          SHCMD("xbacklight -inc 10") },
	{ 0,        XF86XK_MonBrightnessDown,      spawn,          SHCMD("xbacklight -dec 10") },
    { MODKEY,                       XK_Print,  spawn,          SHCMD("maimpick") },

	{ MODKEY,                       XK_Down,   moveresize,     {.v = "0x 25y 0w 0h" } },
	{ MODKEY,                       XK_Up,     moveresize,     {.v = "0x -25y 0w 0h" } },
	{ MODKEY,                       XK_Right,  moveresize,     {.v = "25x 0y 0w 0h" } },
	{ MODKEY,                       XK_Left,   moveresize,     {.v = "-25x 0y 0w 0h" } },
	{ MODKEY|ShiftMask,             XK_Down,   moveresize,     {.v = "0x 0y 0w 25h" } },
	{ MODKEY|ShiftMask,             XK_Up,     moveresize,     {.v = "0x 0y 0w -25h" } },
	{ MODKEY|ShiftMask,             XK_Right,  moveresize,     {.v = "0x 0y 25w 0h" } },
	{ MODKEY|ShiftMask,             XK_Left,   moveresize,     {.v = "0x 0y -25w 0h" } },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
};

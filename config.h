/* See LICENSE file for copyright and license details. */

/* Constants */
#define TERMINAL "st"
#define BROWSER "firefox"

/* appearance */
static const unsigned int borderpx  = 3;        /* border pixel of windows */
static const unsigned int snap      = 12;       /* snap pixel */
static const int refreshrate        = 120;
static const int swallowfloating    = 1;        /* 1 means swallow floating windows by default */
static const int mouse_default      = 0;        /* 1 means enable mouse by default */
static const char col_gray1[]       = "#000000";
static const char col_gray2[]       = "#bbbbbb";
static const char col_float[]       = "#770000";
static const char col_master[]      = "#FF9F1C";
static const char *colors[][5]      = {
	/*               fg         bg          border      float      master */
	[SchemeNorm] = { col_gray2, col_gray1,  col_gray1,  col_gray1, col_gray1   },
	[SchemeSel]  = { col_gray1, col_gray2,  col_gray2,  col_float, col_master  },
};

static const char *const autostart[] = {
/*  program     arguments           options     null terminator  */
    "xhidecursor",  "",             "",         NULL,
    NULL
};

/* tagging */
static const char *tags[] = { "0", "1", "2" };

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
    { "st-256color", "st-256color",    NULL,           0,         0,          1,          1,         -1 },
    { "stfloat",     NULL,             NULL,           0,         1,          1,          1,         -1 },
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
    { NULL,      NULL },
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

#include <X11/XF86keysym.h>
static const Key keys[] = {
	/* modifier                     key        function        argument */
    { MODKEY,                       XK_space,  spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_d,      spawn,          SHCMD("dmenu_run") },
	{ Mod1Mask,                     XK_space,  spawn,          SHCMD(TERMINAL" -c stfloat") },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_minus,  incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_equal,  incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.01} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.01} },
	{ Mod1Mask,                     XK_Tab,    zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY,                       XK_q,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                   XK_BackSpace,  setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
    { MODKEY|ShiftMask,             XK_f,      togglefullscr,  {0} },
	{ MODKEY,                       XK_f,      togglefloating, {0} },
	{ MODKEY,                       XK_grave,  view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_grave,  tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },

	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)

	{ MODKEY|ShiftMask,             XK_End,    quit,           {0} },
	{ MODKEY|ShiftMask,             XK_r,      quit,           {1} }, 

	{ Mod1Mask,                     XK_m,      spawn,          SHCMD(TERMINAL" -c stfloat -e neomutt") },
	{ Mod1Mask,                     XK_n,      spawn,          SHCMD(TERMINAL" -c stfloat -e newsboat") },
	{ MODKEY,                       XK_Escape, spawn,          SHCMD(TERMINAL" -e htop") },
	{ Mod1Mask,                     XK_Escape, spawn,          SHCMD(TERMINAL" -c stfloat -e htop") },
    { MODKEY,                       XK_x,      spawn,          SHCMD("xkill") },
    { MODKEY,                       XK_w,      spawn,          SHCMD(BROWSER) },

#ifdef __linux__
    { MODKEY,                       XK_s,      spawn,          SHCMD("steam -dev") },
    { MODKEY|ShiftMask,             XK_s,      spawn,          SHCMD("pkill -9 steam") },
    { 0,          XF86XK_AudioRaiseVolume,     spawn,          SHCMD("amixer sset Master 5%+") },
    { 0,          XF86XK_AudioLowerVolume,     spawn,          SHCMD("amixer sset Master 5%-") },
    { 0,                 XF86XK_AudioMute,     spawn,          SHCMD("amixer sset Master toggle") },
    { Mod1Mask,                     XK_t,      spawn,          SHCMD(TERMINAL" -c stfloat -e watch -n 1 transmission-remote -l") },
#endif

#ifdef __OpenBSD__
    { Mod1Mask,                     XK_t,      spawn,          SHCMD(TERMINAL" -c stfloat -e gnuwatch -n 1 transmission-remote -l") },
#endif

	{ 0,          XF86XK_MonBrightnessUp,      spawn,          SHCMD("xbacklight -inc 10") },
	{ 0,        XF86XK_MonBrightnessDown,      spawn,          SHCMD("xbacklight -dec 10") },
    { MODKEY,                       XK_Print,  spawn,          SHCMD("maimpick") },
    { MODKEY,                       XK_c,      spawn,          SHCMD("pgrep xcompmgr && pkill -9 xcompmgr || xcompmgr &") },
    { MODKEY|ShiftMask,             XK_k,      spawn,          SHCMD(TERMINAL" -c stfloat -e fkill") },

	{ MODKEY,                       XK_p,      search,         {.i = 0} }, 
	{ MODKEY|ShiftMask,             XK_p,      search,         {.i = 1} }, 
	{ MODKEY|ShiftMask,             XK_q,      search,         {.i = 2} }, 

	{ MODKEY,                       XK_o,      togglemouse,    {0} }, 

	{ MODKEY,                       XK_KP_Down,    moveresize,     {.v = "0x 15y 0w 0h" } },
	{ MODKEY,                       XK_KP_Up,      moveresize,     {.v = "0x -15y 0w 0h" } },
	{ MODKEY,                       XK_KP_Right,   moveresize,     {.v = "15x 0y 0w 0h" } },
	{ MODKEY,                       XK_KP_Left,    moveresize,     {.v = "-15x 0y 0w 0h" } },
	{ MODKEY,                       XK_KP_Begin,   togglefloating, {0} },
    { MODKEY|ShiftMask,             XK_KP_Begin,   togglefullscr,  {0} },

	{ MODKEY,                       XK_KP_Home,    moveresize,     {.v = "-15x -15y 0w 0h" } }, /* Diagonal Left && Up */
	{ MODKEY,                       XK_KP_Prior,   moveresize,     {.v = "15x -15y 0w 0h" } }, /* Diagonal Right && Up */
	{ MODKEY,                       XK_KP_End,     moveresize,     {.v = "-15x 15y 0w 0h" } }, /* Diagonal Left && Down */
	{ MODKEY,                       XK_KP_Next,    moveresize,     {.v = "15x 15y 0w 0h" } }, /* Diagonal Right && Down */

	{ MODKEY|ShiftMask,             XK_KP_Down,    moveresize,     {.v = "0x 0y 0w 15h" } },
	{ MODKEY|ShiftMask,             XK_KP_Up,      moveresize,     {.v = "0x 0y 0w -15h" } },
	{ MODKEY|ShiftMask,             XK_KP_Right,   moveresize,     {.v = "0x 0y 15w 0h" } },
	{ MODKEY|ShiftMask,             XK_KP_Left,    moveresize,     {.v = "0x 0y -15w 0h" } },

	{ MODKEY|ShiftMask,             XK_KP_Home,    moveresize,     {.v = "0x 0y -15w -15h" } }, /* Diagonal Left && Up */
	{ MODKEY|ShiftMask,             XK_KP_Prior,   moveresize,     {.v = "0x 0y 15w -15h" } }, /* Diagonal Right && Up */
	{ MODKEY|ShiftMask,             XK_KP_End,     moveresize,     {.v = "0x 0y -15w 15h" } }, /* Diagonal Left && Down */
	{ MODKEY|ShiftMask,             XK_KP_Next,    moveresize,     {.v = "0x 0y 15w 15h" } }, /* Diagonal Right && Down */
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
};

/* See LICENSE file for copyright and license details. */

/* Constants */
#define TERMINAL "st"
#define BROWSER "glide"

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 12;       /* snap pixel */
static const int refreshrate        = 200;      /* limits the speed of moving && resizing windows */
static const int swallowfloating    = 1;        /* 1 means swallow floating windows by default */
static const int mousedefault       = 0;        /* 1 means enable mouse by default */
static const char *colors[][3]      = {
	/*               border      float      master      */
	[SchemeNorm] = { "#000000",  "#000000", "#000000"   },
	[SchemeSel]  = { "#bbbbbb",  "#770000", "#FF8C00"   },
};

/* autostart */
static const char *const autostart[] = {
/*  program         arguments       options     null terminator  */
	"xhidecursor",  "",             "",         NULL,
	"hsetroot",     "-fill",       "/usr/share/backgrounds/linux.png",    NULL,
	"xset",         "m",            "1 1",      NULL,
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
	{ "st-256color", "st-256color",    NULL,           0,         0,          1,          0,         -1 },
	{ "stfloat",     "st-256color",    NULL,           0,         1,          1,          0,         -1 },
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
	{ NULL,      bstack },
};

/* key definitions */
#define MODKEY Mod4Mask
#define MODKEYTWO Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

#include <X11/XF86keysym.h>
static const Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_space,  spawn,          {.v = (const char*[]){ TERMINAL, NULL } } },
	{ MODKEY,                       XK_d,      spawn,          {.v = (const char*[]){ "dmenu_run", NULL } } },
	{ MODKEYTWO,                    XK_space,  spawn,          {.v = (const char*[]){ TERMINAL, "-c", "stfloat", NULL } } },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_j,      movestack,      {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_k,      movestack,      {.i = -1 } },
	{ MODKEY,                       XK_minus,  incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_equal,  incnmaster,     {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_equal,  incnmaster,     {.i =  0 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.02} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.02} },
	{ MODKEY|ShiftMask,             XK_h,      setcfact,       {.f = +0.10} },
	{ MODKEY|ShiftMask,             XK_l,      setcfact,       {.f = -0.10} },
	{ MODKEY,                       XK_o,      setcfact,       {.f =  0.00} },
	{ MODKEYTWO,                    XK_Tab,    zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY,                       XK_q,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY|ShiftMask,             XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_u,      setlayout,      {.v = &layouts[3]} },
	{ MODKEY|ShiftMask,             XK_Return, togglefullscr,  {0} },
	{ MODKEY,                       XK_Return, togglefloating, {0} },
	{ MODKEYTWO|ShiftMask,          XK_Return, spanmon,        {0} },
	{ MODKEY,                       XK_grave,  view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_grave,  tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },

	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)

	{ MODKEY|ShiftMask|ControlMask, XK_BackSpace,    quit,     {0} },
	{ MODKEY|ShiftMask,             XK_BackSpace,    quit,     {1} }, 

	{ MODKEY,                       XK_n,         spawn,       {.v = (const char*[]){ TERMINAL, "-e", "newsboat", NULL } } },
	{ MODKEY,                       XK_Escape,    spawn,       {.v = (const char*[]){ TERMINAL, "-e", "htop", NULL } } },
	{ MODKEYTWO,                    XK_Escape,    spawn,       {.v = (const char*[]){ TERMINAL, "-c", "stfloat", "-e", "htop", NULL } } },
	{ MODKEY,                       XK_w,         spawn,       {.v = (const char*[]){ BROWSER, NULL } } },
	{ MODKEY,                       XK_e,         resetfacts,  {0} },
	{ MODKEY,                       XK_a,         swapfocus,   {0} },

	{ MODKEY,                       XK_s,         spawn,       {.v = (const char*[]){ "steam", "-dev", NULL } } },

	{ 0,         XF86XK_AudioRaiseVolume,         spawn,       {.v = (const char*[]){ "amixer", "sset", "Master", "5%+", "1>", "/dev/null", NULL } } },
	{ 0,         XF86XK_AudioLowerVolume,         spawn,       {.v = (const char*[]){ "amixer", "sset", "Master", "5%-", "1>", "/dev/null", NULL } } },
	{ 0,                XF86XK_AudioMute,         spawn,       {.v = (const char*[]){ "amixer", "sset", "Master", "toggle", "1>", "/dev/null", NULL } } },

	{ MODKEY|ShiftMask,             XK_s,         spawn,       {.v = (const char*[]){ "maimpick", NULL } } },

	{ MODKEY,                       XK_p,         search,      {.i = 0} },
	{ MODKEY|ShiftMask,             XK_p,         search,      {.i = 1} },
	{ MODKEY|ShiftMask,             XK_q,         search,      {.i = 2} },

	{ MODKEY,                       XK_b,         togglemouse, {0} },

	{ MODKEY|ShiftMask,             XK_slash,     tagmon,      {.i = +1 } },
	{ MODKEY,                       XK_slash,     focusmon,    {.i = +1 } },
	{ MODKEY,                       XK_backslash, swapmon,     {0} },

	// move (rightmost 'wasd' like cluster of keys in ISO layout)
	{ MODKEY,                   XK_apostrophe,  moveresize,     {.v = "0x 20y 0w 0h" } },
	{ MODKEY,                   XK_bracketleft, moveresize,     {.v = "0x -20y 0w 0h" } },
	{ MODKEY,                   XK_numbersign,  moveresize,     {.v = "20x 0y 0w 0h" } },
	{ MODKEY,                   XK_semicolon,   moveresize,     {.v = "-20x 0y 0w 0h" } },

	// resize (rightmost 'wasd' like cluster of keys in ISO layout)
	{ MODKEY|ShiftMask,         XK_apostrophe,  moveresize,     {.v = "0x 0y 0w 20h" } },
	{ MODKEY|ShiftMask,         XK_bracketleft, moveresize,     {.v = "0x 0y 0w -20h" } },
	{ MODKEY|ShiftMask,         XK_numbersign,  moveresize,     {.v = "0x 0y 20w 0h" } },
	{ MODKEY|ShiftMask,         XK_semicolon,   moveresize,     {.v = "0x 0y -20w 0h" } },
};

#define Button9 9 // Highest side mouse button
#define Button8 8 // Lowest side mouse button

/* button definitions */
static const Button buttons[] = {
	/* click                event mask         button          function        argument */
	{ ClkClientWin,         MODKEY|ShiftMask,  Button1,        movemouse,      {0} }, // regular window move
	{ ClkClientWin,         MODKEY,            Button1,        movemouse,      {.i = 1} }, // tiled window move
	{ ClkClientWin,         MODKEY,            Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,            Button3,        clientresize,   {0} },

	/* Focus windows with scroll wheel */
	{ ClkClientWin,         MODKEY,            Button4,        focusstack,     {.i = -1 } },
	{ ClkClientWin,         MODKEY,            Button5,        focusstack,     {.i = +1 } },
	{ ClkRootWin,           MODKEY,            Button4,        focusstack,     {.i = -1 } },
	{ ClkRootWin,           MODKEY,            Button5,        focusstack,     {.i = +1 } },

	{ ClkClientWin,         MODKEY|ShiftMask,  Button4,        movestack,      {.i = -1 } },
	{ ClkClientWin,         MODKEY|ShiftMask,  Button5,        movestack,      {.i = +1 } },
	{ ClkRootWin,           MODKEY|ShiftMask,  Button4,        movestack,      {.i = -1 } },
	{ ClkRootWin,           MODKEY|ShiftMask,  Button5,        movestack,      {.i = +1 } },

	/* Focus monitors with side mouse buttons */
	{ ClkClientWin,         MODKEY,            Button8,        focusmon,       {.i = -1 } },
	{ ClkClientWin,         MODKEY,            Button9,        focusmon,       {.i = +1 } },
	{ ClkRootWin,           MODKEY,            Button8,        focusmon,       {.i = -1 } },
	{ ClkRootWin,           MODKEY,            Button9,        focusmon,       {.i = +1 } },

	{ ClkClientWin,         MODKEY|ShiftMask,  Button8,        tagmon,         {.i = -1 } },
	{ ClkClientWin,         MODKEY|ShiftMask,  Button9,        tagmon,         {.i = +1 } },
	{ ClkRootWin,           MODKEY|ShiftMask,  Button8,        tagmon,         {.i = -1 } },
	{ ClkRootWin,           MODKEY|ShiftMask,  Button9,        tagmon,         {.i = +1 } },
};

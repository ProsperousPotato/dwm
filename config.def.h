/* See LICENSE file for copyright and license details. */

/* Constants */
#define TERMINAL "st"
#define BROWSER "floorp"
#define FILE_EXPLORER "pcmanfm"
#define HOME "/home/arch/"
/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "monospace:size=10" };
static const char dmenufont[]       = "monospace:size=10";
static const char col_gray1[]       = "#000000";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#000000";
static const char col_cyan[]        = "#bbbbbb";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
	{ "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.50; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[T]",      tile },    /* first entry is default */
	{ "[F]",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define PrintScreen 0xff61
#define RaiseVolume 0x1008ff13
#define LowerVolume 0x1008ff11
#define MuteVolume 0x1008ff12
#define BrightDown 0x1008ff03
#define BrightUp 0x1008ff02
#define MuteMic 0x1008ffb2
#define HomePage 0x1008ff18
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ Mod1Mask,                     KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { TERMINAL, NULL };
static const char *cmdprintscreen[]  = { "scrot", HOME".screenshots/%Y-%m.jpg", NULL };
static const char *volumeup[] = { "amixer", "sset", "Master", "5%+", NULL };
static const char *volumedown[] = { "amixer", "sset", "Master", "5%-", NULL };
static const char *volumetoggle[] = { "amixer", "sset", "Master", "toggle", NULL };
static const char *mictoggle[] = { "amixer", "sset", "Capture", "toggle", NULL};
static const char *brightnessup[] = { "brillo", "-q", "-A", "3", NULL };
static const char *brightnessdown[] = { "brillo", "-q", "-U", "3", NULL };
static const char *fasterbrightnessup[] = { "brillo", "-q", "-A", "10", NULL };
static const char *fasterbrightnessdown[] = { "brillo", "-q", "-U", "10", NULL };
static const char *slock[] = { "slock", NULL };
static const char *browser[] = { BROWSER, NULL };
static const char *files[] = { FILE_EXPLORER, NULL };
static const char *steam[] = { "steam", NULL };
static const char *discord[] = { "discord", NULL };


static const Key keys[] = {
	/* modifier                     key           function        argument */
	{ MODKEY,                       XK_d,         spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_Tab,       spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_b,         togglebar,      {0} },
	{ MODKEY,                       XK_j,         focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,         focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,         incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_u,         incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,         setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,         setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_space,     zoom,           {0} },
	{ MODKEY|ShiftMask,             XK_space,     view,           {0} },
	{ MODKEY,                       XK_q,         killclient,     {0} },
  { MODKEY,                       XK_t,         setlayout,      {.v = &layouts[0]} }, 
  { MODKEY,                       XK_f,         setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,         setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_Return,    setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_Return,    togglefloating, {0} },
	{ MODKEY,                       XK_0,         view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,         tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,     focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period,    focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,     tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period,    tagmon,         {.i = +1 } },
	{ MODKEY,                       PrintScreen,  spawn,          {.v = cmdprintscreen } },
	{ 0,                            RaiseVolume,  spawn,          {.v = volumeup } },
	{ 0,                            LowerVolume,  spawn,          {.v = volumedown } },
	{ MODKEY,                       XK_Up,        spawn,          {.v = volumeup } },
	{ MODKEY,                       XK_Down,      spawn,          {.v = volumedown } },
	{ MODKEY,                       XK_Right,     spawn,          {.v = brightnessup } },
  { MODKEY,                       XK_Left,      spawn,          {.v = brightnessdown } },
  { MODKEY|ControlMask,           XK_Right,     spawn,          {.v = fasterbrightnessup } },
  { MODKEY|ControlMask,           XK_Left,      spawn,          {.v = fasterbrightnessdown } },
	{ 0,                            MuteVolume,   spawn,          {.v = volumetoggle } },
	{ 0,                            BrightUp,     spawn,          {.v = brightnessup } },
	{ 0,                            BrightDown,   spawn,          {.v = brightnessdown } },
	{ 0|ControlMask,                BrightUp,     spawn,          {.v = fasterbrightnessup } },
	{ 0|ControlMask,                BrightDown,   spawn,          {.v = fasterbrightnessdown } },
  { 0,                            MuteMic,      spawn,          {.v = mictoggle } },
	{ MODKEY|ShiftMask,             XK_w,         spawn,          {.v = browser } },
	{ MODKEY|ShiftMask,             XK_e,         spawn,          {.v = files } },
	{ MODKEY|ShiftMask,             XK_s,         spawn,          {.v = steam } },
	{ MODKEY|ShiftMask,             XK_d,         spawn,          {.v = discord } },
  { Mod1Mask|ControlMask,         XK_Delete,    spawn,          {.v = slock } },
	{ MODKEY|ShiftMask,             XK_v,         spawn,          SHCMD("$HOME/scripts/./bookmarkthis.sh") },
	{ MODKEY,                       XK_v,         spawn,          SHCMD("xdotool type $(grep -v '^#' ~/.local/share/bookmarks/bookmarksfile | dmenu -i -l 50 | cut -d' ' -f1)") },
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


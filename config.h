/* See LICENSE file for copyright and license details. */

/* Constants */
#define TERMINAL "st"
#define BROWSER "librewolf"

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int snap      = 16;       /* snap pixel */
static const unsigned int gappx     = 5;        /* gaps between windows */
static const int swallowfloating    = 1;        /* 1 means swallow floating windows by default */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "CyberpunkWaifus:size=12:autohint=true, fontawesome:size=12" };
static const char dmenufont[]       = "CyberpunkWaifus:size=12:autohint=true, fontawesome:size=12";
static const char col_gray1[]       = "#000000"; 
static const char col_gray2[]       = "#bbbbbb"; 
static const char col_gray3[]       = "#4CAF50"; // Not selected
static const char col_gray4[]       = "#000000"; 
static const char col_cyan[]        = "#FF8C00"; // Selected
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray1 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
	[SchemeHid]  = { col_gray2, col_gray1,  col_gray1  },
	[SchemeStatus]  = { col_gray3, col_gray1,  "#000000"  }, // Statusbar right {text,background,not used but cannot be empty}
	[SchemeTagsSel]  = { col_cyan, col_gray1,  "#000000"  }, // Tagbar left selected {text,background,not used but cannot be empty}
	[SchemeTagsNorm]  = { col_gray3, col_gray1,  "#000000"  }, // Tagbar left unselected {text,background,not used but cannot be empty}
	[SchemeInfoSel]  = { col_cyan, col_gray1,  "#000000"  }, // infobar middle  selected {text,background,not used but cannot be empty}
	[SchemeInfoNorm]  = { col_gray3, col_gray1,  "#000000"  }, // infobar middle  unselected {text,background,not used but cannot be empty}
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5" }; // These are what is visually displayed in the bar, you can change them to whatever.

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class         instance          title           tags mask  isfloating  isterminal  noswallow  monitor */
    { "steam",       "steamwebhelper", NULL,           0,         1,          0,           0,        -1 },
    { "steam",       "steamwebhelper", "Steam",        0,         0,          0,           0,        -1 },
    { "steam",       NULL,         "Steam Settings",   0,         1,          0,           0,        -1 },
    { "qemu-system-x86_64","qemu-system-x86_64",NULL,  0,         1,          0,           0,        -1 },
    { "Virt-manager",NULL,             NULL,           0,         0,          0,           0,        -1 },
    { "qBittorrent", NULL,             NULL,           0,         1,          0,           0,        -1 },
    { "qBittorrent", "qbittorrent",    NULL,           0,         0,          0,           0,        -1 },
    { "St",          "st",             NULL,           0,         0,          1,           0,        -1 },
    { "XTerm",     "xterm",            NULL,           0,         0,          1,           0,        -1 },
    { "scrcpy",      NULL,             NULL,           0,         1,          0,           0,        -1 },
    { "LibreWolf",   "Alert",          NULL,           0,         1,          0,           0,        -1 },
    { NULL,          NULL,             "Event Tester", 0,         0,          0,           1,        -1 },
};

/* layout(s) */
static const float mfact     = 0.50; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 0; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "",      tile },    /* first entry is default */
	{ "",      NULL },    /* no layout function means floating behavior */
	{ "",      monocle },
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
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_gray4, "-sf", col_cyan, NULL };
static const char *termcmd[]  = { TERMINAL, NULL };
static const char *sutermcmd[]  = { TERMINAL,"-e", "su", NULL };


#include <X11/XF86keysym.h>
static const Key keys[] = {
	/* modifier           key                 function        argument */
    { MODKEY,             XK_d,               spawn,          {.v = dmenucmd } },
    { MODKEY,             XK_space,           spawn,          {.v = termcmd } },
    { MODKEY,             XK_b,               togglebar,      {0} },
    { MODKEY,             XK_j,               focusstackvis,  {.i = +1 } },
    { MODKEY,             XK_k,               focusstackvis,  {.i = -1 } },
    { MODKEY,             XK_i,               incnmaster,     {.i = +1 } },
    { MODKEY,             XK_u,               incnmaster,     {.i = -1 } },
    { MODKEY,             XK_o,               setmfact,       {.f = -0.05} },
    { MODKEY,             XK_p,               setmfact,       {.f = +0.05} },
    { Mod1Mask,           XK_Tab,             zoom,           {0} },
    { MODKEY,             XK_Tab,             view,           {0} },
    { MODKEY,             XK_q,               killclient,     {0} },
    { MODKEY,             XK_t,               setlayout,      {.v = &layouts[0]} }, 
    { MODKEY,             XK_m,               setlayout,      {.v = &layouts[2]} },
    { MODKEY|ShiftMask,   XK_Return,          setlayout,      {0} },
    { MODKEY,             XK_Return,          togglefloating, {0} },
    { MODKEY,             XK_grave,           view,           {.ui = ~0 } },
    { MODKEY|ShiftMask,   XK_grave,           tag,            {.ui = ~0 } },
    { MODKEY,             XK_comma,           focusmon,       {.i = -1 } },
    { MODKEY,             XK_period,          focusmon,       {.i = +1 } },
    { MODKEY|ShiftMask,   XK_comma,           tagmon,         {.i = -1 } },
    { MODKEY|ShiftMask,   XK_period,          tagmon,         {.i = +1 } },
    TAGKEYS(              XK_1,                               0)
    TAGKEYS(              XK_2,                               1)
    TAGKEYS(              XK_3,                               2)
    TAGKEYS(              XK_4,                               3)
    TAGKEYS(              XK_5,                               4)
    { MODKEY|ShiftMask,   XK_End,             quit,           {0} },

  /* Non-default commands i.e. commands added in by me and patches */
    { MODKEY|ShiftMask,             XK_space,                     spawn,          {.v = sutermcmd } },
    { MODKEY,                       XK_minus,                     setgaps,        {.i = -1 } },
    { MODKEY,                       XK_equal,                     setgaps,        {.i = +1 } },
    { MODKEY|ShiftMask,             XK_equal,                     setgaps,        {.i = 0  } },
    { MODKEY|ShiftMask,             XK_j,                         movestack,      {.i = +1 } },
    { MODKEY|ShiftMask,             XK_k,                         movestack,      {.i = -1 } },
    { MODKEY,                       XK_f,                         togglefullscr,  {0} },
    { MODKEY,                       XK_BackSpace,                 hide,           {0} },
    { MODKEY,                       XK_a,                         showall,        {0} },
    { MODKEY,                       XK_g,                         spawn,          SHCMD("dmenu_games") },
    { MODKEY|ShiftMask,             XK_m,                         spawn,          SHCMD(TERMINAL" -e neomutt")},
    { MODKEY|ShiftMask,             XK_n,                         spawn,          SHCMD(TERMINAL" -e nvim")},
    { MODKEY,                       XK_Escape,                    spawn,          SHCMD(TERMINAL" -e htop")},
    { MODKEY,                       XK_n,                         spawn,          SHCMD(TERMINAL" -e newsboat")},
    { MODKEY,                       XK_e,                         spawn,          SHCMD(TERMINAL" -e lfub")},
    { MODKEY,                       XK_slash,                     spawn,          SHCMD(TERMINAL" -e menu") },
    { MODKEY,                       XK_Print,                     spawn,          SHCMD("maimpick") },
    { MODKEY,                       XK_Up,                        spawn,          SHCMD("dwmvol up") },
    { MODKEY,                       XK_Down,                      spawn,          SHCMD("dwmvol down") },
    { MODKEY,                       XK_Right,                     spawn,          SHCMD("dwmlight up") },
    { MODKEY,                       XK_Left,                      spawn,          SHCMD("dwmlight down") },
    { 0,                            XF86XK_AudioRaiseVolume,      spawn,          SHCMD("dwmvol up") },
    { 0,                            XF86XK_AudioLowerVolume,      spawn,          SHCMD("dwmvol down") },
    { 0,                            XF86XK_AudioMute,             spawn,          SHCMD("dwmvol toggle") },
    { 0,                            XF86XK_MonBrightnessUp,       spawn,          SHCMD("dwmlight up") },
    { 0,                            XF86XK_MonBrightnessDown,     spawn,          SHCMD("dwmlight down") },
    { MODKEY,                       XK_F11,                       spawn,          SHCMD("dwmstats") },
    { MODKEY,                       XK_F12,                       spawn,          SHCMD("dwmext") },
    { MODKEY,                       XK_F8,                        spawn,          SHCMD("dwmnet") },
    { MODKEY,                       XK_s,                         spawn,          SHCMD("steam") },
    { Mod1Mask|ControlMask,         XK_Delete,                    spawn,          SHCMD("slock") },
    { MODKEY,                       XK_w,                         spawn,          SHCMD(BROWSER) },
    { MODKEY,                       XK_c,                         spawn,          SHCMD("cliphist add") },
    { MODKEY,                       XK_v,                         spawn,          SHCMD("cliphist sel") },
    { MODKEY,                       XK_x,                         spawn,          SHCMD("xkill") },
    { MODKEY,                       XK_h,                         viewprev,       {0} },
	{ MODKEY,                       XK_l,                         viewnext,  	  {0} },
    { MODKEY|ShiftMask,             XK_h,                         tagtoprev,      {0} },
	{ MODKEY|ShiftMask,             XK_l,                         tagtonext,  	  {0} },
    { MODKEY|ShiftMask,             XK_r,                         quit,           {1} },

    /* Unused keys */
    // { MODKEY,                       XK_f,         setlayout,      {.v = &layouts[1]} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
    { ClkWinTitle,          0,              Button2,        zoom,           {0} },
    { ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
    { ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
    { ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
    { ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
};


#include <X11/XF86keysym.h>
#include "push.c"
/* See LICENSE file for copyright and license details. */

/* appearance */
//static const char font[]           = "-*-terminus-medium-r-*-*-16-*-*-*-*-*-*-*";
static const char font[]            = "-*-terminus-*-*-*-*-*-*-*-*-*-*-*-*";
static const char normbordercolor[] = "#555555";
static const char normbgcolor[]     = "#202020";
static const char normfgcolor[]     = "#bbbbbb";
static const char selbordercolor[]  = "#2d84df";
static const char selbgcolor[]      = "#121212";
static const char selfgcolor[]      = "#ffffff";
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const Bool showbar           = True;     /* False means no bar */
static const Bool topbar            = True;     /* False means bottom bar */

/* tagging */
static const char *tags[] = { "base", "web", "data", "media", "dev", "gfx", "vbox" };

static const Rule rules[] = {
  /* class        instance    title                tags mask  isfloating  monitor */
  { "Gimp",       NULL,       NULL,                1 << 5,    True,        -1 },
  { "Firefox",    NULL,       NULL,                1 << 1,    False,       -1 },
  { "Thunar",     NULL,       NULL,                1 << 2,    False,       -1 },
  { "medit",      NULL,       NULL,                1 << 4,    False,       -1 },
  { "gPodder",    NULL,       NULL,                1 << 6,    False,       -1 },
  { "VirtualBox", NULL,       NULL,                1 << 6,    False,       -1 },
  { NULL,         NULL,       "VLC media player",  1 << 3,    False,        -1 },
};


/* layout(s) */
static const float mfact      = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster      = 1;    /* number of clients in master area */
static const Bool resizehints = False; /* True means respect size hints in tiled resizals */


static const Layout layouts[] = {
  /* symbol     arrange function */
  { "[]=",      tile },    /* first entry is default */
  { "><>",      NULL },    /* no layout function means floating behavior */
  { "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define ALTKEY Mod1Mask
#define CTRLKEY ControlMask

#define TAGKEYS(KEY,TAG) \
  { MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
  { MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
  { MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
  { MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static const char *dmenucmd[]   = { "dmenu_run", "-fn", font, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbgcolor, "-sf", selfgcolor, NULL };
static const char *termcmd[]    = { "urxvt", NULL };
static const char *browsercmd[] = { "firefox", NULL };
static const char *fmancmd[]    = { "thunar", NULL };
static const char *vboxcmd[]    = {"VirtualBox", "--startvm", "WinXP"};

/* bightness and volume */
static const char *brightup[]   = {"sudo", "acerbrightness", "up", NULL};
static const char *brightdown[] = {"sudo", "acerbrightness", "down", NULL};
static const char *volup[]      = {"amixer", "sset", "Master", "5%+", NULL};
static const char *voldown[]    = {"amixer", "sset", "Master", "5%-", NULL};

/* mpd */
static const char *mpcnext[]    = {"mpc", "next", NULL};
static const char *mpcprev[]    = {"mpc", "next", NULL};
static const char *mpctoggle[]  = {"mpc", "toggle", NULL};


static Key keys[] = {
  /* modifier                     key        function        argument */
  { MODKEY,                       XK_r,      spawn,          {.v = dmenucmd } },
  { MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },
  { MODKEY,                       XK_c,      spawn,          {.v = termcmd } },
  { MODKEY,                       XK_w,      spawn,          {.v = browsercmd } },
  { MODKEY,                       XK_v,      spawn,          {.v = vboxcmd } },

  { ALTKEY,                       XK_KP_Add,       spawn,    { .v = volup } },
  { ALTKEY,                       XK_KP_Subtract,  spawn,    { .v = voldown } },
  { CTRLKEY,                      XK_KP_Add,       spawn,    { .v = brightup } },
  { CTRLKEY,                      XK_KP_Subtract,  spawn,    { .v = brightdown } },

  { 0,                            XF86XK_AudioPlay, spawn,   { .v = mpctoggle } },
  { 0,                            XF86XK_AudioPrev, spawn,   { .v = mpcprev } },
  { 0,                            XF86XK_AudioNext, spawn,   { .v = mpcnext } },

  { MODKEY|ShiftMask,             XK_j,      pushdown,       {0} },
  { MODKEY|ShiftMask,             XK_k,      pushup,         {0} },

  { MODKEY|ShiftMask,             XK_b,      togglebar,      {0} },
  { MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
  { MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
  { MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
  { MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
  { MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
  { MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
  { MODKEY,                       XK_Return, zoom,           {0} },
  { MODKEY|ShiftMask,             XK_s,      zoom,           {0} },
  { MODKEY,                       XK_Tab,    view,           {0} },
  { MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
  { MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
  { MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
  { MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
  { MODKEY,                       XK_space,  setlayout,      {0} },
  { MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
  { MODKEY,                       XK_0,      view,           {.ui = ~0 } },
  { MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
  { MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
  { MODKEY,                       XK_period, focusmon,       {.i = +1 } },
  { MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
  { MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
  TAGKEYS(                        XK_1,                      0)
  TAGKEYS(                        XK_2,                      1)
  TAGKEYS(                        XK_3,                      2)
  TAGKEYS(                        XK_4,                      3)
  TAGKEYS(                        XK_5,                      4)
  TAGKEYS(                        XK_6,                      5)
  TAGKEYS(                        XK_7,                      6)
  TAGKEYS(                        XK_8,                      7)
  TAGKEYS(                        XK_9,                      8)
  { MODKEY|ShiftMask,             XK_q,      quit,           {0} },
};

/* button definitions */
/* click can be ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
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


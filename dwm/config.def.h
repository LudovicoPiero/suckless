/* See LICENSE file for copyright and license details. */

/* appearance */
static unsigned int borderpx = 2; /* border pixel of windows */
static unsigned int snap = 32;    /* snap pixel */
static const unsigned int systraypinning =
    0; /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor
          X */
static const unsigned int systrayonleft =
    0; /* 0: systray in the right corner, >0: systray on left of status text */
static const unsigned int systrayspacing = 2; /* systray spacing */
static const int systraypinningfailfirst =
    1; /* 1: if pinning fails, display systray on the first monitor, False:
          display systray on the last monitor*/
static const int showsystray = 1;     /* 0 means no systray */
static const unsigned int gappih = 5; /* horiz inner gap between windows */
static const unsigned int gappiv = 5; /* vert inner gap between windows */
static const unsigned int gappoh =
    5; /* horiz outer gap between windows and screen edge */
static const unsigned int gappov =
    5; /* vert outer gap between windows and screen edge */
static int smartgaps =
    1;                  /* 1 means no outer gap when there is only one window */
static int showbar = 1; /* 0 means no bar */
static int topbar = 1;  /* 0 means bottom bar */
static char font[] = "Iosevka:size=14";
static char dmenufont[] = "Iosevka:size=14";
static const char *fonts[] = {font, "Noto Sans CJK JP:size=14",
                              "Symbols Nerd Font:size=14"};
static char normbgcolor[] = "#1a1b26";
static char normbordercolor[] = "#414868";
static char normfgcolor[] = "#a9b1d6";
static char selfgcolor[] = "#1a1b26";
static char selbordercolor[] = "#7aa2f7";
static char selbgcolor[] = "#7aa2f7";
static char *colors[][3] = {
    /*               fg           bg           border   */
    [SchemeNorm] = {normfgcolor, normbgcolor, normbordercolor},
    [SchemeSel] = {selfgcolor, selbgcolor, selbordercolor},
};

/* tagging */
static const char *tags[] = {"1", "2", "3", "4", "5", "6", "7", "8", "9"};

static const Rule rules[] = {
    /* xprop(1):
     *	WM_CLASS(STRING) = instance, class
     *	WM_NAME(STRING) = title
     */
    /* class                     instance    title tags mask     isfloating
       monitor */

    /* Workspace 1: Dev & Games */
    {"jetbrains", NULL, NULL, 1 << 0, 0, -1},
    {"Albion-Online", NULL, NULL, 1 << 0, 0, -1},

    /* Workspace 2: Zen & Chromium */
    {"zen", NULL, NULL, 1 << 1, 0, -1},
    {"zen-beta", NULL, NULL, 1 << 1, 0, -1},
    {"zen-browser", NULL, NULL, 1 << 1, 0, -1},
    {"Brave-browser", NULL, NULL, 1 << 1, 0, -1},
    {"Chromium-browser", NULL, NULL, 1 << 1, 0, -1},
    {"chromium-browser", NULL, NULL, 1 << 1, 0, -1},
    {"Google-chrome", NULL, NULL, 1 << 1, 0, -1},
    {"chrome", NULL, NULL, 1 << 1, 0, -1},

    /* Workspace 3: Firefox */
    {"firefox", NULL, NULL, 1 << 2, 0, -1},
    {"firefox-esr", NULL, NULL, 1 << 2, 0, -1},
    {"floorp", NULL, NULL, 1 << 2, 0, -1},

    /* Workspace 4: Social */
    {"org.telegram.desktop", NULL, NULL, 1 << 3, 0, -1},
    {"TelegramDesktop", NULL, NULL, 1 << 3, 0, -1},
    {"vesktop", NULL, NULL, 1 << 3, 0, -1},
    {"discord", NULL, NULL, 1 << 3, 0, -1},
    {"WebCord", NULL, NULL, 1 << 3, 0, -1},
    {"ArmCord", NULL, NULL, 1 << 3, 0, -1},

    /* Workspace 5: Mail */
    {"Thunderbird", NULL, NULL, 1 << 4, 0, -1},
    {"org.mozilla.Thunderbird", NULL, NULL, 1 << 4, 0, -1},

    /* Workspace 6: Steam */
    {"Steam", NULL, NULL, 1 << 5, 0, -1},
    {"steam", NULL, NULL, 1 << 5, 0, -1},

    /* Workspace 7: Torrent */
    {"qBittorrent", NULL, NULL, 1 << 6, 0, -1},
    {"org.qbittorrent.qBittorrent", NULL, NULL, 1 << 6, 0, -1},

    /* Workspace 8: WhatsApp */
    {"whatsapp-for-linux", NULL, NULL, 1 << 7, 0, -1},

    /* Workspace 9: Media/Music */
    {"Spotify", NULL, NULL, 1 << 8, 0, -1},
    {"org.fooyin.fooyin", NULL, NULL, 1 << 8, 0, -1},
    {"tidal-hifi", NULL, NULL, 1 << 8, 0, -1},
    {"foobar2000.exe", NULL, NULL, 1 << 8, 0, -1},

    /* Floating Rules */
    {"org.telegram.desktop", NULL, "Media viewer", 1 << 3, 1, -1},
    {"TelegramDesktop", NULL, "Media viewer", 1 << 3, 1, -1},
    {"Steam", NULL, "Special Offers", 1 << 5, 1, -1},
    {"Steam", NULL, "Steam - News", 1 << 5, 1, -1},
    {"steam", NULL, "Special Offers", 1 << 5, 1, -1},
    {"steam", NULL, "Steam - News", 1 << 5, 1, -1},
    /* Bitwarden - dwm matches substring, so "Bitwarden" should be enough if
       title contains it */
    {NULL, NULL, "Bitwarden", 0, 1, -1},
    {"xdg-desktop-portal-gtk", NULL, NULL, 0, 1, -1},
    {"KeePassXC", NULL, "Generate Password", 0, 1, -1},
    {"org.keepassxc.KeePassXC", NULL, "Generate Password", 0, 1, -1},
    {"KeePassXC", NULL, "Browser Access Request", 0, 1, -1},
    {"org.keepassxc.KeePassXC", NULL, "Browser Access Request", 0, 1, -1},

    /* Scratchpads */
    {NULL, "spterm", NULL, 0, 1, -1},
};

/* layout(s) */
static float mfact = 0.55;  /* factor of master area size [0.05..0.95] */
static int nmaster = 1;     /* number of clients in master area */
static int resizehints = 1; /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen =
    1; /* 1 will force focus on the fullscreen window */
static const int refreshrate =
    120; /* refresh rate (per second) for client move/resize */

#define FORCE_VSPLIT                                                           \
  1 /* nrowgrid layout: force two clients to always split vertically */
#include "vanitygaps.c"

static const Layout layouts[] = {
    /* symbol     arrange function */
    {"[]=", tile}, /* first entry is default */
    {"[M]", monocle},
    {"[@]", spiral},
    {"[\\]", dwindle},
    {"H[]", deck},
    {"TTT", bstack},
    {"===", bstackhoriz},
    {"HHH", grid},
    {"###", nrowgrid},
    {"---", horizgrid},
    {":::", gaplessgrid},
    {"|M|", centeredmaster},
    {">M>", centeredfloatingmaster},
    {"><>", NULL}, /* no layout function means floating behavior */
    {NULL, NULL},
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY, TAG)                                                      \
  {MODKEY, KEY, view, {.ui = 1 << TAG}},                                       \
      {MODKEY | ControlMask, KEY, toggleview, {.ui = 1 << TAG}},               \
      {MODKEY | ShiftMask, KEY, tag, {.ui = 1 << TAG}},                        \
      {MODKEY | ControlMask | ShiftMask, KEY, toggletag, {.ui = 1 << TAG}},

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd)                                                             \
  {                                                                            \
    .v = (const char *[]) { "/bin/sh", "-c", cmd, NULL }                       \
  }

/* commands */
static char dmenumon[2] =
    "0"; /* component of dmenucmd, manipulated in spawn() */
// static const char *dmenucmd[] = { "j4-dmenu-desktop", NULL };
static const char *dmenucmd[] = {"dmenu_run", "-m",  dmenumon,       "-fn",
                                 dmenufont,   "-nb", normbgcolor,    "-nf",
                                 normfgcolor, "-sb", selbordercolor, "-sf",
                                 selfgcolor,  NULL};
static const char *termcmd[] = {"alacritty", NULL};
static const char *clipboardpickercmd[] = {"clipmenu", NULL};

/*
 * Xresources preferences to load at startup
 */
ResourcePref resources[] = {
    {"font", STRING, &font},
    {"dmenufont", STRING, &dmenufont},
    {"normbgcolor", STRING, &normbgcolor},
    {"normbordercolor", STRING, &normbordercolor},
    {"normfgcolor", STRING, &normfgcolor},
    {"selbgcolor", STRING, &selbgcolor},
    {"selbordercolor", STRING, &selbordercolor},
    {"selfgcolor", STRING, &selfgcolor},
    {"borderpx", INTEGER, &borderpx},
    {"snap", INTEGER, &snap},
    {"showbar", INTEGER, &showbar},
    {"topbar", INTEGER, &topbar},
    {"nmaster", INTEGER, &nmaster},
    {"resizehints", INTEGER, &resizehints},
    {"mfact", FLOAT, &mfact},
};

static const Key keys[] = {
    /* modifier                     key        function        argument */
    {MODKEY, XK_p, spawn, {.v = dmenucmd}},
    {MODKEY, XK_Return, spawn, {.v = termcmd}},
    {MODKEY, XK_o, spawn, {.v = clipboardpickercmd}},
    {MODKEY, XK_b, togglebar, {0}},
    {MODKEY, XK_j, focusstack, {.i = +1}},
    {MODKEY, XK_k, focusstack, {.i = -1}},
    {MODKEY, XK_i, incnmaster, {.i = +1}},
    {MODKEY, XK_d, incnmaster, {.i = -1}},
    {MODKEY, XK_h, setmfact, {.f = -0.05}},
    {MODKEY, XK_l, setmfact, {.f = +0.05}},
    {MODKEY | ShiftMask, XK_h, setcfact, {.f = +0.25}},
    {MODKEY | ShiftMask, XK_l, setcfact, {.f = -0.25}},
    {MODKEY | ShiftMask, XK_o, setcfact, {.f = 0.00}},
    {MODKEY | ShiftMask, XK_Return, zoom, {0}},
    {MODKEY | Mod1Mask, XK_u, incrgaps, {.i = +1}},
    {MODKEY | Mod1Mask | ShiftMask, XK_u, incrgaps, {.i = -1}},
    {MODKEY | Mod1Mask, XK_i, incrigaps, {.i = +1}},
    {MODKEY | Mod1Mask | ShiftMask, XK_i, incrigaps, {.i = -1}},
    {MODKEY | Mod1Mask, XK_o, incrogaps, {.i = +1}},
    {MODKEY | Mod1Mask | ShiftMask, XK_o, incrogaps, {.i = -1}},
    {MODKEY | Mod1Mask, XK_6, incrihgaps, {.i = +1}},
    {MODKEY | Mod1Mask | ShiftMask, XK_6, incrihgaps, {.i = -1}},
    {MODKEY | Mod1Mask, XK_7, incrivgaps, {.i = +1}},
    {MODKEY | Mod1Mask | ShiftMask, XK_7, incrivgaps, {.i = -1}},
    {MODKEY | Mod1Mask, XK_8, incrohgaps, {.i = +1}},
    {MODKEY | Mod1Mask | ShiftMask, XK_8, incrohgaps, {.i = -1}},
    {MODKEY | Mod1Mask, XK_9, incrovgaps, {.i = +1}},
    {MODKEY | Mod1Mask | ShiftMask, XK_9, incrovgaps, {.i = -1}},
    {MODKEY | Mod1Mask, XK_0, togglegaps, {0}},
    {MODKEY | Mod1Mask | ShiftMask, XK_0, defaultgaps, {0}},
    {MODKEY, XK_Tab, view, {0}},
    {MODKEY, XK_w, killclient, {0}},
    {MODKEY, XK_t, setlayout, {.v = &layouts[0]}},
    {MODKEY, XK_f, setlayout, {.v = &layouts[1]}},
    {MODKEY, XK_m, setlayout, {.v = &layouts[2]}},
    {MODKEY, XK_space, setlayout, {0}},
    {MODKEY | ShiftMask, XK_space, togglefloating, {0}},
    {MODKEY, XK_0, view, {.ui = ~0}},
    {MODKEY | ShiftMask, XK_0, tag, {.ui = ~0}},
    {MODKEY, XK_comma, focusmon, {.i = -1}},
    {MODKEY, XK_period, focusmon, {.i = +1}},
    {MODKEY | ShiftMask, XK_comma, tagmon, {.i = -1}},
    {MODKEY | ShiftMask, XK_period, tagmon, {.i = +1}},
    TAGKEYS(XK_1, 0) TAGKEYS(XK_2, 1) TAGKEYS(XK_3, 2) TAGKEYS(XK_4, 3)
        TAGKEYS(XK_5, 4) TAGKEYS(XK_6, 5) TAGKEYS(XK_7, 6) TAGKEYS(XK_8, 7)
            TAGKEYS(XK_9, 8){MODKEY | ShiftMask, XK_q, quit, {0}},
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle,
 * ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
    /* click                event mask      button          function argument */
    {ClkLtSymbol, 0, Button1, setlayout, {0}},
    {ClkLtSymbol, 0, Button3, setlayout, {.v = &layouts[2]}},
    {ClkWinTitle, 0, Button2, zoom, {0}},
    {ClkStatusText, 0, Button2, spawn, {.v = termcmd}},
    {ClkClientWin, MODKEY, Button1, movemouse, {0}},
    {ClkClientWin, MODKEY, Button2, togglefloating, {0}},
    {ClkClientWin, MODKEY, Button3, resizemouse, {0}},
    {ClkTagBar, 0, Button1, view, {0}},
    {ClkTagBar, 0, Button3, toggleview, {0}},
    {ClkTagBar, MODKEY, Button1, tag, {0}},
    {ClkTagBar, MODKEY, Button3, toggletag, {0}},
};

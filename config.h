#define TERMINAL "footclient"
#define BROWSER "org.mozilla.firefox"

#define ALT   WLR_MODIFIER_LOGO
#define SUPER WLR_MODIFIER_ALT
#define SHIFT WLR_MODIFIER_SHIFT
#define CTRL  WLR_MODIFIER_CTRL
#define CAPS  WLR_MODIFIER_MOD3
#define MDEIA SUPER|CTRL

/* Taken from https://github.com/djpohly/dwl/issues/466 */
#define COLOR(hex)    { ((hex >> 24) & 0xFF) / 255.0f, \
                        ((hex >> 16) & 0xFF) / 255.0f, \
                        ((hex >> 8) & 0xFF) / 255.0f, \
                        (hex & 0xFF) / 255.0f }

/* appearance */
static const int sloppyfocus               = 0;  /* focus follows mouse */
static const int bypass_surface_visibility = 0;  /* 1 means idle inhibitors will disable idle tracking even if it's surface isn't visible  */
static const int smartgaps                 = 1;  /* 1 means no outer gap when there is only one window */
static const int monoclegaps               = 0;  /* 1 means outer gaps in monocle layout */
static const unsigned int borderpx         = 2;  /* border pixel of windows */
static const unsigned int gappih           = 10; /* horiz inner gap between windows */
static const unsigned int gappiv           = 10; /* vert inner gap between windows */
static const unsigned int gappoh           = 10; /* horiz outer gap between windows and screen edge */
static const unsigned int gappov           = 10; /* vert outer gap between windows and screen edge */
static const float rootcolor[]             = COLOR(0x222222ff);
static const float bordercolor[]           = COLOR(0x444444ff);
static const float focuscolor[]            = COLOR(0x005577ff);
static const float urgentcolor[]           = COLOR(0xff0000ff);
/* To conform the xdg-protocol, set the alpha to zero to restore the old behavior */
static const float fullscreen_bg[]         = {0.1f, 0.1f, 0.1f, 1.0f}; /* You can also use glsl colors */
/* static const float fullscreen_bg[]         = {0.1, 0.1, 0.1, 0.0};  */

/* tagging - TAGCOUNT must be no greater than 31 */
#define TAGCOUNT (9)

/* logging */
static int log_level = WLR_ERROR;

/* Autostart */
static const char *const autostart[] = {
        "startw", NULL,
        NULL /* terminate */
};


static const Rule rules[] = {
	/* app_id     title       tags mask     isfloating  isterm  noswallow  monitor */
	{ "firefox",  NULL,       1 << 8,       0,          0,      1,         -1 },
	{ "foot",     NULL,       0,            0,          1,      1,         -1 },
};

/* layout(s) */
static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
	{ "TTT",      bstack },
	{ "===",      bstackhoriz },
};

/* monitors */
/* NOTE: ALWAYS add a fallback rule, even if you are completely sure it won't be used */
static const MonitorRule monrules[] = {
	/* name       mfact  nmaster scale layout       rotate/reflect                x    y */
	/* example of a HiDPI laptop monitor:
	{ "eDP-1",    0.5f,  1,      2,    &layouts[0], WL_OUTPUT_TRANSFORM_NORMAL,   -1,  -1 },
	*/
	/* defaults */
	{ NULL,       0.55f, 1,      1,    &layouts[0], WL_OUTPUT_TRANSFORM_NORMAL,   -1,  -1 },
};

/* keyboard */
static const struct xkb_rule_names xkb_rules = {
    .layout = "gb",
	.options = "ctrl:nocaps",
};

static const int repeat_rate = 25;
static const int repeat_delay = 600;

/* Trackpad */
static const int tap_to_click = 0;
static const int tap_and_drag = 1;
static const int drag_lock = 1;
static const int natural_scrolling = 1;
static const int disable_while_typing = 1;
static const int left_handed = 0;
static const int middle_button_emulation = 0;
static const enum libinput_config_scroll_method scroll_method = LIBINPUT_CONFIG_SCROLL_2FG;
static const enum libinput_config_click_method click_method = LIBINPUT_CONFIG_CLICK_METHOD_BUTTON_AREAS;
static const uint32_t send_events_mode = LIBINPUT_CONFIG_SEND_EVENTS_ENABLED;
static const enum libinput_config_accel_profile accel_profile = LIBINPUT_CONFIG_ACCEL_PROFILE_ADAPTIVE;
static const double accel_speed = 0.0;
static const enum libinput_config_tap_button_map button_map = LIBINPUT_CONFIG_TAP_MAP_LRM;

#define TAGKEYS(KEY,TAG) \
	{ SUPER,                    KEY,            view,            {.ui = 1 << TAG} }, \
	{ SUPER|CTRL,  KEY,            toggleview,      {.ui = 1 << TAG} }, \
	{ SUPER|SHIFT, KEY,            tag,             {.ui = 1 << TAG} }, \
	{ SUPER|CTRL|SHIFT,KEY,toggletag,  {.ui = 1 << TAG} }

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static const char *termcmd[] = { TERMINAL, NULL };
static const char *menucmd[] = { "bemenu-run", NULL };


#include "keys.h"
#include "shiftview.c"

static const Key keys[] = {
	/* Note that Shift changes certain key codes: c -> C, 2 -> at, etc. */
	/* modifier           key                         function          argument */
    TAGKEYS(              Key_1,                                        0),
    TAGKEYS(              Key_2,                                        1),
    TAGKEYS(              Key_3,                                        2),
    TAGKEYS(              Key_4,                                        3),
    TAGKEYS(              Key_5,                                        4),
    TAGKEYS(              Key_6,                                        5),
    TAGKEYS(              Key_7,                                        6),
    TAGKEYS(              Key_8,                                        7),
    TAGKEYS(              Key_9,                                        8),
    { SUPER,              Key_0,                        view,             {.ui = ~0} },
	{ SUPER|SHIFT,        Key_0,                        tag,              {.ui = ~0} },
	{ SUPER,		      Key_minus,	                spawn,		       SHCMD("pamixer -d 5; kill -44 $(pidof someblocks)") },
	{ SUPER|SHIFT,		  Key_minus,	                spawn,		       SHCMD("pamixer -d 15; kill -44 $(pidof someblocks)") },
	{ SUPER,			  Key_equal,	                spawn,		       SHCMD("pamixer -i 5; kill -44 $(pidof someblocks)") },
	{ SUPER|SHIFT,		  Key_equal,	                spawn,		       SHCMD("pamixer -i 15; kill -44 $(pidof someblocks)") },
	{ SUPER,			  Key_BackSpace,	            spawn,		       {.v = (const char*[]){ "sysact", NULL } } },
	{ SUPER|SHIFT,		  Key_BackSpace,	            spawn,		       {.v = (const char*[]){ "sysact", NULL } } },

    { SUPER,              Key_Tab,                      view,             {0} },
    { SUPER,              Key_q,                        killclient,       {0} },
    { SUPER|SHIFT,        Key_q,                        quit,             {0} },
    { SUPER,			  Key_w,		                spawn,		       {.v = (const char*[]){ BROWSER, NULL } } },
    { SUPER|SHIFT,		  Key_w,		                spawn,		       {.v = (const char*[]){ TERMINAL, "-e", "nmtui", NULL } } },
	{ SUPER,			  Key_f,		                spawn,		       {.v = (const char*[]){ TERMINAL, "-e", "lf", NULL } } },
	{ SUPER,		      Key_r,		                spawn,		       {.v = (const char*[]){ TERMINAL, "-e", "htop", NULL } } },
    { SUPER,              Key_t,                        setlayout,        {.v = &layouts[0]} },
    { SUPER|SHIFT,        Key_f,                        setlayout,        {.v = &layouts[1]} },
    { SUPER,              Key_m,                        setlayout,        {.v = &layouts[2]} },
    { SUPER,              Key_u,                        setlayout,        {.v = &layouts[3]} },
    { SUPER,              Key_o,                        setlayout,        {.v = &layouts[4]} },
    { SUPER,              Key_i,                        incnmaster,       {.i = +1} },
    { SUPER,              Key_d,                        incnmaster,       {.i = -1} },
	{ SUPER|ALT,		  Key_p,			            spawn,		       {.v = (const char*[]){ "mpc", "toggle", NULL } } },
	{ SUPER|SHIFT,		  Key_p,			            spawn,		       SHCMD("mpc pause; pauseallmpv") },
	{ SUPER,			  Key_bracketleft,	            spawn,		       {.v = (const char*[]){ "mpc", "seek", "-10", NULL } } },
	{ SUPER|SHIFT,		  Key_bracketleft,	            spawn,		       {.v = (const char*[]){ "mpc", "seek", "-60", NULL } } },
	{ SUPER,			  Key_bracketright,	            spawn,		       {.v = (const char*[]){ "mpc", "seek", "+10", NULL } } },
	{ SUPER|SHIFT,		  Key_bracketright,	            spawn,		       {.v = (const char*[]){ "mpc", "seek", "+60", NULL } } },
	{ SUPER,			  Key_backslash,	            view,		       {0} },
	{ SUPER,			  Key_a,		                togglegaps,       {0} },
	{ SUPER|SHIFT,		  Key_a,		                defaultgaps,      {0} },
    { SUPER,              Key_p,                        spawn,            {.v = menucmd} },
    { SUPER,              Key_Return,                   spawn,            {.v = termcmd} },
    { SUPER,              Key_g,                        shiftview,        { .i = -1 } },
    { SUPER,              Key_semicolon,                shiftview,        { .i = 1 } },

    { SUPER,              Key_b,                        togglebar,        {0}},
    { SUPER,              Key_j,                        focusstack,       {.i = +1} },
    { SUPER,              Key_k,                        focusstack,       {.i = -1} },
    { SUPER|SHIFT,        Key_j,                        movestack,        {.i = +1} },
    { SUPER|SHIFT,        Key_k,                        movestack,        {.i = -1} },
    { SUPER,              Key_h,                        setmfact,         {.f = -0.05f} },
    { SUPER,              Key_l,                        setmfact,         {.f = +0.05f} },

	{ SUPER,			  Key_z,		                incgaps,	       {.i = +3 } },
	{ SUPER,			  Key_x,		                incgaps,	       {.i = -3 } },

	{ SUPER|SHIFT,		  Key_n,		                spawn,		       SHCMD(TERMINAL " -e newsboat ; pkill -RTMIN+6 someblocks") },
	{ SUPER,			  Key_m,		                spawn,		       {.v = (const char*[]){ TERMINAL, "-e", "ncmpcpp", NULL } } },
	{ SUPER|SHIFT,		  Key_m,		                spawn,		       SHCMD("wpctl set-mute @DEFAULT_AUDIO_SINK@ toggle; kill -44 $(pidof someblocks)") },
	{ SUPER,			  Key_comma,	                spawn,		       {.v = (const char*[]){ "mpc", "prev", NULL } } },
	{ SUPER|SHIFT,		  Key_comma,	                spawn,		       {.v = (const char*[]){ "mpc", "seek", "0%", NULL } } },
	{ SUPER,			  Key_period,	                spawn,		       {.v = (const char*[]){ "mpc", "next", NULL } } },
	{ SUPER|SHIFT,		  Key_period,	                spawn,		       {.v = (const char*[]){ "mpc", "repeat", NULL } } },

    { SUPER|SHIFT,        Key_space,                    togglefloating,   {0} },
    { SUPER,              Key_e,                        togglefullscreen, {0} },
    { SUPER,              Key_comma,                    focusmon,         {.i = WLR_DIRECTION_LEFT} },
    { SUPER,              Key_period,                   focusmon,         {.i = WLR_DIRECTION_RIGHT} },
    { SUPER|SHIFT,        Key_comma,                    tagmon,           {.i = WLR_DIRECTION_LEFT} },
    { SUPER|SHIFT,        Key_period,                   tagmon,           {.i = WLR_DIRECTION_RIGHT} },

    { 0,		          Key_Print,	                spawn,		{.v = (const char*[]){ "screenshot", NULL } } },

    /* { SUPER,		      Key_F1,		                spawn,		SHCMD("groff -mom /usr/local/share/dwm/larbs.mom -Tpdf | zathura -") }, */
    /* { SUPER,		      Key_F2,		                spawn,		{.v = (const char*[]){ "tutorialvids", NULL } } }, */
    /* { SUPER,		      Key_F3,		                spawn,		{.v = (const char*[]){ "displayselect", NULL } } }, */
    { SUPER,		      Key_F4,		                spawn,		SHCMD("footclient -e pulsemixer; kill -44 $(pidof someblocks)") },
    /* { SUPER,		      Key_F5,		                xrdb,		{.v = NULL } }, */
    { SUPER,		      Key_F6,		                spawn,		{.v = (const char*[]){ "torwrap", NULL } } },
    { SUPER,		      Key_F7,		                spawn,		{.v = (const char*[]){ "td-toggle", NULL } } },
    /* { SUPER,		      Key_F8,		                spawn,		{.v = (const char*[]){ "mailsync", NULL } } }, */
    { SUPER,		      Key_F9,		                spawn,		{.v = (const char*[]){ "mounter", NULL } } },
    { SUPER,		      Key_F10,		                spawn,		{.v = (const char*[]){ "unmounter", NULL } } },
    { SUPER,		      Key_F11,		                spawn,		SHCMD("mpv --untimed --no-cache --no-osc --no-input-default-bindings --profile=low-latency --input-conf=/dev/null --title=webcam $(ls /dev/video[0,2,4,6,8] | tail -n 1)") },
    { SUPER,		      Key_F12,		                spawn,		SHCMD("remaps") },

    /* { 0,               Key_XF86PowerOff,             spawn,      {.v = (const char*[]){ "sysact", NULL } } }, */
    { 0,                  Key_XF86AudioMute,		    spawn,		SHCMD("pamixer -t; kill -44 $(pidof someblocks)") },
    { 0,                  Key_XF86AudioRaiseVolume,	    spawn,		SHCMD("pamixer -i 3; kill -44 $(pidof someblocks)") },
    { 0,                  Key_XF86AudioLowerVolume,	    spawn,		SHCMD("pamixer -d 3; kill -44 $(pidof someblocks)") },
    { 0,                  Key_XF86AudioMicMute,	        spawn,		SHCMD("pactl set-source-mute @DEFAULT_SOURCE@ toggle") },
    { 0,                  Key_XF86MonBrightnessUp,	    spawn,		{.v = (const char*[]){ "light", "-A", "15", NULL } } },
    { 0,                  Key_XF86MonBrightnessDown,	spawn,		{.v = (const char*[]){ "light", "-U", "15", NULL } } },


    /* Ctrl-Alt-Backspace and Ctrl-Alt-Fx used to be handled by X server */
    { CTRL|WLR_MODIFIER_ALT,Key_BackSpace, quit, {0} },
#define CHVT(KEY,n) { CTRL|WLR_MODIFIER_ALT, KEY, chvt, {.ui = (n)} }
    /* Ctrl-Alt-Fx is used to switch to another VT, if you don't know what a VT is
     * do not remove them.
     */
    CHVT(Key_F1, 1), CHVT(Key_F2,  2),  CHVT(Key_F3,  3),  CHVT(Key_F4,  4),
    CHVT(Key_F5, 5), CHVT(Key_F6,  6),  CHVT(Key_F7,  7),  CHVT(Key_F8,  8),
    CHVT(Key_F9, 9), CHVT(Key_F10, 10), CHVT(Key_F11, 11), CHVT(Key_F12, 12),
};

static const Button buttons[] = {
    {}
    /* { SUPER, BTN_LEFT,   moveresize,     {.ui = CurMove} }, */
    /* { SUPER, BTN_MIDDLE, togglefloating, {0} }, */
    /* { SUPER, BTN_RIGHT,  moveresize,     {.ui = CurResize} }, */
};

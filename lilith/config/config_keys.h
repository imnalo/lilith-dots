/* ======================================================================
 *  config_keys.h — Key + mouse bindings. Super = MODKEY.
 * ----------------------------------------------------------------------
 *  Menus call `lilith-menu <mode>` (they appear on the bottom edge, over the bar);
 *  media keys use wpctl / brightnessctl; Print / Super+Print call lilith-shot / lilith-record.
 *  Edit, then run:  lilith-rice build   (and restart the session)
 * ====================================================================== */

/*
 * Key and mouse bindings.
 * Binding format: { modifiers, key, function, argument }
 * Note: for keys, the first matching entry in keys[] wins and stops the search.
 */

/* Main modifier: Super (Logo) key. */
#define MODKEY WLR_MODIFIER_LOGO
#define ALT_MODKEY WLR_MODIFIER_ALT  /* secondary modifier: Alt */

/* Generates the four tag bindings for one number key:
 *   MODKEY + KEY                  view tag
 *   MODKEY + Ctrl + KEY           toggle tag visibility in the current view
 *   MODKEY + Shift + SKEY         move the focused window to the tag
 *   MODKEY + Ctrl + Shift + SKEY  toggle the tag on the focused window
 * KEY is the number key, SKEY its shifted symbol (US layout), TAG is 0-based. */
#define TAGKEYS(KEY,SKEY,TAG) \
	{ MODKEY,                    KEY,            view,            {.ui = 1 << TAG} }, \
	{ MODKEY|WLR_MODIFIER_CTRL,  KEY,            toggleview,      {.ui = 1 << TAG} }, \
	{ MODKEY|WLR_MODIFIER_SHIFT, SKEY,           tag,             {.ui = 1 << TAG} }, \
	{ MODKEY|WLR_MODIFIER_CTRL|WLR_MODIFIER_SHIFT,SKEY,toggletag, {.ui = 1 << TAG} }

/* Helper: run a shell command string via /bin/sh -c, e.g. SHCMD("cmd | cmd"). */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* Commands started by the bindings below (NULL-terminated argv arrays). */
static const char *termcmd[] = { "foot", NULL };  /* terminal */
static const char *menu_apps[]  = { "lilith-menu", "apps", NULL };  /* application launcher */
static const char *menu_clip[]  = { "lilith-menu", "clip", NULL };  /* clipboard history */
static const char *yazicmd[]    = { "foot", "-a", "yazi", "yazi", NULL };  /* yazi file manager in a terminal */
static const char *stratacmd[]  = { "strata", NULL };  /* Strata GUI file manager */
static const char *zencmd[]     = { "zen", NULL };  /* Zen browser */
static const char *zedcmd[]     = { "zed", NULL };  /* Zed editor */
static const char *menu_power[] = { "lilith-menu", "power", NULL };  /* power menu: exit, suspend, reboot, poweroff */
static const char *menu_cheat[] = { "lilith-menu", "cheat", NULL };  /* searchable key binding cheatsheet */
static const char *menu_font[]  = { "lilith-menu", "font", NULL };  /* font picker */
static const char *menu_wall[]  = { "lilith-menu", "wall", NULL };  /* wallpaper picker */
static const char *menu_wifi[]  = { "lilith-menu", "wifi", NULL };  /* Wi-Fi menu (NetworkManager) */
static const char *menu_bt[]    = { "lilith-menu", "bluetooth", NULL };  /* Bluetooth menu (optional: lilith-rice bluetooth) */
static const char *shot_region[] = { "lilith-shot", "region", NULL };  /* screenshot: select an area */
static const char *shot_full[]   = { "lilith-shot", "full", NULL };  /* screenshot: whole screen */
static const char *rec_region[]  = { "lilith-record", "region", NULL };  /* screen recording: select an area (press again to stop) */
static const char *rec_full[]    = { "lilith-record", "full", NULL };  /* screen recording: whole screen (press again to stop) */
static const char *volupcmd[]   = { "wpctl", "set-volume", "-l", "1.0", "@DEFAULT_AUDIO_SINK@", "5%+", NULL };  /* volume +5% (capped at 100%) */
static const char *voldowncmd[] = { "wpctl", "set-volume", "@DEFAULT_AUDIO_SINK@", "5%-", NULL };  /* volume -5% */
static const char *volmutecmd[] = { "wpctl", "set-mute", "@DEFAULT_AUDIO_SINK@", "toggle", NULL };  /* toggle mute */
static const char *brupcmd[]    = { "brightnessctl", "set", "10%+", NULL };  /* brightness +10% */
static const char *brdowncmd[]  = { "brightnessctl", "set", "10%-", NULL };  /* brightness -10% */

/* Keyboard bindings. */
static const Key keys[] = {
	{ MODKEY,                    XKB_KEY_r,           spawn,            {.v = menu_apps} },  /* Super+R: application launcher */
	{ MODKEY,                    XKB_KEY_v,           spawn,            {.v = menu_clip} },  /* Super+V: clipboard history */
	{ MODKEY,                    XKB_KEY_e,           spawn,            {.v = stratacmd} },  /* Super+E: Strata file manager */
	{ MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_e,           spawn,            {.v = yazicmd} },  /* Super+Shift+E: yazi file manager */
	{ MODKEY,                    XKB_KEY_f,           spawn,            {.v = zencmd} },  /* Super+F: Zen browser */
	{ MODKEY,                    XKB_KEY_t,           spawn,            {.v = zedcmd} },  /* Super+T: Zed editor */
	{ MODKEY,                    XKB_KEY_Escape,      spawn,            {.v = menu_power} },  /* Super+Escape: power menu */
	{ MODKEY,                    XKB_KEY_slash,       spawn,            {.v = menu_cheat} },  /* Super+/: key binding cheatsheet */
	{ MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_t,           spawn,            {.v = menu_font} },  /* Super+Shift+T: font picker */
	{ MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_w,           spawn,            {.v = menu_wall} },  /* Super+Shift+W: wallpaper picker */
	{ MODKEY,                    XKB_KEY_n,           spawn,            {.v = menu_wifi} },  /* Super+N: Wi-Fi menu */
	{ MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_n,           spawn,            {.v = menu_bt} },  /* Super+Shift+N: Bluetooth menu */
	{ MODKEY,                    XKB_KEY_Return,      spawn,            {.v = termcmd} },  /* Super+Enter: open terminal */
	{ MODKEY,                    XKB_KEY_z,		  zoomfit,	    {0} },  /* Super+Z: zoom out to fit all windows */
	{ MODKEY,                    XKB_KEY_q,           spawn,            {.v = termcmd} },  /* Super+Q: open terminal */
	{ MODKEY,                    XKB_KEY_Tab,         focusstackcenter,       {.i = +1} },  /* Super+Tab: focus next window and center the view on it */
	{ MODKEY,                    XKB_KEY_k,           focusstackcenter,       {.i = -1} },  /* Super+K: focus previous window and center the view on it */
	{ MODKEY,                    XKB_KEY_c,           killclient,       {0} },  /* Super+C: close focused window */
	{ MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_f,           togglefullscreen, {0} },  /* Super+Shift+F: toggle fullscreen */
	{ MODKEY,                    XKB_KEY_0,           view,             {.ui = ~0} },  /* Super+0: show all tags */
	{ MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_parenright,  tag,              {.ui = ~0} },  /* Super+Shift+0: show the focused window on all tags */
	{ MODKEY,                    XKB_KEY_comma,       focusmon,         {.i = WLR_DIRECTION_LEFT} },  /* Super+,: focus the monitor to the left */
	{ MODKEY,                    XKB_KEY_period,      focusmon,         {.i = WLR_DIRECTION_RIGHT} },  /* Super+.: focus the monitor to the right */
	{ MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_less,        tagmon,           {.i = WLR_DIRECTION_LEFT} },  /* Super+Shift+,: send window to the monitor on the left */
	{ MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_greater,     tagmon,           {.i = WLR_DIRECTION_RIGHT} },  /* Super+Shift+.: send window to the monitor on the right */
	/* Super+1..9 and variants: tag bindings (see TAGKEYS above). */
	TAGKEYS(          XKB_KEY_1, XKB_KEY_exclam,                        0),
	TAGKEYS(          XKB_KEY_2, XKB_KEY_at,                            1),
	TAGKEYS(          XKB_KEY_3, XKB_KEY_numbersign,                    2),
	TAGKEYS(          XKB_KEY_4, XKB_KEY_dollar,                        3),
	TAGKEYS(          XKB_KEY_5, XKB_KEY_percent,                       4),
	TAGKEYS(          XKB_KEY_6, XKB_KEY_asciicircum,                   5),
	TAGKEYS(          XKB_KEY_7, XKB_KEY_ampersand,                     6),
	TAGKEYS(          XKB_KEY_8, XKB_KEY_asterisk,                      7),
	TAGKEYS(          XKB_KEY_9, XKB_KEY_parenleft,                     8),
	{ MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_q,           quit,             {0} },  /* Super+Shift+Q: quit the compositor */
	{ MODKEY,                    XKB_KEY_b,           togglebar,        {0} },  /* Super+B: show/hide the bar */
	{ MODKEY|WLR_MODIFIER_CTRL,  XKB_KEY_b,           barcyclepos,      {.i = +1} },  /* Super+Ctrl+B: move the bar to the next screen edge */
	{ MODKEY|WLR_MODIFIER_CTRL|WLR_MODIFIER_SHIFT, XKB_KEY_b, barcyclepos, {.i = -1} },  /* Super+Ctrl+Shift+B: move the bar to the previous screen edge */
	{ MODKEY|ALT_MODKEY,         XKB_KEY_b,           togglebarfloat,   {0} },  /* Super+Alt+B: toggle between reserved space and floating bar */
	{ MODKEY|ALT_MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_b, togglebarlayer,  {0} },  /* Super+Alt+Shift+B: toggle the bar above/below windows */

	/* Canvas navigation: focus by direction (0 = up, 1 = left, 2 = down, 3 = right). */
	{ MODKEY,                    XKB_KEY_w,           focusdir,         {.ui = 0} },  /* Super+W: focus the window above */
	{ MODKEY,                    XKB_KEY_a,           focusdir,         {.ui = 1} },  /* Super+A: focus the window to the left */
	{ MODKEY,                    XKB_KEY_s,           focusdir,         {.ui = 2} },  /* Super+S: focus the window below */
	{ MODKEY,                    XKB_KEY_d,           focusdir,         {.ui = 3} },  /* Super+D: focus the window to the right */
	{ MODKEY,                    XKB_KEY_Home,         homecanvas,       {0} },  /* Super+Home: return the canvas to its home position */
	{ MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_Left,         movecanvas,       {.i = 0} },  /* Super+Shift+Left: pan the canvas left (0 = left, 1 = right, 2 = up, 3 = down) */
	{ MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_Right,        movecanvas,       {.i = 1} },  /* Super+Shift+Right: pan the canvas right */
	{ MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_Up,           movecanvas,       {.i = 2} },  /* Super+Shift+Up: pan the canvas up */
	{ MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_Down,         movecanvas,       {.i = 3} },  /* Super+Shift+Down: pan the canvas down */
	{ MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_Tab,        centerwindow,     {0} },  /* Super+Shift+Tab: center the focused window */

	/* Zoom: step of 0.25 per press. */
	{ MODKEY, XKB_KEY_equal, zoom,      {.f =  +0.25f} },  /* Super+=: zoom in */
	{ MODKEY, XKB_KEY_minus, zoom,      {.f = -0.25f} },  /* Super+-: zoom out */

	/* Screenshots and screen recording. */
	{ 0,                         XKB_KEY_Print,       spawn,            {.v = shot_region} },  /* Print: screenshot of an area */
	{ WLR_MODIFIER_SHIFT,        XKB_KEY_Print,       spawn,            {.v = shot_full} },  /* Shift+Print: screenshot of the whole screen */
	{ MODKEY,                    XKB_KEY_Print,       spawn,            {.v = rec_region} },  /* Super+Print: record an area, again to stop */
	{ MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_Print,       spawn,            {.v = rec_full} },  /* Super+Shift+Print: record the screen, again to stop */

	/* Media keys; barspawn runs the command and refreshes the bar modules. */
	{ 0, XKB_KEY_XF86AudioRaiseVolume,  barspawn, {.v = volupcmd} },  /* volume up */
	{ 0, XKB_KEY_XF86AudioLowerVolume,  barspawn, {.v = voldowncmd} },  /* volume down */
	{ 0, XKB_KEY_XF86AudioMute,         barspawn, {.v = volmutecmd} },  /* mute toggle */
	{ 0, XKB_KEY_XF86MonBrightnessUp,   barspawn, {.v = brupcmd} },  /* brightness up */
	{ 0, XKB_KEY_XF86MonBrightnessDown, barspawn, {.v = brdowncmd} },  /* brightness down */

	{ WLR_MODIFIER_CTRL|WLR_MODIFIER_ALT,XKB_KEY_Terminate_Server, quit, {0} },  /* Ctrl+Alt+Backspace: quit the compositor */
/* Ctrl+Alt+F1..F12: switch to the virtual terminal n. */
#define CHVT(n) { WLR_MODIFIER_CTRL|WLR_MODIFIER_ALT,XKB_KEY_XF86Switch_VT_##n, chvt, {.ui = (n)} }
	CHVT(1), CHVT(2), CHVT(3), CHVT(4), CHVT(5), CHVT(6),
	CHVT(7), CHVT(8), CHVT(9), CHVT(10), CHVT(11), CHVT(12),
};

/* Mouse bindings. Format: { click target, modifiers, button, function, argument }
 * Targets: ClkClient = window, ClkRoot = empty canvas, ClkTagBar = tag buttons,
 * ClkStatus = status area of the bar. SCROLL_UP/SCROLL_DOWN are the scroll wheel. */
static const Button buttons[] = {
	{ ClkClient, MODKEY, BTN_LEFT,   moveresize,     {.ui = CurMove} },  /* Super+left drag on a window: move it */
	{ ClkClient, MODKEY, BTN_RIGHT,  moveresize,     {.ui = CurResize} },  /* Super+right drag on a window: resize it */
	{ ClkClient, MODKEY|WLR_MODIFIER_SHIFT, BTN_LEFT, movecanvasmouse, {.f = 1} },  /* Super+Shift+left drag on a window: pan the canvas */
	{ ClkRoot, MODKEY|WLR_MODIFIER_SHIFT, BTN_LEFT, movecanvasmouse, {.f = 1} },  /* Super+Shift+left drag on empty canvas: pan the canvas */
	{ ClkRoot, 0, BTN_LEFT, movecanvasmouse, {.f = 1} },  /* left drag on empty canvas: pan the canvas */
	{ ClkRoot, 0, BTN_RIGHT, spawn, {.v = termcmd} },  /* right click on empty canvas: open terminal */
	{ ClkTagBar, 0,         BTN_LEFT,   view,       {0} },  /* left click on a tag: view it */
	{ ClkTagBar, 0,         BTN_RIGHT,  toggleview, {0} },  /* right click on a tag: toggle it in the current view */
	{ ClkTagBar, MODKEY,    BTN_LEFT,   tag,        {0} },  /* Super+left click on a tag: move the focused window there */
	{ ClkTagBar, MODKEY,    BTN_RIGHT,  toggletag,  {0} },  /* Super+right click on a tag: toggle the tag on the focused window */
	{ ClkStatus, 0,         BTN_MIDDLE, spawn,      {.v = termcmd} },  /* middle click on the status area: open terminal */
	{ ClkClient, MODKEY, SCROLL_UP,   zoom, {.f = +0.25f} },  /* Super+scroll up over a window: zoom in */
	{ ClkClient, MODKEY, SCROLL_DOWN, zoom, {.f = -0.25f} },  /* Super+scroll down over a window: zoom out */

	{ ClkRoot, MODKEY, SCROLL_UP,   zoom, {.f = +0.25f} },  /* Super+scroll up over empty canvas: zoom in */
	{ ClkRoot, MODKEY, SCROLL_DOWN, zoom, {.f = -0.25f} },  /* Super+scroll down over empty canvas: zoom out */

	{ ClkRoot, 0, SCROLL_UP,   zoom, {.f = +0.25f} },  /* scroll up over empty canvas: zoom in */
	{ ClkRoot, 0, SCROLL_DOWN, zoom, {.f = -0.25f} },  /* scroll down over empty canvas: zoom out */
};
/* Graphics tablet pen buttons. Format: { button, state, function, argument }.
 * The single placeholder entry below binds nothing. */
static const TabletButton tabletbuttons[] = {
	{ 0,            0,                     NULL,       {0} }
};

/* Graphics tablet pad buttons, same format. Placeholder entry only; binds nothing. */
static const TabletPadButton tabletpadbuttons[] = {
	{ 0,            0,                     NULL,       {0} }
};

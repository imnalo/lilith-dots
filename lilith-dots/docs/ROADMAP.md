# Roadmap

## Done
- [x] One-command installer: dry run, backups, safe re-runs, `verify`, `packages` pre-flight
- [x] runit + elogind only; NetworkManager switch as a separate, last, confirmed step (wpa_supplicant disabled, not removed)
- [x] Bluetooth, brightness, audio (PipeWire per the Void handbook), Intel drivers and microcode, Wayland session
- [x] vxwm-style bar (compact, floating, bottom) with icon + percentage for volume, brightness and battery
- [x] Red `REC` badge on the bar while recording
- [x] Menus in the bar's style (wmenu): apps, clipboard, power, fonts, wallpapers, Wi-Fi, Bluetooth, key cheatsheet
- [x] Fonts: Gallant Raster Term (default), JetBrains Mono, Space Grotesk, Terminus, Symbols Nerd Font
- [x] Zen, Strata, Zed, yazi, foot, zsh, fastfetch with a Void logo (no wordmark)
- [x] Screenshots (`Print`) and screen recording (`Super+Print`)
- [x] UI scale from one line in `palette.conf`; default wallpaper `39lg2d`

## Next
- [ ] Rope-corner screenshot selector (damped spring, low bounce), accent colour; needs a native layer-shell client
- [ ] Instant recolouring: patch lilith to load colours, font and wallpaper at runtime, plus palette extraction from the wallpaper
- [ ] Menus that slide up above the bar at bar width, using lilith's own animation curves (native client)
- [ ] Recolour GTK and Qt apps live from the palette
- [ ] README screenshots

## Decided
- Volume and brightness live in the bar. No notification daemon, idle daemon, lock screen or seatd/acpid.

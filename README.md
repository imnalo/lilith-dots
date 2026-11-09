<h1 align="center">lilith-dots</h1>

<p align="center"><i>A personal, opinionated, vibecoded rice for the <a href="https://github.com/ohto121/lilith">lilith</a> Wayland window manager.<br>
Made for one machine: a <b>Lenovo ThinkPad X1 Carbon Gen 7</b> (Intel i7-8565U, UHD 620) on <b>Void Linux (glibc, runit)</b>.</i></p>

<!-- Add screenshots when the desktop is running:
<p align="center"><img src="docs/screenshots/desktop.png" width="820"></p> -->

---

## About

This is **my own** custom rice, built around **one laptop**: a Lenovo ThinkPad X1 Carbon Gen 7 with an Intel CPU
and integrated Intel graphics. It is **opinionated** and **vibecoded** (written together with an AI assistant),
so expect my taste, not a general-purpose distribution. It will probably run on other Void glibc machines, but
the power, firmware and driver choices are tuned for this one.

It stands on the shoulders of three projects. Thank you:

| | |
|---|---|
| **[@ohto121](https://github.com/ohto121)** | [**lilith**](https://github.com/ohto121/lilith): the Wayland compositor with the infinite canvas that everything here is built on |
| **[@ceapeapea](https://github.com/ceapeapea)** | [**lilith-dotfiles**](https://github.com/ceapeapea/lilith-dotfiles): the lilith rice this one is based on |
| **[@ceapeapea](https://github.com/ceapeapea)** | [**vxwm-dotfiles**](https://github.com/ceapeapea/vxwm-dotfiles): the bar-centred design: the bar, its proportions, and menus that look like the bar |

## Philosophy

- **Bar-centred.** The bar is the heart of the desktop, copied from vxwm-dotfiles: compact, floating, 30 px tall,
  8 px above the bottom edge, 57 % of the screen wide (550 px side padding on a 2560 px panel). Menus look like it.
  Volume and brightness show **on the bar** with an icon and a percentage, never as popups.
- **Minimal and brutalist.** Square corners, double borders, no gaps, no blur, no transparency, one font.
- **Terminal-style.** foot + zsh, a pixel font (Gallant Raster Term), menus that are just lines of text.
- **No idle, no lock screen, no notifications.** Open the lid and you are back in your session.
- **Lightweight.** Aiming for **1 GB of RAM or less** at idle. No display manager, no heavy daemons.
- **One source of truth.** Colours, font, UI scale and wallpaper live in one file: `palette.conf`.
- **Readable and safe.** Every file starts with a header saying what it is and how to reload it.
  The installer is idempotent, backs up what it replaces, and verifies itself.

## What you get

### Default apps
| Job | App |
|---|---|
| Browser | **Zen Browser** (`Super+F`) |
| File manager | **Strata** (`Super+E`), with **yazi** in the terminal (`Super+Shift+E`) |
| Editor | **Zed** (`Super+T`) |
| Terminal | **foot** (`Super+Q`), greeting with **fastfetch** and a Void logo without the word |
| Shell | **zsh** with syntax highlighting, autosuggestions, history search, fzf, completions, git-aware prompt |
| Launcher, menus | **wmenu**, styled like the bar (see below) |

### The bar and its menus
The bar sits at the bottom: tags, then cpu, ram, temperature, brightness, volume, battery, and a status text
(`lilith | Sun 08 Nov  19:20`). While you record the screen a **bright red `REC` badge** appears in it.

Menus open on the bottom edge in the bar's colours and font:

| Menu | Key | What it does |
|---|---|---|
| App launcher | `Super+R` | Every program in your PATH |
| Clipboard history | `Super+V` | Text and images (cliphist) |
| Power menu | `Super+Escape` | One line: Exit · Suspend · Reboot · Poweroff (no lock) |
| Key cheatsheet | `Super+/` | Every key binding, searchable |
| Font picker | `Super+Shift+T` | Sets the font for terminal, bar and menus |
| Wallpaper picker | `Super+Shift+W` | Choose from `~/Pictures/Wallpapers` |
| Wi-Fi | `Super+N` | NetworkManager networks (new secured networks open `nmtui`) |
| Bluetooth | `Super+Shift+N` | Power, scan, connect and disconnect |

### Screenshots and recording
`Print` dims the screen and lets you drag an area (accent-coloured outline); `Shift+Print` captures everything.
Files go to `~/Pictures/Screenshots` and the clipboard. `Super+Print` records an area, `Super+Shift+Print` the screen;
press again to stop. Files go to `~/Videos/Recordings`.

### Fonts
**Gallant Raster Term** is the default everywhere (terminal, bar, menus, GTK, fontconfig). Also installed:
**JetBrains Mono** (code in Zed), **Space Grotesk**, **Terminus**, and **Symbols Nerd Font** (the bar icons).

### The system
| | |
|---|---|
| Session | runit + **elogind only** (seat, lid, power button, suspend). No acpid, no seatd, no idle daemon |
| Network | **NetworkManager** + `nmtui`. `wpa_supplicant` is *disabled*, not removed (NetworkManager needs it) |
| Bluetooth | bluez + `bluetoothd`, your user in the `bluetooth` group |
| Audio | PipeWire + WirePlumber + `alsa-pipewire`, wired as the Void handbook describes |
| Graphics | Mesa (iris), Vulkan, Intel VA-API (`iHD`), Wayland-native session |
| Power | tlp + thermald, charge capped at 80 %, Intel microcode (nonfree repo, enabled for you) |
| Brightness | `brightnessctl` (your user in `video`), keys show on the bar |

### UI scale
Change **one line**: `scale=1` in `~/.config/lilith-rice/palette.conf` (try `1.25` or `1.5`), then `lilith-theme`
and restart the session.

## Dependencies

All of these are installed for you. Void packages (glibc, x86_64):
```sh
sudo xbps-install -y base-devel git pkg-config make gcc wlroots0.19-devel \
  wayland-devel wayland-protocols libinput-devel libxkbcommon-devel libdrm-devel \
  fcft-devel pixman-devel xcb-util-wm-devel xorg-server-xwayland bluez dbus elogind \
  NetworkManager foot foot-terminfo zsh zsh-syntax-highlighting zsh-autosuggestions \
  zsh-completions zsh-history-substring-search yazi fzf fastfetch wmenu wl-clipboard \
  cliphist grim slurp wf-recorder curl brightnessctl pipewire wireplumber \
  alsa-pipewire fontconfig dejavu-fonts-ttf terminus-font unzip xz mesa-dri \
  vulkan-loader mesa-vulkan-intel intel-media-driver linux-firmware-intel sof-firmware \
  tlp thermald
```
Strata runtime libraries: see `packages/void-strata.txt`. Zen runtime libraries: `packages/void-zen.txt`.
Downloaded (not in Void's repos): Gallant, JetBrains Mono, Space Grotesk, Symbols Nerd Font, Strata, Zen, Zed.
`lilith-rice packages` checks that every package name exists before you install anything.

## Install (with the script)

Finish a normal Void installation, connect to Wi-Fi (wpa_supplicant), and make sure your user is in
`wheel`, `audio`, `video` and `network`. Then:

```sh
sudo xbps-install -Syu                      # update the system (xbps first if it asks)
sudo xbps-install -y git
git clone https://github.com/imnalo/lilith-dots ~/lilith-dots
cd ~/lilith-dots
./lilith-rice install                       # everything except the network switch
./lilith-rice network                       # LAST: wpa_supplicant -> NetworkManager, then run nmtui
reboot
```

Log in on **tty1**: the desktop starts by itself. Press `Super+/` to see every key.
If something prints `FAIL`, read the hint next to it; `./lilith-rice verify` shows the whole picture.
Every step in detail: **[docs/WHAT-IT-DOES.md](docs/WHAT-IT-DOES.md)**.

| Command | What it does |
|---|---|
| `install` | deps, services, bluetooth, fonts, wallpapers, source, config, build, strata, zen, zed, verify |
| `deps` | System update, nonfree repo, every package one by one, Intel microcode |
| `packages` | Checks that every package name exists in the Void repos (installs nothing) |
| `services` | Enables dbus, elogind, bluetoothd, tlp, thermald |
| `bluetooth` | Bluetooth group and rfkill |
| `fonts` | Gallant, JetBrains Mono, Space Grotesk, Symbols Nerd Font (checksums pinned where possible) |
| `wallpapers` | The eight wallhaven wallpapers to `~/Pictures/Wallpapers` |
| `source` / `config` / `build` | Fetch lilith, link dotfiles and system files, compile lilith |
| `strata` / `zen` / `zed` | Install the apps from their official releases |
| `network` | Switch Wi-Fi to NetworkManager (asks first) |
| `theme` | Re-apply `palette.conf` |
| `verify` / `update` | Check everything / pull and rebuild |

## Install (manually)

Everything the script does, by hand, as your normal user (`sudo` where shown).

**1. Update, enable the nonfree repo, install packages**
```sh
sudo xbps-install -Syu
sudo xbps-install -y void-repo-nonfree && sudo xbps-install -Sy
sudo xbps-install -y base-devel git pkg-config make gcc wlroots0.19-devel \
  wayland-devel wayland-protocols libinput-devel libxkbcommon-devel libdrm-devel \
  fcft-devel pixman-devel xcb-util-wm-devel xorg-server-xwayland bluez dbus elogind \
  NetworkManager foot foot-terminfo zsh zsh-syntax-highlighting zsh-autosuggestions \
  zsh-completions zsh-history-substring-search yazi fzf fastfetch wmenu wl-clipboard \
  cliphist grim slurp wf-recorder curl brightnessctl pipewire wireplumber \
  alsa-pipewire fontconfig dejavu-fonts-ttf terminus-font unzip xz mesa-dri \
  vulkan-loader mesa-vulkan-intel intel-media-driver linux-firmware-intel sof-firmware \
  tlp thermald
sudo xbps-install -y intel-ucode && sudo xbps-reconfigure -fa      # Intel microcode (nonfree)
```

**2. Services (runit)**
```sh
for s in dbus elogind bluetoothd tlp thermald; do sudo ln -s /etc/sv/$s /var/service/$s; done
```

**3. Get this repo and the compositor**
```sh
git clone https://github.com/imnalo/lilith-dots ~/lilith-dots
git clone https://github.com/ohto121/lilith ~/.local/src/lilith
```
lilith is not packaged for Void, so it is compiled from source as your normal user. Sources live in
`~/.local/src/lilith`, the result is one binary, installed to `~/.local/bin/lilith`. All build libraries came with
the `-devel` packages above (notably `wlroots0.19-devel`; lilith needs wlroots 0.19, not 0.20).

**4. Fonts** (into `~/.local/share/fonts/lilith`)
```sh
mkdir -p ~/.local/share/fonts/lilith /tmp/fonts && cd /tmp/fonts
curl -fsSLo gallant.tar.gz https://codeload.github.com/NanoBillion/gallant/tar.gz/v0.1
echo "bb5477bb2b0c2e06b0242d1c6da17d957d78654fb4df9374dc49862b67b75c40  gallant.tar.gz" | sha256sum -c -                    # must say OK
tar -xzf gallant.tar.gz && cp gallant-0.1/gallant.ttf ~/.local/share/fonts/lilith/
curl -fsSLo jb.zip https://github.com/JetBrains/JetBrainsMono/releases/download/v2.304/JetBrainsMono-2.304.zip
echo "6f6376c6ed2960ea8a963cd7387ec9d76e3f629125bc33d1fdcd7eb7012f7bbf  jb.zip" | sha256sum -c -                           # must say OK
unzip -q jb.zip -d jb && cp jb/fonts/ttf/JetBrainsMono-{Regular,Bold,Italic,BoldItalic}.ttf ~/.local/share/fonts/lilith/
curl -fsSLo sg.zip https://github.com/floriankarsten/space-grotesk/releases/download/2.0.0/SpaceGrotesk-2.0.0.zip
unzip -q sg.zip -d sg && find sg -name '*.ttf' -exec cp {} ~/.local/share/fonts/lilith/ \;
curl -fsSLo nerd.zip https://github.com/ryanoasis/nerd-fonts/releases/latest/download/NerdFontsSymbolsOnly.zip
unzip -q nerd.zip -d nerd && cp nerd/SymbolsNerdFont-Regular.ttf ~/.local/share/fonts/lilith/
fc-cache -f && fc-list | grep -i "gallant"      # shows the real family name of the Gallant file
```
Terminus comes from the `terminus-font` package. If the Gallant family is not called `Gallant Raster Term`,
put its real name in `font=` in `palette.conf` (the script does this for you).

**5. Wallpapers** (`wallpapers/wallhaven.txt`; tries `.jpg`, then `.png`)
```sh
mkdir -p ~/Pictures/Wallpapers && cd ~/Pictures/Wallpapers
for id in 0qy157 g8kyj3 zpvdzv 39lg2d 90kkr1 2166q9 qrpp7d og7rj9; do
  p=$(echo $id | cut -c1-2)
  curl -fLO "https://w.wallhaven.cc/full/$p/wallhaven-$id.jpg" || curl -fLO "https://w.wallhaven.cc/full/$p/wallhaven-$id.png"
done
```
The default wallpaper is `39lg2d`.

**6. Palette, compositor config, build**
```sh
mkdir -p ~/.config/lilith-rice ~/.local/bin
cp ~/lilith-dots/theme/palette.conf ~/.config/lilith-rice/palette.conf
cp ~/lilith-dots/lilith/config.h ~/.local/src/lilith/config.h
cp ~/lilith-dots/lilith/config/*.h ~/.local/src/lilith/config/
ln -sf ~/lilith-dots/bin/lilith-theme ~/.local/bin/lilith-theme
~/.local/bin/lilith-theme --no-build                    # writes theme.h, foot and Strata colours
make -C ~/.local/src/lilith                              # compile
install -Dm755 ~/.local/src/lilith/lilith ~/.local/bin/lilith
```

**7. Dotfiles and scripts**
```sh
for f in ~/lilith-dots/bin/*; do ln -sf "$f" ~/.local/bin/$(basename "$f"); done
ln -sf ~/lilith-dots/lilith-rice ~/.local/bin/lilith-rice
mkdir -p ~/.config/{foot,yazi,fontconfig,fastfetch,gtk-3.0,gtk-4.0,zed}
ln -sf ~/lilith-dots/config/foot/foot.ini          ~/.config/foot/foot.ini
ln -sf ~/lilith-dots/config/yazi/yazi.toml         ~/.config/yazi/yazi.toml
ln -sf ~/lilith-dots/config/fontconfig/fonts.conf  ~/.config/fontconfig/fonts.conf
ln -sf ~/lilith-dots/config/fastfetch/config.jsonc ~/.config/fastfetch/config.jsonc
ln -sf ~/lilith-dots/config/gtk-3.0/settings.ini   ~/.config/gtk-3.0/settings.ini
ln -sf ~/lilith-dots/config/gtk-4.0/settings.ini   ~/.config/gtk-4.0/settings.ini
ln -sf ~/lilith-dots/config/zed/settings.json      ~/.config/zed/settings.json
ln -sf ~/lilith-dots/config/zsh/zshrc    ~/.zshrc
ln -sf ~/lilith-dots/config/zsh/zprofile ~/.zprofile
sudo usermod -s "$(command -v zsh)" "$USER"
```

**8. System files, power menu, audio**
```sh
sudo install -Dm644 ~/lilith-dots/system/etc/elogind/logind.conf.d/10-lilith.conf /etc/elogind/logind.conf.d/10-lilith.conf
sudo install -Dm644 ~/lilith-dots/system/etc/tlp.d/10-x1c7.conf /etc/tlp.d/10-x1c7.conf
# power menu: let wheel suspend/reboot/poweroff without a password (check the paths with: command -v zzz reboot poweroff)
echo '%wheel ALL=(root) NOPASSWD: /usr/bin/zzz, /usr/bin/reboot, /usr/bin/poweroff' | sudo tee /etc/sudoers.d/10-lilith-power
sudo chmod 0440 /etc/sudoers.d/10-lilith-power && sudo visudo -c
sudo mkdir -p /etc/pipewire/pipewire.conf.d /etc/alsa/conf.d
sudo ln -s /usr/share/examples/wireplumber/10-wireplumber.conf /etc/pipewire/pipewire.conf.d/
sudo ln -s /usr/share/examples/pipewire/20-pipewire-pulse.conf /etc/pipewire/pipewire.conf.d/
sudo ln -s /usr/share/alsa/alsa.conf.d/50-pipewire.conf /etc/alsa/conf.d/
sudo ln -s /usr/share/alsa/alsa.conf.d/99-pipewire-default.conf /etc/alsa/conf.d/
```

**9. Bluetooth**
```sh
sudo usermod -aG bluetooth "$USER" && sudo rfkill unblock bluetooth
```

**10. Strata, Zen, Zed**
```sh
sudo xbps-install -y bubblewrap ffmpeg ffmpegthumbnailer gstreamer1 gst-libav \
  gst-plugins-base1 gst-plugins-good1 gtk4 gtksourceview5 gvfs poppler-glib \
  adwaita-icon-theme
# Strata: download the x86_64-unknown-linux-gnu archive + .sha256 from https://github.com/lgse/strata/releases/latest
sha256sum -c strata-*-x86_64-unknown-linux-gnu.tar.gz.sha256            # must say OK
tar -xzf strata-*-x86_64-unknown-linux-gnu.tar.gz && install -Dm755 strata-*-x86_64-unknown-linux-gnu/strata ~/.local/bin/strata
# Zen:
sudo xbps-install -y gtk+3 dbus-glib alsa-lib libXtst pciutils
curl -fsSLO https://github.com/zen-browser/desktop/releases/latest/download/zen.linux-x86_64.tar.xz
mkdir -p ~/.local/opt && tar -xJf zen.linux-x86_64.tar.xz -C ~/.local/opt && ln -sf ~/.local/opt/zen/zen ~/.local/bin/zen
# Zed:
curl -fsSL "https://cloud.zed.dev/releases/stable/latest/download?asset=zed&arch=x86_64&os=linux&source=docs" -o zed.tar.gz
tar -xzf zed.tar.gz -C ~/.local && ln -sf ~/.local/zed.app/bin/zed ~/.local/bin/zed
```

**11. Switch Wi-Fi to NetworkManager (last)**
```sh
sudo rm /var/service/wpa_supplicant /var/service/dhcpcd        # only the service links; the packages stay
sudo ln -s /etc/sv/NetworkManager /var/service/NetworkManager
nmtui                                                           # activate a connection, enter the password
```
`wpa_supplicant` stays installed because NetworkManager uses it as its Wi-Fi backend; only its *service* would clash.

**12. Reboot and log in on tty1.**

## Keys

`Super` is the main modifier. The original lilith bindings are kept; I only added new ones. Every binding lives in
[`lilith/config/config_keys.h`](lilith/config/config_keys.h), and `Super+/` lists them on screen.

| Keys | Action |
|---|---|
| `Super+Q` / `Super+Enter` | Terminal |
| `Super+F` / `Super+E` / `Super+T` | Zen browser / Strata / Zed |
| `Super+Shift+E` | yazi |
| `Super+R` | App launcher |
| `Super+V` | Clipboard history |
| `Super+Escape` | Power menu |
| `Super+/` | Key cheatsheet |
| `Super+Shift+T` / `Super+Shift+W` | Font picker / wallpaper picker |
| `Super+N` / `Super+Shift+N` | Wi-Fi menu / Bluetooth menu |
| `Print` / `Shift+Print` | Screenshot: area / whole screen |
| `Super+Print` / `Super+Shift+Print` | Record: area / whole screen (again to stop) |
| `Super+C` | Close window |
| `Super+Shift+F` | Fullscreen |
| `Super+1…9` | View a tag; `+Shift` send the window there; `+Ctrl` toggle it |
| `Super+0` | Show all tags |
| `Super+W/A/S/D` | Focus the window above / left / below / right |
| `Super+Tab` / `Super+K` | Next / previous window, centred |
| `Super+Shift+Tab` | Centre the focused window |
| `Super+Z` | Zoom out to fit all windows |
| `Super+=` / `Super+-` | Zoom in / out |
| `Super+Home` | Return the canvas to home |
| `Super+Shift+Arrows` | Pan the canvas |
| `Super+B` | Show / hide the bar |
| `Super+Shift+Q` | Quit lilith |
| Volume / brightness keys | Change them; the bar updates |

**Mouse:** drag empty canvas to pan · scroll over the canvas to zoom · `Super`+left-drag moves a window ·
`Super`+right-drag resizes it · right-click empty canvas for a terminal.

## Animations
lilith's original animations are kept untouched (`lilith/config/config_animation.h`), as in its developer's demo.

## Customising

| I want to change… | Edit | Then |
|---|---|---|
| Colours, font, scale, wallpaper | `~/.config/lilith-rice/palette.conf` | `lilith-theme`, restart the session |
| Bar layout and text | `lilith/config/config_bar.h` | `lilith-rice build`, restart the session |
| Borders / animations / keys / touchpad | `lilith/config/config_*.h` | same |
| Packages | `packages/*.txt` | `lilith-rice deps` |
| zsh, foot, yazi, fastfetch, Zed | `config/<app>/…` | open a new window |

## Status

Working: everything above. **Not built yet** ([docs/ROADMAP.md](docs/ROADMAP.md)): instant recolouring from the wallpaper
(colours are set in `palette.conf` for now), menus that slide up at bar width (today they span the bottom edge), and the
rope-corner screenshot selector (today: dimmed screen and an accent-coloured outline).

## Layout

```
lilith-rice          the installer (one command)
bin/                 lilith-session · autostart · status · menu · theme · shot · record
lilith/              compositor config (config.h + config/*.h), copied into the lilith source tree
config/              foot · zsh · yazi · fontconfig · fastfetch · gtk · zed (symlinked into ~)
system/              files installed to /etc (elogind, tlp)
packages/            package, service and download lists
wallpapers/          wallhaven IDs (no images in the repo)
theme/palette.conf   colours, font, scale, wallpaper
docs/                WHAT-IT-DOES.md · ROADMAP.md
```

## Licences
lilith is by [@ohto121](https://github.com/ohto121); the files under `lilith/` are derived from its configuration and
keep its licences. Design and many ideas from [@ceapeapea](https://github.com/ceapeapea). [Strata](https://github.com/lgse/strata)
is by lgse. Everything else here is MIT.

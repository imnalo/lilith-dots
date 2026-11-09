# What `lilith-rice` does, exactly

Everything the installer touches, in the order it happens. Nothing else on your system is changed.

- Run it as your **normal user**. It uses `sudo` (or `doas`) only for steps marked **root**.
- `DRY=1 ./lilith-rice <command>` prints every root command instead of running it.
- Every step is safe to repeat. A file it replaces is first moved to `~/.config-backup/<time>/`.
- It always has `~/.local/bin` in its own PATH, so it finds the tools it just installed.

## `./lilith-rice install`

| # | Step | Fails the install? |
|---|---|---|
| 1 | `deps` | yes, if a required package is missing |
| 2 | `services` | yes |
| 3 | `bluetooth` | yes |
| 4 | `fonts` | no, only a warning |
| 5 | `wallpapers` | no, only a warning |
| 6 | `source` | yes |
| 7 | `config` | yes |
| 8 | `build` | yes |
| 9 | `strata`, `zen`, `zed` | no, only warnings |
| 10 | `verify` | reports everything |

`network` is deliberately **not** part of `install` (see the end).

### 1. `deps`: packages
1. **root** `xbps-install -Sy` syncs the repos (updating xbps first if it asks).
2. **root** `xbps-install -Syu` updates the whole system. Void does not support partial upgrades.
3. **root** enables **`void-repo-nonfree`** (Intel microcode and some firmware live there) and syncs.
4. **root** installs every package in `packages/void-required.txt`, **one at a time**; installed ones are skipped,
   failures are listed at the end with a hint. They cover:
   - build tools and lilith's build libraries: `base-devel`, `wlroots0.19-devel`, wayland, libinput, xkbcommon, drm, fcft, pixman, xcb-util-wm, XWayland
   - session: dbus, elogind, NetworkManager, bluez
   - desktop: foot, zsh and its plugins, yazi, fzf, fastfetch, wmenu, wl-clipboard, cliphist, grim, slurp, wf-recorder, curl, brightnessctl
   - audio: pipewire, wireplumber, alsa-pipewire
   - fonts and tools: fontconfig, DejaVu, Terminus, unzip, xz
   - the X1 Carbon: Mesa, Vulkan, Intel media driver, Intel and SOF firmware, tlp, thermald
5. **root** installs the optional list (`xdg-utils`); a failure only warns.
6. **root** installs `intel-ucode` and rebuilds the initramfs (`xbps-reconfigure -fa`, about a minute); a failure only warns.

`./lilith-rice packages` is a read-only pre-flight: it asks the Void repos whether each name exists.

### 2. `services`: runit
**root** For `dbus`, `elogind`, `bluetoothd`, `tlp`, `thermald` it links `/var/service/<n> -> /etc/sv/<n>` unless it exists.
Nothing is disabled. Your `chronyd`, your `dhcpcd`/`wpa_supplicant` (until `network`) and your choice about `acpid` are untouched.

| Service | Job |
|---|---|
| dbus | Message bus; elogind, NetworkManager, bluez and PipeWire need it |
| elogind | Lets your user use the screen, keyboard and GPU without root; creates `XDG_RUNTIME_DIR`; lid, power button, suspend |
| bluetoothd | The Bluetooth daemon (bluez) |
| tlp | Background power management; caps the battery charge at 80 % |
| thermald | Intel thermal daemon: keeps the CPU from overheating and throttling hard |

### 3. `bluetooth`
**root** Adds you to the `bluetooth` group (needed to talk to bluez without root; applies after you log in again)
and runs `rfkill unblock bluetooth` so a blocked radio does not look like a driver problem.

### 4. `fonts` (no root, into `~/.local/share/fonts/lilith`)
Downloads and installs **Gallant** (SHA-256 checked), **JetBrains Mono** (SHA-256 checked), **Space Grotesk** and
**Symbols Nerd Font** (HTTPS only), then `fc-cache -f`. A checksum mismatch deletes the file and fails that font.
Terminus comes from the `terminus-font` package.

### 5. `wallpapers`
Downloads each ID in `wallpapers/wallhaven.txt` to `~/Pictures/Wallpapers/wallhaven-<id>.jpg` (or `.png`).
Existing files are skipped. `39lg2d` is the default wallpaper (set in `palette.conf`).

### 6. `source`
Clones `https://github.com/ohto121/lilith` into `~/.local/src/lilith`, or fetches and resets it to upstream.
That tree is generated from this repo plus upstream, so do not keep edits there.

### 7. `config`
1. **Dotfiles**: symlinks into this repo (so `git pull` updates them), executable bits restored:

   | Link | Target |
   |---|---|
   | `~/.local/bin/lilith-rice`, `lilith-*` | `lilith-rice`, `bin/*` |
   | `~/.config/foot/foot.ini` | `config/foot/foot.ini` |
   | `~/.config/yazi/yazi.toml` | `config/yazi/yazi.toml` |
   | `~/.config/fontconfig/fonts.conf` | `config/fontconfig/fonts.conf` |
   | `~/.config/fastfetch/config.jsonc` | `config/fastfetch/config.jsonc` |
   | `~/.config/gtk-3.0/settings.ini`, `gtk-4.0/settings.ini` | `config/gtk-*/settings.ini` |
   | `~/.config/zed/settings.json` | `config/zed/settings.json` |
   | `~/.zshrc`, `~/.zprofile` | `config/zsh/zshrc`, `zprofile` |

   `~/.config/lilith-rice/palette.conf` is copied from `theme/palette.conf` **only if it does not exist**, so your choices survive.
   If the Gallant file calls itself something other than "Gallant Raster Term", `font=` is set to its real name.
2. **System files** **root**: `/etc/elogind/logind.conf.d/10-lilith.conf` (lid and power button, no idle) and `/etc/tlp.d/10-x1c7.conf`.
3. **Power menu** **root**: `/etc/sudoers.d/10-lilith-power`: members of `wheel` may run **only** `zzz`, `reboot`, `poweroff`
   without a password. The rule is validated with `visudo -c` first; if it does not validate, nothing is installed.
4. **Audio** **root**: the links the Void handbook describes: `pipewire` starts WirePlumber and pipewire-pulse itself,
   and ALSA apps use PipeWire (`/etc/pipewire/pipewire.conf.d/*`, `/etc/alsa/conf.d/*`).
5. **Login shell** **root**: `usermod -s <zsh>`.
6. **lilith config**: copies `lilith/config.h` and `lilith/config/*.h` into the source tree, then runs `lilith-theme --no-build`
   (palette to `theme.h`, foot colours and font, Strata theme).

### 8. `build`
Checks that `wlroots-0.19` development files exist, regenerates the palette outputs, runs `make` in `~/.local/src/lilith`
(`build.log`; the last lines are shown on failure) and installs the binary to `~/.local/bin/lilith`.

### 9. `strata`, `zen`, `zed`
- **Strata**: needs x86_64 and **glibc 2.39+**; installs its runtime libraries (**root**), reads the latest release from the GitHub API,
  downloads the `x86_64-unknown-linux-gnu` archive and its `.sha256`, **verifies it (nothing is installed on a mismatch)**, installs `~/.local/bin/strata`.
- **Zen**: installs its runtime libraries (**root**), downloads the official `zen.linux-x86_64.tar.xz`, unpacks to `~/.local/opt/zen`,
  links `~/.local/bin/zen`, writes a desktop entry. No checksum is published, so it relies on HTTPS.
- **Zed**: downloads the official tarball, unpacks to `~/.local/zed.app`, links `~/.local/bin/zed`, writes the desktop entry as Zed's docs describe.
  Needs Vulkan, which `mesa-vulkan-intel` provides.

### 10. `verify`
Read-only. Checks every command, the services, groups, the elogind, sudo and PipeWire files, fonts, palette, fastfetch config,
the login shell, wallpapers, and the apps. Warns about `acpid` or an unset `XDG_RUNTIME_DIR`. Exits non-zero on problems.

## `./lilith-rice network` (last, on purpose)
Asks for confirmation. Then **root**: removes the `/var/service/wpa_supplicant` and `/var/service/dhcpcd` **links** (the packages stay;
NetworkManager uses wpa_supplicant as its Wi-Fi backend) and enables `/var/service/NetworkManager`. Your Wi-Fi drops for a moment; run `nmtui` to reconnect.

## The scripts it installs

| Script | Job |
|---|---|
| `lilith-session` | Starts lilith in a D-Bus session from tty1 (via `~/.zprofile`): `lilith-status | lilith`. Log: `~/.cache/lilith/session.log` |
| `lilith-autostart` | Run by lilith: PipeWire and the clipboard watchers |
| `lilith-status` | The bar's status text (clock) and the red `REC` badge |
| `lilith-menu` | All bar-style menus (wmenu): apps, clip, power, font, wall, wifi, bluetooth, cheat |
| `lilith-theme` | `palette.conf` to `theme.h`, foot colours and font, Strata theme; recolours open terminals; rebuilds lilith |
| `lilith-shot` | Screenshots (`grim` + `slurp`) |
| `lilith-record` | Screen recording (`wf-recorder`); signals `lilith-status` |

## Undoing it
```sh
rm ~/.local/bin/lilith ~/.local/bin/lilith-* ~/.local/bin/{strata,zen,zed}
rm -r ~/.local/opt/zen ~/.local/zed.app ~/.local/share/fonts/lilith
rm ~/.zshrc ~/.zprofile ~/.config/{foot/foot.ini,yazi/yazi.toml,fontconfig/fonts.conf,fastfetch/config.jsonc,zed/settings.json}
sudo rm /var/service/{bluetoothd,tlp,thermald}          # keep dbus and elogind if other things use them
sudo rm /etc/elogind/logind.conf.d/10-lilith.conf /etc/tlp.d/10-x1c7.conf /etc/sudoers.d/10-lilith-power
sudo rm /etc/pipewire/pipewire.conf.d/{10-wireplumber,20-pipewire-pulse}.conf /etc/alsa/conf.d/{50-pipewire,99-pipewire-default}.conf
```
Backups of anything replaced are in `~/.config-backup/`.

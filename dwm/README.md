# dwm - dynamic window manager

dwm is an extremely fast, small, and dynamic window manager for X.

![dwm screenshot](assets/screenshot.png)

## Requirements

In order to build dwm you need the Xlib header files.

## Installation

1. Edit `config.mk` to match your local setup (dwm is installed into the `/usr/local` namespace by default).
2. Edit `config.def.h` to configure keybindings, colors, and rules.

## Building

To build and install dwm, simply run the rebuild script:

    ./rebuild.sh

This script handles cleaning, compiling, and installing the binary (sudo permissions may be required depending on your installation path).

## Running dwm

Add the following line to your `.xinitrc` to start dwm using `startx`:

    exec dwm

If you are using a display manager (like LightDM or SDDM), ensure a `dwm.desktop` file is present in `/usr/share/xsessions/`.

### Status Bar

To display status info in the bar, you can use `slstatus` or a simple loop in your `.xinitrc`:

    while xsetroot -name "$(date) $(uptime | sed 's/.*,//')"; do
        sleep 1
    done &
    exec dwm

## Configuration

The configuration of dwm is done by creating a custom `config.h` and (re)compiling the source code.

**Note:** Always edit `config.def.h`. The `rebuild.sh` script handles copying it to `config.h` automatically.

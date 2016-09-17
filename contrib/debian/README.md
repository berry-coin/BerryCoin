
Debian
====================
This directory contains files used to package berrycoind/berrycoin-qt
for Debian-based Linux systems. If you compile berrycoind/berrycoin-qt yourself, there are some useful files here.

## berrycoin: URI support ##


berrycoin-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install berrycoin-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your berrycoin-qt binary to `/usr/bin`
and the `../../share/pixmaps/bitcoin128.png` to `/usr/share/pixmaps`

berrycoin-qt.protocol (KDE)



Debian
====================
This directory contains files used to package covid19d/covid19-qt
for Debian-based Linux systems. If you compile covid19d/covid19-qt yourself, there are some useful files here.

## covid19: URI support ##


covid19-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install covid19-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your covid19-qt binary to `/usr/bin`
and the `../../share/pixmaps/covid19128.png` to `/usr/share/pixmaps`

covid19-qt.protocol (KDE)


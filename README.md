# Aquila Air Mouse Driver

This driver was developed by reversing the original Aquila Air binaries made for Windows. reversing OemDrv.exe and Lowdev.dll

## Dependencies

- hidapi-devel
- glfw-devel
- mesa-libGL-devel

## Build & Run

./build-and-open.sh

The first run installs a udev rule for the mouse (asks for sudo once) so the driver can run as your user; running the GUI through sudo breaks the display connection.

## Links

- Writeup: https://writeups.nicolas.rest/article.html?f=mouse_driver.md

![GUI](assets/gui.png)

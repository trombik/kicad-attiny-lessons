# AVR MCU lessons

Various AVR MCU lessons at Makers. The lessons are intended for middle level
students, who have mastered basic programming with Arduino. The lessons are
written in pure C, not Arduino. In the lessons, you will learn the internal of
AVR MCUs. You will have to control memory mapped resisters, use avr libc, and
go through the data sheet.

The data sheet can be downloaded at
[Microchip website](https://www.microchip.com/en-us/product/ATtiny85).

## Requirements

All lessons requires the followings:

* Python 3.x
* `tox` python module (see [tox installation](https://tox.wiki/en/latest/install.html))
* ["Arduino as ISP" programmer](https://github.com/trombik/kicad-avr-programmer)
* 5V power source, such as USB
* ATTiny85-20P (DIP package)

## Setting up `platformio`

At the top directory, run:

```console
tox
```

You should see something like:

```console
...
python run-test: commands[0] | pio --version
PlatformIO Core, version 6.1.4
_______________ summary ______________
  python: commands succeeded
  congratulations :)
```

Then, activate the python virtual environment. For Windows:

```console
.tox/python/bin/activate.bat
```

For others:

```console
source .tox/python/bin/activate
```

## Writing the firmware

Build the firmware:

```console
pio run
```

Write the firmware:

```console
pio run -t upload --upload-port ${PORT}
```

Replace `${PORT}` with the one on your machine, such as `COM1` for Windows,
`/dev/ttyUSB0` for Linux, `/dev/cu.XXXX` for macOS, and `/dev/cuaU0` for
FreeBSD.

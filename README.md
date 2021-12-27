# ngage-display-converter

A modern clone of the [Nokia N-Gage display
converter](https://archive.org/details/Nokia_N-Gage_Gallery_E3_2004/E3_2004_031.jpg)
developed for the [Finnish Museum of
Games](https://www.vapriikki.fi/en/pelimuseo/) to replicate the display
on a larger monitor while the N-Gage continues to output an image on the
onscreen.

## Status

The project is under development and is not functional in its current
state.

## Compiling

First install the [Raspberry Pi Pico SDK](https://datasheets.raspberrypi.com/pico/getting-started-with-pico.pdf).

The project can then be compiled using CMake:
```bash
mkdir build
cd build
cmake -DPICO_COPY_TO_RAM=1 ..
make
```

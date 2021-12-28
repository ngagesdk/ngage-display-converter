# Firmware

## Compiling

First install the [Raspberry Pi Pico SDK](https://datasheets.raspberrypi.com/pico/getting-started-with-pico.pdf).

The project can then be compiled using CMake:
```bash
mkdir build
cd build
cmake -DPICO_COPY_TO_RAM=1 ..
make
```

## Licence and Credits

The project is licensed under "The MIT License" unless stated otherwise.
See the file [LICENSE.md](LICENSE.md) for details.

[PicoDVI](https://github.com/Wren6991/PicoDVI) by Luke Wren is licensed
under a BSD 3-Clause License.  See the file
[LICENSE](src/libdvi/LICENSE) for details.

The N-Gage QD overlay was designed by [Dan
Whelan](https://danwhelan.ie/) and is inspired by the original overlay
used by Nokia.

# Stub project for "new" 0-series megaAVR microcontrollers

This is a sample project demonstrating how to compile and upload code for the new ATmega808/809/1608/1609/3208/3209/4808/4809 microcontrollers without using an IDE.

These new chips do not use the 2x3-pin ISP connection for flashing. Instead, they use a 1-wire protocol called UPDI. You won't need a special programming device, just an [FTDI USB-to-serial cable](https://www.sparkfun.com/products/9718).

**Note: these instructions are currently only for macOS and Linux.**

## Installing the toolchain

If you've done AVR development for the previous-generation Atmel chips (ATmega328P, ATmega644P, ATtiny85, etc.) you've probably installed the GNU distribution of avr-gcc/avr-libc from your OS's package manager (Homebrew, apt-get, etc.) **However** (as of 1/7/2020) support for these newer parts is only available in Microchip's toolchain. Installing it is a somewhat manual process, but is fairly straightforward.

1. Download the AVR 8-bit toolchain for your platform from [Microchip's site](https://www.microchip.com/mplab/avr-support/avr-and-arm-toolchains-c-compilers). You'll wind up with a file named something like `avr8-gnu-toolchain-osx-3.6.2.503-darwin.any.x86_64.tar.gz` or `avr8-gnu-toolchain-3.6.2.1759-linux.any.x86_64.tar.gz`.
2. Extract this archive. You'll wind up with a directory named something like `avr8-gnu-toolchain-darwin_x86_64` or `avr8-gnu-toolchain-linux_x86_64`.
3. Move this directory to a system-wide location, like `/usr/local` or `/opt/local`. (The Makefile in this repo assumes you are using `/usr/local`.) Use `sudo` if necessary.
4. Download the "Atmel ATmega Series Device Support" package from [http://packs.download.atmel.com](http://packs.download.atmel.com). 
5. Change the file extension on the downloaded `.atpack` file to `.zip` and unzip it. You'll wind up with a directory named something like `Atmel.ATmega_DFP.1.4.346`.
6. Move this directory to the same directory from step 3. Use `sudo` if necessary.
7. Download **pyupdi** from GitHub: [https://github.com/mraardvark/pyupdi/archive/master.zip](https://github.com/mraardvark/pyupdi/archive/master.zip).
8. Unzip the archive and rename the directory from `pyupdi-master` to `pyupdi`.
9. Move the `pyupdi` directory to the same directory as in step 3. Your base directory (e.g. `/usr/local`) should now contain these three subdirectories:
 - `avr8-gnu-toolchain-<osname>/`
 - `Atmel.ATmega_DFP.<version>/`
 - `pyupdi/`
10. If you don't have the PySerial and IntelHex packages installed, install them with `pip3 install pyserial intelhex`.


## Building

If you installed the tools in a directory other than `/usr/local`, change the value of `AVR_BASE_DIR` in the Makefile appropriately.

Run `make` to build the hex file.


## Uploading

Connect your FTDI cable to the chip and power it up. If this is a brand new chip, run `make fuse` to configure the fuse bits for a 20MHz clock frequency.

Run `make flash` to upload your code! The example program (`blink.hex`) will blink an LED connected to PD7 (pin 27 on TQFP parts, pin 16 on PDIP parts) once per second.


## UPDI circuit

All you need is an FTDI cable and a 4.7k resistor. For TQFP/QFN chips, the UPDI pin is pin 41. For DIPs, it's pin 30.

```
  ┌───┐                    ┌──────────┐
  │BLK├───GND              │          │
  │BRN│─x                  │          │
  │RED│─x                  │          │
  │ORN├────[4.7kΩ]──●──────│UPDI      │
  │YEL├─────────────┘      │          │
  │GRN│-x                  │          │
  └───┘                    └──────────┘
FTDI cable                  ATmega4809 
```


## License

The contents of this repository are released to the public domain.
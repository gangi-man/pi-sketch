# PiSketch

## Overview

PiSketch is the digital version of a drawing toy.

We can draw lines with knobs on a normal display which is connected with en HDMI like cable.

PiSketch is built with the great project [PicoDVI](https://github.com/Wren6991/PicoDVI)

## How to build
The building flow is below.
1. Print 3D models for the enclosure
1. Build the circuit board.
1. Assemble all parts
1. Make [software](https://github.com/gangi-man/pi-sketch) for PiSketch and install uf2 file to Raspberry Pi Pico on the board.

### Print 3D models
Just print all stl files.

There is'nt any cautious point but no support setting makes the raound edge of the enclosure fine.

### Build the circuit board.
Cut a PCB board into 95mm x 45mm size and solder electric parts as the schematic.

### Assemble parts
Put rotary encoders and tacitic switches in the holes and fasten nuts.

Close the lid of enclosure.

### Build binary for PiSketch.
1. Clone this repository
1. Initialize submodules
1. Invoke cmake and build
1. Install the built uf2 file to the Raspberry Pi Pico.

## Usage
If you turn the left knob, the line on the screen moves holizontally and if you turn the right knob, you will see the line moves vertically

### Bill of Materials
* PCB board x 1 (larger than 95mm x 45mm)
* [Pico-DVI-Sock](https://github.com/Wren6991/Pico-DVI-Sock) x 1 I bought one at [Switch Science](https://www.switch-science.com/products/7431)
* Rotary encoder [EC12E2420801](https://tech.alpsalpine.com/j/products/detail/EC12E2420801/) x2
* Capacitor 0.01uF x 4
* Resistor 10k x 8
* USB B micro socket x1 (USB C might be better)

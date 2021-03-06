# PianoLeds2
This is the code of the second generation controller for my MIDI based keyboard LED strip, which makes different LEDs
shine based on the notes I play. It is currently work in progress.

## History
I started the redesign because I found that the [first version](https://github.com/danielschenk/mlc) was not extensible
enough anymore, both in terms of hardware and software.
The first version has some light effect "patches" (presets with different colors) hard-coded into
the firmware, together with the MIDI program numbers they respond to. This means that adding or changing a patch means
C coding, recompiling and flashing the chip.
The plan is a fully configurable version, so I can make and edit light effect patches from my smartphone or notebook,
even last-minute when everything is already setup on stage and the show is about to begin.

I'm an embedded software engineer, and like to make the most out of limited hardware (like the AVR microcontroller which
runs the previous version). However, my time to hobby around is also limited, and I prefer C++ for embedded now, because
of the object-oriented nature of the language. There's enough cheap hardware around which has enough memory and is
powerful enough to make use of these advantages.

## How to build and run
### The ESP32 application
1. Go to the `Esp32Application` folder and copy or rename the file `BoardOverride_template.h` to `BoardOverride.h` and change any pin definitions in there if needed.
1. Install PlatformIO.
1. Execute one of the following:
    1. `platformio run` to only build.
    1. `platformio run --target upload` to build and upload on to the ESP32 module (don't forget to hold the IO0 button).

### The unit tests
Execute one of the following:
- `platformio run -e tests` to build and run all unit tests.
- `platformio run -e tests --target [TestName]` to build and run only that test suite (e.g. _ProcessingChainTest_). 
- `platformio run -e tests --target memcheck` to build and run all unit tests under valgrind (currently doesn't work correctly).

### The MidiInputMonitor (little test application for BaseMidiInput, to run on PC)
This currently only supports Mac.
Execute `platformio run -e pc` to build and `.pioenvs/pc/program` to run.

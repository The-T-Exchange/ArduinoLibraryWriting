# ArduinoLibraryWriting
Norman Dunbar's presentation to the group on the subject of writing Arduino libraries.

The LaTeX files, `*.tex`, in the current directory are the sources for the presentation notes. There's more detail in the notes than in the presentation slides.

`AVRAssemblyLanguage.tex` and `arduinoLanguage.tex` are used to highlight Arduino code as it would be in the IDE.

## Directories

The following directories are supplied.

### Fritzing

This directory contains a Fritzing project and an exported image, showing the breadboard layout used when demonstrating the LM75 temperature sensor sketches, used to show how a sketch can be converted to a library and then modified to use said library.

### LM75_AB

This directory is laid out _exactly_ as it needs to be to be considered in the correct format for an Arduino library. The three boilerplate files are here: 

* `LICENSE` - the licence under which the library is t=released.
* `keywords.txt` - for the Arduino IDE, pre-version 2.x, the keywords used for source code highlighting. Not used in version 2.x, but should still be provided for 1.x users.
* `library.properties` - the library properties file, funnily enough.

There is a `src` directory where the source and header files are to be found:

* `LM75_AB.h` - header file for the library.
* `LM75_AB.cpp` - source file for the library. This is a `.cpp` file as using a `.c` file results in the errors explained in the `CompilerErrors.txt` file.
* `CompilerErrors.txt` - why you get errors with a `.c` file, when it worked perfectly in a sketch but fails to compile when converted to a library even with _no code changes!_---it's because the system header files have C++ code in them and the C compiler can't compile those!

Finally, there's an `examples` directory with a single sketch, `Temperature.ino`. This simply loops around reading and displaying the current room temperature on the Serial Monitor. 

There is a `LM875_AB.zip` file, in the top-level directory which was used to demonstrate adding a zip library to the Arduino IDE at the presentation.

### Presentation

This directory contains the Libre Office Impress source file, `ArduinoLibraries.odp`. This is the slide show used at the actual presentation by Norman.

### Sketches

This directory has all the sketches used in the presentation.

* `BareBones.ino` - this is the sketch where all the LM75 temperature sensor code is built into the sketch. It does not use any libraries for the LM75.
* `WithLibrary.ino` - this is the "after" sketch. The LM75_AB library created in the presentation is used an a new sketch.
* `AssemblyExamples.ino` - this directory contains a few examples of using the Assembly Language version of the LM75 library, written for Norman's *_Arduino Assembly Language_* book, published by Apress in September 2026.

The C++ library created for the presentation is deliberately limited in features. The Assembly Version is fully featured and covers all the features of the LM75 sensors. The demonstration sketches are:

* `LM75A_Comparator.ino` - demonstrates the LM75 raising an over-temperature alarm in comparator mode where the alarm is cancelled when the temperature cools again.
* `LM75A_Interrupt.ino` - demonstrates the LM75 raising an over-temperature alarm in interrupt mode where the alarm remains in force until cancelled. This mode is weird though:

* The over-temperature alarm is raised when the temperature rises above a specific setting.
* The alarm will _not_ be cleared, as comparator mode will, when the temperature drops again.
* If the temperature drops below the low setting, _and_ the over-temperature alarm was manually cleared, another alarm will be raised when the temperature falls below the low setting.
* Alternatively, if the temperature drops below the low setting, _and_ the over-temperature alarm was _not_ cleared, no new alarm will be raised when the temperature falls below the low setting.

This, I think, ensures that in the event of the LM75 being used to monitor unattended systems, any temperature situations will always show that an alarm had been raised. _Unless_, of course, if someone cleared the alarm after temperature dropped again.

I told you it was weird!

* The alarm will be [manually] cleared if _any_ of the sensor's registers are read or written. Which does tend to imply that on receiving an over-temperature alarm, the software should disable further temperature readings until the alarm can be properly attended to by a human, or at the very least, a small dog. ;o)

Anyway, there's a `readme.txt` file to explain the Assembly examples, and a breadboard layout image too.

Have fun.


Norman Dunbar, September 2026.

 

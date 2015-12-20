# ATEmbedded Presentation

ATEmbedded is the core of our application. Its goal is to allow us to generate and send AT commands to the AR Drone, with a lighter framework than the one provided by the official SDK.

## Organisation

Below is an overview of the structure of this project:
.
├── Build
│   ├── core
│   ├── howard
│   ├── test
│   └── Test_Exec
├── Makefile (not yet working)
├── NOTES
└── Sources
    ├── core
    └── test

The source code is in the Source directory, divided in two parts : 
    - The core directory contains the source code of ATEmbedded
    - The test directory contains tests programs, for specific parts of the program. THESE MAY BECOME OUTDATED

The NOTES directory contains some of our notes.

The Build directory is created at compile time and contains the executable (howard), the core and test directories containing the correspoding object files, and the Test_Exec directory containing test executables.

## Compiling

To compile the program, run the make command from the Sources/core directory.
To compile the tests, run the make command from the Sources/test directory.

## core detailed

.
└── Sources
    └── core
        ├── com_AT.c/h
        ├── controller.c/h
        ├── debug.h
        ├── howard.c
        ├── navdata.c/h
        ├── navdata_structs.h
        ├── shared.h
        └── udp_sender.c/h

### udp_sender:
Communicate with the drone through UDP. Offered functionnalities:
- creating/closing UDP sockets
- send messages through these sockets
- receive messages through the sockets
2 UDP sockets are used:
- port 5554, to ask for navdata and receive it
- port 5556, to send AT commands

### com_AT:
Create and send AT commands to the drone. Available commands:
- AT REF: Take off, land, enter and exit emergency mode
- AT PCMD: Move the drone
- AT FTRIM: Trim the drone's sensors. Must be used while lying on the ground
- AT CONFIG: Set the configuration of the drone. In our case, mostly used for navdata configuration
- AT CTRL: Ack command. Used when establishing navdata communication
- AT COMWG: Watchdog. The drone considers the connection lost after 2 seconds with no received message.
- Some more coming
These commands are wrapped under a higher level interface, with simple functions like take_off(), turn_right()...
Navdata are being integrated to provide easy control of the drone.

### navdata_structs:
Definition of the structures used to store navdata.

### navdata:
Provides an interface to:
- initialise navdata reception
- update local navdata
- TODO : change navdata configuration

### controller:
NOT YET IMPLEMETED
This will provide an algorithm to pilot the drone

### shared:
Declaration of global variables that can be used by different parts of the project.

### howard:
Our main program. Contains the declaration of the following threads:
- Main thread, used to pilot the drone for now. Probably will run the controller algorithm in the future
- Navdata thread, to initialize navdata communication and then receive navdata from the drone.
- Watchdog thread, to send a watchdog command every 1.8 second

### debug:
Definition of some macros used for debug purposes

## test detailed
Yeah, but not today



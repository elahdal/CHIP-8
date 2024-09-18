# CHIP-8 Emulator - Project Report

## Overview
This project is an emulator for the **CHIP-8**, an interpreted programming language used in 1970s video game consoles. The emulator simulates the execution of CHIP-8 programs, supporting graphics, input, and sound, providing a platform to run classic CHIP-8 games.

### Key Features
- **Emulation of CHIP-8 Instructions**: The project supports the full set of CHIP-8 opcodes, handling operations like memory manipulation, display management, and input handling.
- **Display Rendering**: A graphical output is generated using a pixel grid, emulating the original 64x32 monochrome display of CHIP-8 systems.
- **Input Handling**: The system emulates the 16-key hexadecimal keyboard used in CHIP-8 programs.
- **Timers and Sound**: The emulator implements delay and sound timers to maintain the game's timing and produce audio output.

## Design Patterns Used

### 1. Interpreter Pattern
The emulator interprets each CHIP-8 opcode and executes it accordingly. The **Interpreter Pattern** is used to define a way to evaluate CHIP-8 instructions and carry out operations like drawing to the screen, updating memory, and handling input.

#### Why Interpreter Pattern?
- **Simplifies Code Execution**: By interpreting opcodes one by one, the emulator easily maps each operation to a specific function.
- **Maintainability**: New opcodes or variations (such as for SCHIP-8) can be added by expanding the interpreter logic without restructuring the core emulator.

### 2. Singleton Pattern
A singleton design pattern is used for managing core components of the system, such as memory and the graphics display, ensuring that only one instance of these components exists throughout the application's lifecycle.

#### Why Singleton Pattern?
- **Resource Management**: The memory and display need to be accessed by different parts of the emulator (e.g., opcode execution and input handling), and having a single instance prevents conflicts and ensures consistent state across the application.

## Emulator Structure

### 1. **CPU**
The central processing unit (CPU) emulates the execution cycle of the CHIP-8 system:
- **Registers**: The CHIP-8 CPU has 16 general-purpose registers (`V0` to `VF`), along with a 16-bit address register (`I`) and a program counter (`PC`).
- **Opcode Fetching and Decoding**: The CPU fetches a 2-byte opcode from memory, decodes it, and executes the corresponding operation.
- **Timers**: Implements delay and sound timers, decrementing them at a rate of 60 Hz.

### 2. **Memory**
The CHIP-8 system has 4KB of memory:
- **Program Storage**: Programs are typically loaded starting at memory address 0x200.
- **Font Storage**: The first portion of memory stores sprite data for displaying characters.

### 3. **Graphics**
The graphics system is built on a 64x32 pixel monochrome display, where each pixel is either on or off. Drawing operations are performed using XOR logic, which allows for sprite collisions and erasing.

### 4. **Input**
The emulator simulates the 16-key hexadecimal keypad used in CHIP-8, mapping keys to corresponding actions in the game.

### 5. **Sound**
The sound system plays a tone whenever the sound timer is greater than zero, simulating the basic audio capabilities of CHIP-8.

## Technology Stack
- **C Programming Language**: The emulator is developed using C, leveraging its low-level memory management and efficient execution.
- **SDL (Simple DirectMedia Layer)**: SDL is used for rendering graphics and handling input, providing cross-platform capabilities.
- **Hexadecimal and Bitwise Operations**: Since CHIP-8 relies heavily on bitwise operations for opcode handling and graphics rendering, these concepts are fundamental to the project's execution.

## Challenges and Solutions
- **Opcode Decoding**: Since CHIP-8 instructions are packed into 16-bit opcodes, decoding and interpreting the various instruction formats required careful bitwise manipulation.
- **Timing**: Ensuring accurate timing for game logic, display refresh, and sound was critical for faithful emulation. This was achieved by synchronizing the emulator's update cycle with a 60Hz clock.

## Conclusion
The CHIP-8 Emulator project showcases fundamental concepts in emulator development, such as opcode interpretation, memory management, and hardware emulation (input, graphics, sound). Through the use of the **Interpreter** and **Singleton** design patterns, the emulator is both extendable and manageable, providing a solid foundation for further enhancement or porting to other systems.

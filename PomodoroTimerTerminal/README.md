# Pomodoro Timer for Embedded Linux
A terminal-based Pomodoro timer application designed to improve your productivity using the Pomodoro Technique. This project utilizes a Raspberry Pi 3 B+ and a 5V buzzer.

## Introduction
The Pomodoro Technique is a time management method developed by Francesco Cirillo in the late 1980s. 
The technique uses a timer to break down work into intervals, traditionally 25 minutes in length, separated by short breaks.

## Getting Started

### Prerequisites

- Raspberry Pi 3 B+ (or similar model)
- 5V buzzer
- Linux OS (raspbian)

1. Clone this repository to your Raspberry Pi.
```bash
   git clone https://github.com/prasadmerya/pomodoro.git
```
2. Navigate to the project dir
```bash
   cd pomodoro
```
3. Build the project using CMake. 
source "-S" - CMakeLists.txt pomodoro.c gpio.h 
```bash
  cmake -S . -B ./build
  cd build
  make
```
4. Run the Pomodoro timer application
```bash
   ./POMODOROtimer
```

If  " Permission denied " error occures 
use root login or run sudo

```bash
   sudo ./POMODOROtimer
```

# Configuration
GPIO Pin Configuration: You can configure the GPIO pin used for the buzzer by modifying the gpio.h file.

## About
This is a simple game engine that was built to run bare-metal on a Raspberry Pi 3.
Using the Raspberry Pi's UART hardware, the games can be played through a serial terminal, and create colored text graphics with ANSI codes. 

The engine was architected with platform-specific details (timer, terminal) abstracted out so it could also
be implemented and compiled for desktop, which is easier to test and debug.
The platform-specific dependencies are injected in [`main.c`](source/main.c) based on compiler flags.

## Demo
A menu and two games are included as examples, controlled using the WASD and Space keys.

<details>
  <summary><b>Menu</b> (Epilepsy warning: has cycling colors)</summary>
  <img alt="Menu" src="images/game-menu.gif" />
</details>

<details>
  <summary><b>Snake</b></summary>
  <img alt="Snake" src="images/game-snake.gif" />
</details>

<details>
  <summary><b>Tic-Tac-Toe</b></summary>
  <img alt="Tic-Tac-Toe" src="images/game-tic-tac-toe.gif" />
</details>

## Design

<details>
  <summary>Architecture Diagram</summary>
  <img alt="Architecture Diagram" src="images/diagram-architecture.png" />
</details>

<details>
  <summary>Sequence Diagram</summary>
  <img alt="Sequence Diagram" src="images/diagram-sequence.png" />
</details>

## Building

Building can be done with `make raspi3`, or `make gcc` for desktop. Making raspi3 requires the Linaro arm-none-eabi-g++ cross compilation toolchain.

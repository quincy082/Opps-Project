# Proj_3

### Group Name: Pixels

<br>

### Student 1: Dia Pitroda  
### Student ID: 202404009  

<br>

### Student 2: Vadi Quincy Hiren  
### Student ID: 202401488  

<br>

### Student 3: Sania Debbarma  
### Student ID: 202404037  

<br>

# Multiplayer LAN Carrom Game – C & OpenGL Implementation

## Table of Contents
- [Overview](#overview)
- [Modules](#modules)
- [Execution Flow](#execution-flow)
- [Architecture & Analysis](#architecture--analysis)
- [How to Build and Run](#how-to-build-and-run)
- [Contribution Suggestions](#contribution-suggestions)
- [License](#license)

## Overview
This project is a real-time, LAN-based multiplayer **Carrom** game built using **C** and **OpenGL**, with networking handled via **TCP sockets**.

It supports:
- 2-player LAN mode  
- 2-player mode with AI  
- 4-player mode using separate clients

<br>

## Modules

- `main.c`: Initializes OpenGL and selects game mode  
- `car_client2p.c`: 2-player LAN client logic  
- `car_client2p_ai.c`: 2-player client with AI  
- `car_client4p1.c`, `car_client4p2.c`, `car_client4p3.c`: 4-player clients  
- `serv_include/`: Server logic for player syncing and game state broadcasting  
- `Makefile`: Automates the compilation of modules

<br>

## Execution Flow

1. Start the server; it begins listening for client connections  
2. Clients connect using server’s IP and port; player IDs are assigned  
3. Game state is initialized (striker, coins, scores)  
4. Server coordinates turn-based actions  
5. Clients send move data to the server  
6. Server validates moves and broadcasts updated state  
7. Game continues until a player wins

<br>

## Architecture & Analysis

### Approaches Used

- **TCP Sockets**: Ensures reliable message delivery  
- **OpenGL**: Handles 2D rendering for the board and objects  
- **Client Split Logic**: Each gameplay mode has a separate client  
- **AI Mode**: AI logic is embedded in a dedicated client

<br>

### Key Data Structures

- `struct point`: Represents a 2D coordinate (x, y)  
- `char buffer[1024]`: For serializing and sharing game states  
- `int turn, player_id`: Controls turns and player management  
- `coin_x[10], coin_y[10]`: Arrays representing coin positions

<br>

### Trade-offs Made

| Design Choice                  | Advantages                             | Drawbacks                                 |
|-------------------------------|----------------------------------------|-------------------------------------------|
| Separate clients (4-player)   | Easier role management and debugging   | Redundant code, not scalable              |
| TCP Protocol                  | Reliable and ordered communication     | Slightly more latency and setup overhead  |
| Direct OpenGL use             | Lightweight, minimal dependencies      | Limited UI/UX capabilities                |
| Hardcoded AI                  | Quick to integrate, no API needed      | Not reusable, lacks learning capability   |

<br>

## How to Build and Run

### Prerequisites

- Linux or macOS  
- GCC compiler  
- OpenGL + GLUT (`freeglut3-dev` on Ubuntu)

<br>

### Build Instructions

```bash
sudo apt install freeglut3-dev
make

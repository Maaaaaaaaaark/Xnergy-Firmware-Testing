# Xnergy-General Firmware Testing
> This repository is a submission for **Question 1: Communication System Design**.

This project implements a lightweight communication protocol between **multiple mobile robots (MCU A)** and **fixed charging stations (MCU B)** using **IEEE 802.15.4 RF modules**. The system simulates a dynamic robot charging environment with reliable handshaking and real-time data exchange under timing constraints.




## Directory Structure

```plaintext
├── docs/                        # Design documents & diagrams
│   ├── Communication System Design Document.md
│   └── DFD and Message Flows.pdf
│
├── include/                    # Header files (.h)
│   ├── protocol.h              # Common message format definitions (payloads, headers)
│   ├── rf_comm.h               # RF communication abstraction layer
│   ├── session.h               # Session state machine & tracking
│   ├── robot_app.h             # Robot logic (charging flow, scanning, session)
│   └── station_app.h           # Station logic (handling scan/connect requests)
│
├── src/                        # Source files (.c) – core implementation
│   ├── protocol.c              # Message construction/parsing logic
│   ├── rf_comm.c               # RF layer send/receive logic (stubbed for simulation)
│   ├── session.c               # Session FSM: handshake, retry, timeouts
│   ├── robot_app.c             # Robot behaviors & session maintenance
│   └── station_app.c           # Station-side message handling
│
├── main/                       # Entry points for simulation
│   ├── main_robot.c            # Robot device main loop
│   └── main_station.c          # Station device main loop
│
└── README.md                   # This file

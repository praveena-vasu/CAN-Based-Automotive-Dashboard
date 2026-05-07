# 🚗CAN-Based-Automotive-Dashboard

📜Description

The CAN-Based Automotive Dashboard is an Embedded C application designed to display real-time vehicle parameters such as speed, RPM, gear position, and indicator status using CAN communication. The project enables data exchange between multiple ECUs over a two-wire CAN bus and displays the received information on a CLCD.

This project mainly works using the CAN protocol for reliable real-time communication between embedded systems in automotive applications.

🔷Features

  - Display Real-Time Vehicle Parameters

  - CAN Communication Between Multiple ECUs

  - Display Speed, RPM, Gear & Indicator Status

  - CAN ID-Based Message Filtering

  - Real-Time Data Processing

  - CLCD Interface for Dashboard Display

⚙️Technologies Used

  - Embedded C

  - CAN Protocol

  - MCP2515 CAN Controller

  - TJA1050 CAN Transceiver

  - Microcontroller (PIC/STM32)

  - CLCD Interfacing

  - UART Debugging

  - Interrupt Handling

📍Validation

  - Validates CAN message IDs before processing.

  - Handles invalid or corrupted CAN frames.

  - Ensures proper synchronization between transmission and reception.

  - Maintains stable real-time display updates without communication loss.

▶️How to Run

    Compile the Embedded C project using MPLAB / STM32CubeIDE
    Flash the code into the microcontroller
    Connect CAN controller and transceiver hardware
    Power ON the system to monitor vehicle parameters

🔶Displayed Parameters

    Speed      : 60 km/h
    RPM        : 3000
    Gear       : G3
    Indicator  : LEFT

👩‍💻Author : Praveena

Distributed ICU Patient Monitoring System

1. Project Overview

The Distributed ICU Patient Monitoring System is designed to monitor important patient health and environmental parameters in an Intensive Care Unit (ICU).

The system uses multiple sensor nodes to collect patient-related data such as temperature, light intensity and oxygen level. The collected data is transmitted from Node A to Node B using CAN (Controller Area Network) communication.

Node B is connected to a computer server through UART communication, where the received patient information is displayed for monitoring.

2. Objectives

- To monitor patient health parameters continuously.
- To collect sensor data using distributed nodes.
- To transfer data reliably using CAN communication.
- To display patient information on a computer server.
- To reduce manual monitoring efforts.
- To improve data security using local server storage.

3. Hardware Requirements

- LPC2129 Microcontroller (if used in the implementation)
- Temperature Sensor
- LDR Sensor
- Oxygen Sensor
- CAN Transceiver
- UART Interface
- Computer / Server
- Power Supply
- Connecting Wires

4. Software Requirements

- Embedded C
- Keil uVision IDE
- Flash Magic
- Serial Terminal
- CAN Communication
- UART Communication

5. Block Diagram Description

The project consists of two main nodes.

Node A – Sensor Node

Node A collects sensor readings from:

- Temperature Sensor
- LDR Sensor
- Oxygen Sensor

The collected data is processed and transmitted to Node B through the CAN interface.

Node B – Server Node

Node B receives the sensor data through CAN communication and forwards the information to the computer server using UART communication.

Computer Server

The computer receives and displays the patient monitoring information, including temperature, light intensity and oxygen level.

6. Communication Protocols

CAN (Controller Area Network):
Used for communication between Node A and Node B. It provides reliable data communication between distributed nodes.

UART (Universal Asynchronous Receiver Transmitter):
Used for transferring the received patient information from Node B to the computer server.

7. Working Principle

1. Sensors connected to Node A collect patient monitoring data.
2. The microcontroller reads the sensor values.
3. Sensor data is transmitted to Node B through CAN communication.
4. Node B receives the transmitted information.
5. The received data is sent to the computer through UART.
6. The computer displays the patient monitoring parameters.

8. Advantages

- Continuous patient monitoring.
- Reliable communication between distributed nodes.
- Reduced manual monitoring.
- Local data storage and improved control over patient information.
- Easy integration of multiple sensors.
- Real-time data transmission.

9. Applications

- Intensive Care Units (ICU).
- Hospitals.
- Patient monitoring systems.
- Healthcare monitoring equipment.
- Medical research facilities.

10. Conclusion

The Distributed ICU Patient Monitoring System provides a distributed approach to monitoring patient-related parameters. By combining sensor interfacing, CAN communication and UART communication, the system collects and transfers monitoring data to a central computer server. It helps improve monitoring efficiency and provides better control over patient information.

11. Future Enhancements

- Add heart rate and blood pressure monitoring.
- Implement wireless monitoring.
- Develop a graphical user interface.
- Add patient data logging and history.
- Implement alert notifications for abnormal readings.
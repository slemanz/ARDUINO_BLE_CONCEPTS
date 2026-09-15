# Tinyusb Examples

This repo will use TinyUSB v0.21.0 and STM32F411 (Blackpill Weact).

## Concepts

The most important concepts about USB are:

- **Host and device:** the PC is generally the host and is in charge of
everything, the device only responds.

- **Enumeration:** when you plug the device in the cable, the PC asks "who are
you?" and the device answers with descriptors.

- **Descriptors:** byte tables that describe the device, like:
    - VID/PID (vendor and product IDs)
    - How many interfaces it has
    - Which class each interface belongs to
    - Which endpoints it uses
    
**Note:** with tinyusb the descriptors are written with the help of ready-made
*macros.

- **Endpoints:** the data "channels", Endpoint - is the control endpoint (used
for enumeration), the others are numbered and have a direction:
    - IN (device to PC, e.g. 0x81)
    - OUT (PC to device, e.g. 0x02)

- **Classes:** standardized protocols that the operation system already
understands, without custom drivers. A virtual serial port is the **CDC-ACM**
class. It uses two interfaces: a control interface with a notification endpoint,
and a data interface with one IN and one OUT endpoint. Tinyusb generates all of
this with a single macro. Windows 10+, Linux and macOS support CDC natively, so
the board shows up as COMx or /dev/ttyACM0, with no driver installation.

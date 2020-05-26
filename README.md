# esp32_ble_simple_advertise
# Overview
Minimal esp-idf BLE advertise example for ESP32.<br>
This program periodically advertises short data to central devices.<br>
You will find the last byte of the packet is updated every 2 seconds.

# Usage
## Build project
```bash
git clone https://github.com/UsukeO235/esp32_ble_simple_advertise.git
cd esp32_ble_simple_advertise
. $HOME/esp/esp-idf/export.sh
idf.py set-target esp32
idf.py build
```
## Flash program
```bash
idf.py -p /dev/ttyUSB0 flash
```
/dev/ttyUSB0 is a port to where you connect your ESP32 board.
## Launch monitor
```bash
idf.py monitor
```

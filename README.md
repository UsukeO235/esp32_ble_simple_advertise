# esp32_ble_simple_advertise
Minimal esp-idf BLE advertise example for ESP32

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

Overview
==

This is my attempt at bringing support for sqfmi wathcy board into zephyr as a standalone module. It includes bsp as well as a driver for the eink display.

## Build instructions
```
cd ~/zephyrproject
west build -b watchy/esp32s3/procpu ~/zephyrproject/zephyr/samples/hello_world -p auto -DEXTRA_ZEPHYR_MODULES=<path_to_module_clone>
```
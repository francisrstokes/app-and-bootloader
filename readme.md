# App and Bootloader with libopencm3

This is a minimal experiment to get a little bootloader + app firmware up and running for an STM32 Cortex-M4 chip (STM32F401RE).

| Area             | Size   | Start Address |
|------------------|--------|---------------|
| Bootloader       | 32KiB  | 0x0800_0000   |
| Main Application | 480KiB | 0x0800_8000   |

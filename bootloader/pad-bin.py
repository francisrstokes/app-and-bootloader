#!/usr/bin/env python

import os

BOOTLOADER_FILE = "bootloader.bin"
TARGET_SIZE = 0x8000

size = os.stat(BOOTLOADER_FILE).st_size

if size > TARGET_SIZE:
    raise RuntimeError("Bootloader larger than maximum size")

if size < TARGET_SIZE:
    diff = TARGET_SIZE - size
    with open(BOOTLOADER_FILE, "ab") as f:
        f.write(bytearray([0xFF for _ in range(diff)]))


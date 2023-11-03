#!/usr/bin/bash
if [ -f "F1C100S_BOOT.bin" ]; then
    ./tools/download/sunxi-fel.exe -p spiflash-write 0x0 ./F1C100S_BOOT.bin
else
    echo "F1C100S_BOOT.bin Not Found"
fi
if [ -f "F1C100S_PRO.bin" ]; then
    ./tools/download/sunxi-fel.exe -p spiflash-write 0x10000 ./F1C100S_PRO.bin
else
    echo "F1C100S_PRO.bin Not Found"
fi
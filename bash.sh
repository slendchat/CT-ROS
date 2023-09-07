#!/bin/bash
sudo mount /dev/sdc1 ~/mnt/fdrv
echo "[mount kernel]"
make
sudo cp ~/Documents/PROJECT_STROS/CT-ROS/kernel8.img ~/mnt/fdrv/kernel8.img
echo "[copy kernel to sdcard]"
sudo umount ~/mnt/fdrv
echo "[umount kernel]"
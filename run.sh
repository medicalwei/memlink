#!/bin/bash
QEMU_PATH=~/Documents/qemu/x86_64-softmmu/qemu-system-x86_64
IMG_PATH=~/Documents/qemu-img/test-linux.img

$QEMU_PATH \
  -enable-kvm \
  -device virtio-memlink-pci \
  $IMG_PATH
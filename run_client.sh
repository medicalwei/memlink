#!/bin/bash
MODULE_DIR=$PWD/linux
AP_DIR=$PWD/ap

{
  cd $MODULE_DIR
  make run
}

{
  cd $AP_DIR
  make run
}

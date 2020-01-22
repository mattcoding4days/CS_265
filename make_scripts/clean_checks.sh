#!/bin/bash

# source our environment vars, 

# need to source with full path since makefile will be calling it
source make_scripts/grader_vars.sh
echo

if [[ -d "$GRADER_OBJ" ]]; then
  echo "Removing Object Files Direcory"
  rm -rf "$GRADER_OBJ"
fi

# check if debug object directory exits
if [[ -d "$GRADER_OBJD" ]]; then
  echo "Removing Object Files Debug Direcory"
  rm -rf "$GRADER_OBJD"
fi

# check if binary directory exits
if [[ -d "$GRADER_BIN" ]]; then
  echo "Removing Binary Direcory"
  rm -rf "$GRADER_BIN"
fi

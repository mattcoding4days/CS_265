#!/bin/bash

# source our environment vars, 

# need to source with full path since makefile will be calling it
source make_scripts/grader_vars.sh

if [[ -d "$GRADER_OBJ" ]]; then
  printf "Removing Object Files Direcory\n"
  rm -rf "$GRADER_OBJ"
else
  printf "Nothing to do for ==> %s\n" "$GRADER_OBJ"
fi

# check if debug object directory exits
if [[ -d "$GRADER_OBJD" ]]; then
  printf "Removing Object Files Debug Direcory\n"
  rm -rf "$GRADER_OBJD"
else
  printf "Nothing to do for ==> %s\n" "$GRADER_OBJD"
fi

# check if binary directory exits
if [[ -d "$GRADER_BIN" ]]; then
  printf "Removing Binary Direcory\n"
  rm -rf "$GRADER_BIN"
else
  printf "Nothing to do for ==> %s\n" "$GRADER_BIN"
fi

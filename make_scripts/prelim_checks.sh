#!/bin/bash

# This is a helper build script for the root project makefile
# A build rule will only be triggered if the script is called with
# either '-r' for release or '-d' for debug

# since the root makefile will be calling the scripts
# the path must be sourced from the makefiles position
# in the hiearchy 
# NOTE: eg: makefile -> make_scripts/prelim_checks.sh

source make_scripts/grader_vars.sh


function trigger_release() {
  # check if object directory exists
  if [[ ! -d "$GRADER_OBJ" ]]; then
    printf "Creating Object Files Directory\n"
    mkdir "$GRADER_OBJ"
  fi

  # check if binary directory exits
  trigger_binary
}


function trigger_debug() {
  # check if debug object directory exits
  if [[ ! -d "$GRADER_OBJD" ]]; then
    printf "Creating Object Debug Files Directory\n"
    mkdir "$GRADER_OBJD"
  fi

  # check if binary directory exits
  trigger_binary
}


function trigger_binary() {
  # build the binary directory
  if [[ ! -d "$GRADER_BIN" ]]; then
    printf "Creating Binary Directory\n"
    mkdir "$GRADER_BIN"
  fi
}


# entry point
if [[ "$#" -eq 1 ]]; then
  for arg; do
    if [[ "$arg" == "-r" ]]; then
      trigger_release
    elif [[ "$arg" == "-d" ]]; then
      trigger_debug
    else
      printf "%s accepts only one Argument:\n -r : release\n-d : debug\n" "$0"
    fi
  done
fi

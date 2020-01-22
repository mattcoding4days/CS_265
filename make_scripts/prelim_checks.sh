#!/bin/bash
# This is a helper build script for the root project makefile
# A build rule will only be triggered if the script is called with
# either 'release' or 'debug'


source make_scripts/grader_vars.sh


function trigger_release() {
  # check if object directory exists
  if [[ ! -d "$GRADER_OBJ" ]]; then
    echo "Creating Object Files Directory"
    mkdir "$GRADER_OBJ"
  fi

  # check if binary directory exits
  if [[ ! -d "$GRADER_BIN" ]]; then
    echo "Creating Binary Directory"
    mkdir "$GRADER_BIN"
  fi
}


function trigger_debug() {
  # check if debug object directory exits
  if [[ ! -d "$GRADER_OBJD" ]]; then
    echo "Creating Object Debug Files Directory"
    mkdir "$GRADER_OBJD"
  fi

  # check if binary directory exits
  if [[ ! -d "$GRADER_BIN" ]]; then
    echo "Creating Binary Directory"
    mkdir "$GRADER_BIN"
  fi
}


# entry point
if [[ "$#" -eq 1 ]]; then
  echo
  for arg; do
    if [[ "$arg" == "release" ]]; then
      trigger_release
    elif [[ "$arg" == "debug" ]]; then
      trigger_debug
    else
      echo "Accepts only one Argument: release or debug"
    fi
  done
fi

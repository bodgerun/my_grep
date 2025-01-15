#!/bin/bash

reset=$'\033[0;m'
grey=$'\033[2;37m'
red=$'\033[0;31m'
green=$'\033[0;32m'

__border__ () {
  echo -n $grey
  echo "----------------------------------------------------------------"
  echo -n $reset
}

__header__ () {
  __border__
  echo
  echo $grey"   TEST: $1"$reset
  echo
  __border__
}

__footer__ () {
  [ $1 -eq 0 ] && color=$green || color=$red
  __border__
  echo
  echo $color"   IN TOTAL: $1 fails"$reset
  echo
  __border__
}

__echo_result__ () {
  if [ $1 -eq 0 ]; then
    echo $green"   OK!"$reset
  else
    echo $red"   FAILS: $1"$reset
  fi   
}

__process_result__ () {
  (( fails+=$1 ))
  __echo_result__ $1
}

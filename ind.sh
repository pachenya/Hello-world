#!/bin/sh
if [ $# -eq 1 ]; then
  echo "indenting $1"
  indent $1 -ts2 -bli0 -cli0 -nut
else
  echo "file name?"
fi


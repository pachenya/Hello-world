#!/bin/sh
if [ $# -eq 1 ]; then
  echo "indenting $1"
  indent $1 -ts2 -bli0 -cli0
else
  echo "file name?"
fi


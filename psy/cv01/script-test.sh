#!/usr/bin/env bash
echo "Hello, World!"

echo "NUMBER OF ARGUMENTS: $#"
I=0
while [ $# -gt 0 ]; do
  let I++
  echo "ARGUMENT $I: '$1'"
  shift
done

#!/bin/bash

if [ $# -lt 2 ]; then
    echo "Usage: $0 <file_name> <command>"
    exit 1
fi

file_name="$1"
shift 1 # Shift twice to remove the first and second arguments

# inotifywait -e close_write,moved_to,create -m . |
inotifywait -e close_write -m . |
while read -r directory events filename; do
  if [ "$filename" = "$file_name" ]; then
    eval "$@"
    echo "----------------------------------------------------------------"
  fi
done

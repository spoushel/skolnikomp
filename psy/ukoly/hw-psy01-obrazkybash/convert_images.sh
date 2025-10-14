#!/bin/bash

error=0

for extension in jpg jpeg tif tiff; do
    for name in *."$extension"; do
        if [ -f "$name" ]; then
            basename="${name%.*}"
            if convert "$name" "$basename.png" 2>/dev/null; then
                continue
            else
                echo "Nelze vytvorit soubor $basename.png" >&2
                error=1
            fi
        fi
    done
done

if [ $error -eq 1 ]; then
    exit 1
else
    exit 0
fi
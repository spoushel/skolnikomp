#!/bin/bash

for extension in jpg jpeg tif tiff; do
    for name in *."$extension"; do
        if [ -f "$name" ]; then
            basename="${name%.*}"
            if convert "$name" "$basename.png" 2>/dev/null; then
                echo "vytvoreno $name"
                continue
            else
                echo "Nelze vytvorit soubor $name" >&2
                exit 1
            fi
        fi
    done
done

exit 0
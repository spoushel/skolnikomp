#!/bin/bash

d=false
t=false
z=false

while getopts "dtz" opt; do
    case $opt in
        d) d=true ;;
        t) t=true ;;
        z) z=true ;;
        \?) exit 3 ;;
    esac
done
shift $((OPTIND-1))

dir="${1}"
archive="${2}"

if [ $# -ne 2 ]; then
    exit 3
fi
[ -f "$archive" ] || exit 3
[ -d "$dir" ] && [ -r "$dir" ] || exit 3

temp_dir=$(mktemp -d) || { echo "Nelze vytvořit dočasný adresář" >&2; exit 2; }
tar -xzf "$archive" -C "$temp_dir" || { echo "Nelze rozbalit archiv" >&2; rm -rf "$temp_dir"; exit 3; }

if [ "$t" = true ] && [ "$d" = true ]; then
    exit 3
fi
if [ "$t" = false ] && [ "$d" = false ]; then
    exit 3
fi

if [ "$z" = true ]; then
    new_files="/tmp/new_files_$$"
    > "$new_files"
    
    number=0
    while [ -f "rozdil_$(printf '%03d' $number).tgz" ]; do
        number=$((number + 1))
        if [ $number -ge 1000 ]; then
            echo "Nelze vytvořit soubor rozdil_XXX.tgz" >&2
            rm -rf "$temp_dir"
            exit 2
        fi
    done
    new_archive="rozdil_$(printf '%03d' $number).tgz"
fi

error_file="/tmp/error_$$"

if [ "$d" = true ]; then
    find "$dir" -type f | while read local_file; do
        relative_path=${local_file#"$dir"/}       
        if [ ! -r "$local_file" ]; then
            echo "Nelze zkontrolovat soubor $relative_path" >&2
            touch "$error_file"
            continue
        fi
        
        archive_file="$temp_dir/$relative_path"
        
        if [ -f "$archive_file" ]; then
            if [ ! -r "$archive_file" ]; then
                echo "Nelze zkontrolovat soubor $relative_path" >&2
                touch "$error_file"
                echo "$relative_path"
                if [ "$z" = true ]; then
                    echo "$relative_path" >> "$new_files"
                fi
            elif ! diff -q "$local_file" "$archive_file" > /dev/null; then
                echo "$relative_path"
                if [ "$z" = true ]; then
                    echo "$relative_path" >> "$new_files"
                fi
            fi
        else
            echo "$relative_path"
            if [ "$z" = true ]; then
                echo "$relative_path" >> "$new_files"
            fi
        fi
    done
fi

if [ "$t" = true ]; then
    find "$dir" -type f | while read local_file; do
        relative_path=${local_file#"$dir"/}
        
        if [ ! -r "$local_file" ]; then
            echo "Nelze zkontrolovat soubor $relative_path" >&2
            touch "$error_file"
            continue
        fi
        
        archive_file="$temp_dir/$relative_path"
        
        if [ -f "$archive_file" ]; then
            if [ ! -r "$archive_file" ]; then
                echo "Nelze zkontrolovat soubor $relative_path" >&2
                touch "$error_file"
                echo "$relative_path"
                if [ "$z" = true ]; then
                    echo "$relative_path" >> "$new_files"
                fi
            elif [ "$local_file" -nt "$archive_file" ]; then
                echo "$relative_path"
                if [ "$z" = true ]; then
                    echo "$relative_path" >> "$new_files"
                fi
            fi
        else
            echo "$relative_path"
            if [ "$z" = true ]; then
                echo "$relative_path" >> "$new_files"
            fi
        fi
    done
fi

if [ "$z" = true ]; then
    if [ -s "$new_files" ]; then
        tar -czf "$new_archive" -C "$dir" --files-from="$new_files" 2>/dev/null || { echo "Nelze vytvořit soubor $new_archive" >&2; rm -rf "$temp_dir"; exit 2; }
    else
        tar -czf "$new_archive" --files-from /dev/null 2>/dev/null || { echo "Nelze vytvořit soubor $new_archive" >&2; rm -rf "$temp_dir"; exit 2; }
    fi
    rm -f "$new_files"
fi

rm -rf "$temp_dir"

if [ -f "$error_file" ]; then
    rm -f "$error_file"
    exit 1
fi
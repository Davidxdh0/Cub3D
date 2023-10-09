#!/bin/bash

# Directory containing the files to execute
directory="maps/valid"

# List all files in the directory
files=("$directory"/*)

# Iterate through the files and execute them
for file in "${files[@]}"; do
    if [ -f "$file" ]; then
        # Print the file name and execute it with ./cub3d
        echo "Executing $file"
        # valgrind --leak-check=full --show-leak-kinds=definite --track-origins=yes ./cub3d $file
		./cub3d $file
        # Wait for the user to press the "Escape" key to continue
        echo "Press any key to continue..."
        read -s -n 1 key

        # Check if the key is Escape (ASCII value 27)
        if [ "$key" == $'\e' ]; then
            continue
        else
            echo "Exiting..."
			break ;
        fi
		sleep 10
    fi
done

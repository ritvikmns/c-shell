
# Shell in C


# Description


1. Prompt Shows the username, system name and the current working directory relative to home (~).

2. Warp changes the cwd (sequentially if multiple inputs are given) and accepts both relative and absolute paths.

3. Creates background process by using the token '&'(command before this runs in background). Also, prints the process ID of the created process.

4. Peek lists out all the files/directories in the given path. It gives more info with "-l" flag and shows the hidden files using the "-a" flag.

5. Proclore lists out the information of given process ID.

6. It also shows run normal shell commands and gives out the output.

7. Pastevents is used to view the last 15 commands and also run any of those given the index.

8. Seek is used find files/directories with given filename(without extension) in the given directory tree and prints out the paths. It also prints out the file contents and change the cwd if only one path is found (only happen if we give the "-e" flag).


# Assumptions

1. Max Len of Path = Max Len of Command = 4096 characters.

2. No Spaces in paths or filenames.

3. Warp - on a just launched terminal will remain in home.

4. Max Len of filename/directory names = 256 characters

5. Max Num of Background processes = 1000

6. Lexicographic order is case-insensitive




*This project has been created as part of the 42 curriculum by cdahlhof.*

# ft_ls

## Description

the ls command is used to list contents of a directory, by default the current one

## What the Program Does

list the contents of the named directories or the current one, also implementing the following flags:

 - -a include the hidden files in the listing
 - -l express additional information about the content, like age and permissions
 - -r reverse the order of the listed output
 - -t sort by time instead
 - -R recursively list the content of the given folders

## Instructions

- To build the project, run

```sh
make
```

this will update the required subrepositories and compile the executable

- To run the program, use


```sh
./ft_ls
```

with any of the above mentioned flags.

the order of arguments can be varied, like in the original ls function any flags independend of location are applied to any given directories

### Technical notes

the original function ls has some reliance on the localisation settings of the OS, wherein depending on the locals (specifically LC_COLLATE) the order of output is sorted in different ways. depending on the state of that variable the output orders case sensitive or not (ABCabc or AaBbCc).

Due to the limitations the subject sets on what commands we can use for our implementation this behaviour is not replicated in ft_ls

### Utils

https://wiki.ubuntuusers.de/ls/

### execution notes

the subject noted that it is strongly advised to implement the recursive behaviour from the very beginning.
the only part to really take care of there i believe is the order of output, which is why i need to initially go over the directories and sort them, before listing their contents too. thus i iterate over all given (or the default) first and store the paths of the subdirectories, then sort recursively and then print the output recursively



# file-manager-cpp
A mini-project file manager built on Operating Systems lab module(s) 6, 10 and 11. A project that aimed at applying the learnt knowledge of operating systems to devise a file managing command line interface that can carry out file management operations like most modern operating systems.

## Getting started
1. To get started all you have to do is fork, and then clone the forked repository on to your machine.
2. Once that is done, create your own branch, preferrably name it as v2.12 or something. then type ```git checkout <new-branch-name>``` to move to the new branch you just created.
3. Once done, head on over to the file ```tests/test_cli.cpp``` and run the code.
4. Type the command ```help``` to get a list of all available commands.
5. To explore certain command's syntax type ```help <command-name>``` from the list of commands.

## Helping the developers
Test out each and every combination of commands possible, and when you find a bug, create an issue on this repo. We will try to fix the issue. Keep updating your forks before continuing further work.

## Developing on the project
They key issue that this project has is its multi-thread command ```nscript```, that runs multiple thread instances of the script files on the same command line.
### Intent of the feature
The intent of this feature was to allow multiple command line interfaces to work on the same resource pool, that is, the memory structure, the file system and use locks which are already in place, to make sure the entry of the data into the memory is not flawed.


## Devleoping on the project
Please fork the entire repository, but work on your own branches creted from ```v2.1``` on your forks on your devices, and publish a pull request. Contributors helping to make this project better will be thanked :)
### Optional: Rewriting the Codebase
Optionally, if you find the file structure improvable, or you do not like the codebase at all, a rewrite will be welcome. Make sure it is as modular as possible.

Each and every contribution, that is or isn't merged is appreciated by the both of us :)

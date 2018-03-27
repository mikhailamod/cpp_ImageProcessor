Mikhail Amod
AMDMIK002
CSC3022H Assignment 2

To compile: run the 'make' command
To run: cd into bin folder and execute volImage with appropiate parameters
Executable file located in bin folder

How program runs:
The program uses the imageBaseName to locate the .data file and all .raw files.
e.g. if imageBaseName == MRI, it will search in the lib/MRI/ folder for MRI.data file
and for all MRI[num].raw files.

Operations include: -d (diff map), -x(extract) and -g(row extract, the extra credit option)
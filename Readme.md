# Grader is a project for my fall semester 2019 Software Engineering course [CSCI 265] Prof Dave Wessels


* It is a simple command line program written in C++ with the following features:
    - Calculate a consolidate grades for as many given students in a text based config file with Specific Evaluation data
    - Capable of searching for one student if specified by the '-s' flag
    - Can handle a considerable amount of different errors with out crashing and still calculating lines that are not corrupted
    - Ignores any text following a '#' as a comment
    - Ignores white space and tabs
    - Can detect if a student Withdrew from the course if a 'WDR' [in any case] is found in data
    - Can detect if a student came with in 0.5% of a higher letter grade

## To test the program run the following commands [make install option to be added in the future]


```bash
# There are 3 ways to run the makefile

# Only build the release version
make release

# Build only debug version
make debug

# make all
make

# standard.txt is a test case with no errors
./bin/grader test_files/standard.txt

# search for one student
./bin/grader -s tob test_files/standard.txt

# when your done clean up
make clean

```

## The project was turned in with hand-written documentation and bash scripts to automate testing

* The above parts of the project are being changed for my own interest in learning
    - Python scripts to automate the generation of C++ code documentation based on .hpp files
    - Python testing scripts are currently being written to replace the old bash scripts because Python > Bash


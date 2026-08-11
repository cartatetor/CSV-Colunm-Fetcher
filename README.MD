# CSV File Column Fetcher

- gets specified column from specified file
- puts column in specified output file on seporate lines
- Oringonally writton to get album names from csv file with album name being third entry.
- returns 1 on full program exucution
- returns negitive on failure

## Building:

Currently only tested on linux

### Linux (should work on any distro):

- ./BUILD.bash
- OR
- g++ CSV_Column_Fetch.cpp -o Your_Desired_Name

### Windows:

- Program is untested

### Mac/OSx:

- Program is untested

### OpenBSD/BSD:

- Program is untested

## Command Options:

of - The Output File. The default is 'OutFile.txt'

- of=out\ file.tx

if - The Input File

- if=in\ file.txt

column - which column number to pull from

- column=3

delim - The column seporator/What seporates the column. The default is ','

- delim=:

Example:

- FetchCSVColumn if=SomeInput\ File.csv of=output delim=; column=6

## Notes

- No "Quietness leval" added yet
- Currently does not check is the total number of columns to less than the Column Number to pull from
- Overwites output file

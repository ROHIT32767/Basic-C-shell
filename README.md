# Assignment-2
# 2021101113
# Operating Systems and Networks, Monsoon 2022
# creating a user-defined interactive shell program 
# Gowlapalli Rohit

>##### All these commands are tested on Ubuntu Version 20.04.3 LTS (Focal Fossa) 
```
2021101113_Assignment2
├── cd.c
├── cd.h
├── discover.c
├── discover.h
├── echo.c
├── echo.h
├── headers.h
├── history.c
├── history.h
├── history.txt
├── linked_list.c
├── linked_list.h
├── linked_main.c
├── ls.c
├── ls.h
├── main.c
├── makefile
├── pinfo.c
├── pinfo.h
├── process_command.c
├── process_command.h
├── prompt.c
├── prompt.h
├── PWD.c
├── PWD.h
├── README.md
├── sig_handler.c
├── sig_handler.h
├── spec4.c
├── spec4.h
├── str_tok_and.c
└── str_tok_and.h
```

* >Commands to be executed

 `$ make`  
 `$ ./main`
* > Neglect all warnings during execution of make file-they are just errors due to unused variables
<hr>

```

Specification 1: Display requirement


prompt-display format ::  <username@system_name:curr_dir>

Assumptions:

1) It is assumed that
   a) strlen( absolute_path to the home directory of the shell ) <=300
   b) strlen( curr_dir in display prompt ) <=300
   c) strlen( system_name) <= 200
   d) strlen( username) <= 200
   e) strlen( Time taken by foreground process ) <=300
   f) strlen( input ) <=1000
   g) strlen( absolute_path to history.txt) <=625
2) getline() is used to read the input received on displaying the prompt
3) Input is tokenised with following delimiters in order (";","&"," ")


```
```

Specification 2: Builtin commands

execvp or similar commands were not used to implement these commands

Command type : "cd"

a) cd < Directory Path > / <Directory Name>
   i) If the Directory path is valid ,then the working directory is changed to the corresponding Directory Path
   ii) If the Directory Path is invalid , then perror is Displayed
b) cd -
   i)prints the previous working directory and shifts to the previous working directory
   ii)If there is no such previous working directory, "OLDPWD NOT SET" is printed on to the display screen.
c) cd ~ / cd 
  working directory is changed to the home-directory of the shell

Command type : "echo"

echo <arg1> <arg2> ............ <argn>

a) It is assumed that command echo can have any number of arguments
b) echo writes arguments to standard output
c) multi-line strings and environmental variables are not handled

Command type : "pwd"

pwd <arg1> <arg2> ............. <argn>

a) pwd command writes the full pathname of the current working directory to the standard output.

b) As the presence of other arguments doesnt affect processing "pwd" in accordance with Linux-Shell, any number of arguments can be given to pwd

```
```

Specification 3: ls command


"ls" command-lists directory contents
execvp or similar commands were not used to implement these commands

a) ls <Directory Name>/<Directory Path>/<File_name>/<File_path>
   i) If the Diectory path is valid ,then all the contents of the directory entry get displayed onto the screen
   ii) If multiple such directory paths/File paths,all the contents of each directory entry get displayed onto the screen,Directory entries of a Directory are printed after printing the name of the directory
   iii) If the Directory Path is invalid , then perror is Displayed

b) ls -a <Directory Name>/<Directory Path>/<File_name>/<File_path>
do not ignore  directory entries starting with .

c) ls -l 
displays extra information regarding files

d) ls < arguments in (a) > < arguments in (b) > < arguments in (c) >
displayed according to the union of all the printing combinations

e) ls command lists all the directory entries in alphabetical order

f) In ls -l ,if the last-modfied time of a directory and the current_time differ by more than 6 months-then, <month> <day> <Year> unlike <month> <day> <Hours>:<Minutes> in other cases

g) It is assumed that directory name would not contain any spaces

h) colours are assigned for different types of directory entries
    green-executables
    white-files
    blue-directories
```
```

Specification 4: System commands with and without arguments :
Specification 6: Finished Background Processes [5 marks]

Foreground process ->  shell waits for process to complete and regain control when this process exits.

Background process -> shell will spawn that process and doesn't wait for the process to exit

a)If the input is of the form:
<command-1>&<command-2> &... &..&<command-(n-1)>&<command-n>
shell runs all the commands of the form <command-j> where 1<=j<n in the background and <command-n> is run in the foreground.

b) If T=Time taken by the foreground process
 i) If T>=1 ,next prompt: <username@system_name:curr_dir took Ts>
 ii) next prompy: <username@system_name:curr_dir>

c) Background processing for built-in commands is not handled like ls,echo,pwd,pinfo,cd

d)Multiple background processes can be run in the background

e) Whenever a new background process is started, the PID of then newly created background proess is printed on to the display screen

f) If a background process exits,then the shell displays the appropriate message to the user

g) commands like fork(),waitpid(),execvp(),signal() are used in addition to use of a Doubly Linked list to indicate the process-number

h) It is assumed that strlen(any argument) <= 600

```
```
Specification 5: pinfo command

pinfo <pid> - prints the process info of the given pid
pinfo - prints the process-related info of your shell program

a) If /proc/<pid>/stat or /proc/<pid>/exe is unaccesible,then appropriate perror is displayed
b) commands like getpid(),fopen(),fscanf(),fclose(),readlink(,,) are used to implement this command
c) It is assumed that a maximum of 52 entries can be present in /proc/<pid>/stat
d) It is assumed that strlen(/proc/<pid>/stat) <=800 and strlen(/proc/<pid>/exe) <=800 and strlen(buffer written into in readlink)<=500
e) '+' is added to the status code if the process is in the foreground
f) commands like getpid(),fopen(),fscanf(),readlink() are used to implement pinfo
g) If the executable path directs to a path which resides inside the home-directory of the shell,the prefix-path of the homedirectory of the shell is replaced by ~

Display Format of pinfo command:
pid : <pid>
process Status : {R/S/S+/Z}
memory : {<Virtual Memory>}
executable Path : <path>
```
```

Specification 7: Discover command

command format : discover <target_dir> <type_flags> <find_name> (fixed-format) (Total-16 cases) (<type-flags> ∈ {-d,-f})

a) DFS is used along with opendir() and readdir() to implement the discover command
b) scandir command may not be prefered to iterate over the directory entries as scanddir automatically mallocs the name_list thereby causing a possibility of stack_frame to pile-up and give rise to seg_fault
c) perror is displayed if one of the paths redirected to is invalid 
d) Some of the syntax-error cases in discover command are not handled
e) I have not handled cases like discover -df and discover -fd as those cases are not mentioned in the document as its mentioned that -d searches for all directories and -f searches for all files but there is no definition for -df and -fd which are not defined.

```
```
Specification 8: history
command type : history

a) history.txt is used to maintain the last 20 commands executed through the shell
b) history command prints a maximum of the last 10 commands executed through the shell
c) command is not stored in history if it is the exactly same as the previously entered command.
d) empty commands and commands with just whitespace characters are not handled properly
e) oldest commands are overwritten if more than 20 commands are entered
f) The commands are tracked across multiple sessions of shell
g) It is assumed that strlen(command) < 400 to be able to display it in history.txt

```
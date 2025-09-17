1. The current zip file contains a simple shell program that can execute one command.  To compile, input:
  make

Then you can run it:
  ./SimpleShell


2. For Assignment One:
(1) Revise simple-execute.c (that is the only file you need to submit) to implement the functions mentioned in Assignment One. 
    In simple-execute.c, you can define your own functions and add header files if needed. However, you must use "dup()", "pipe()", and "execvp()" to execute the commands.

(2) Your program should be compiled by:
    make

(3) At least, your shell program should be able to correctly execute the following commands:

$$$ ls
$$$ ps
$$$ ps -al
$$$ ls -l | wc -l
$$$ ls -l | grep D | wc -l
$$$ cat Makefile | tail -n 5 | head -n 3 | grep simple

Note: we may use some new test cases when grading.

Submission: You only need to submit simple-execute.c. (please include your group information (names and SIDs by code comments) in this file)

Enjoy coding!!!
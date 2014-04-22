Java program (DefendTheFort.java) must be run from the command line.

The c program, code_protection, from the cuddlebearsCodeProtection.c  and .h
files using the included makefiles.  In imposes a number of restraints. In
addition to length limit it imposes on names it also imposes the following:

-All characters in names must be letters.

-Integer is limited based not only on the size of the integer,
 but also on its ability to cause overflow or underflow during
 addition and subtraction operations.

-The input file must exist.

-Any files usage is limited to the directory that the program is 
 executed in. No global paths or subdomain paths are accepted.

-Filenames must include alphanumeric characters only. 

-An extension is automatically appended to files and is not
 determined through user input.

-Passwords must be between 6 and 24 characters in length.

-Passwords can only be comprised of alphanumeric charactes.
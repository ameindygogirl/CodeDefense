Java program (DefendTheFort.java) must be run from the command line.

Input file MUST be located in the same directory as the .java files.

We defended against:
-Names longer than 50 characters.
-All characters in names must be letters.

-Absolute pathnames
-File formats other than .txt

-Numbers too large to fit in int (2147483648) 
-Numbers too small to fit in int (-2147483649) 

-Passwords aren't visible on screen

____________________________________________________________________________
The c program, code_protection, from the cuddlebearsCodeProtection.c  and .h
files can be compiled using the included makefiles.  

Input file MUST be located in the same directory as the .c file.

We defended against:
-Names longer than 50 characters.
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


The c program contains some commented out code, particularly at the
bottom of the file. This was an incipient openssl pw encryption and
hashing attempt that was abandoned because it was well beyond the
requirements of the assignment and was becoming too time consuming.

A note on using different operating systems:
Several vulnerabilities have surfaced in Windows that did not show
themselves when the program was run in Linux. Most of the ones we
found have been fixed, but one regarding an error with long name
inputs has not. We would be surprised if there are not other such
vulnerabilities which we simply did not discover.
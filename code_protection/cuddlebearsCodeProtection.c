#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include <openssl/evp.h>

#include "cuddlebearsCodeProtection.h"

/* gensalt.c, gensalt.h and their makefile obtained from
 * perfec.to/gensalt */

int main()
{
	char *first_name, *last_name, *in, *out, *temp, line[FILE_LEN];
	FILE *data_file, *infile, *outfile;
	int a, b;
	
	/* open the data file */
	data_file = open_file(DATA_FILE, "rw");
	
	get_name(&first_name, 0);
	get_name(&last_name, 1);
	
	/* get 2 integers from the user */
	a = get_int();
	b = get_int();
	flush();	

	/* get input and output file names from the user */
	get_fname(&in, 0);
	get_fname(&out, 1);

	/* if the filenames are the same, add a 1 to the end of the outfile name */
	if(!strncmp(in, out, min_string_len(in, out))) {
		temp = out;
		out = calloc(strlen(temp)+1, sizeof(char));
		if( out == NULL ) {
			printf("Memory allocation failed\n");
			exit(EXIT_FAILURE);
		}
		out[0] = '\0';
		strcat(out, temp);
		strcat(out, "1");
		free(temp);
	}
	
	/* append the extension to the filenames */
	append_extension(&in);
	append_extension(&out);
	
	/* get the user's pw and store it */
	init_password(data_file);	
	
	/* ask the user for their pw and verify it */
	if(!verify_password(data_file)) {
		printf("Password verification failed. Exiting\n");
		return 0;
	}
	
	fclose(data_file);
	
	/* open input and output files	*/
	infile = open_file(in, "r");
	outfile = open_file(out, "w");	

	fprintf(outfile, "%s\n%s\n", first_name, last_name);
	fprintf(outfile, "%d + %d = %d\n", a, b, a+b);
	fprintf(outfile, "%d * %d = %d\n", a, b, a*b);
	
	/* print the contents of the input file into the output file */
	while( fgets(line, LINE_LEN, infile) ) {
		fprintf(outfile, "%s", line);
	}
	
	/* free memory */
	free(first_name);
	free(last_name);
	free(in);
	free(out);
		
	/* close files	*/
	fclose(infile);
	fclose(outfile);
	/* fclose(data_file); */	
		
	return 0;
} /* end main */

/* open file with the given name in the given mode */
FILE* open_file(char* fname, const char * mode)
{
	FILE* file = fopen(fname, mode);
	
	if(file == NULL) {
		printf("Could not open file %s\n", fname);
		exit(EXIT_FAILURE);
	}
	
	return file;
} /* end open file */

/* get a name from the user */
void get_name(char **name, int lname)
{
	char temp[60];
	*name = NULL;
	
	while( *name == NULL ) {
		if(!lname) {
			printf("Enter your first name: ");
		} else {
			printf("Enter your last name: ");
		}
		if( fgets(temp, NAME_LEN, stdin) != NULL ){
			/* get rid of the newline character */
			if (temp[strlen(temp)-1] == '\n') {
				temp[strlen(temp)-1] = '\0';
			}
		}
		
		if( !valid_name(temp) ) {
			printf("That name input is not valid\n");
		} else {
			/* +1 to null terminate */
			*name = (char*) malloc(sizeof(strlen(temp)+1) * sizeof(char));
			strncpy(*name, temp, strlen(temp));
		}
	}
} /* end get_name */

/* check if the name is valid */
int valid_name(char *name)
{
	int i;
	
	/* name must be at least 2 chars long */
	if(strlen(name) < 2) {
		printf("A single character or less is not a valid name\n");
		return 0;
	}
	
	/* if a every char of the name is not a letter or an 
	 * apostrophe, it is not valid */
	for(i = 0; i < strlen(name)-1; i++){
		if(!isalpha(name[i]) && name[i] != '\'') {
			printf("invalid character in the name\n");
			return 0;
		}
	}
	return 1;
}

/* get an integer from the user */
int get_int()
{
	char check[FILE_LEN];
	int num, is_valid = 0;
	
	/* might need more protection in here */
	while(!is_valid) {
		printf("Enter an integer: ");
		fscanf(stdin, "%s", check);
		
		/* check if the input is valid */
		if(!valid_int(check)) {
			continue;
		}
		
		is_valid = 1;
	}
	
	num = atoi(check);
	
	return num;
}

/* Checks wheter a user's input is a valid integer input */
int valid_int(char* candidate)
{
	long int l;
	int i;
	char temp[2];
	
	/* check if the user input is too long to be an integer */
	if(strlen(candidate) > INT_LEN) {
		printf("The provided integer is too long\n");
		return 0;
	}
	
	/* check that every element of the string is a digit */	
	for( i = 0; i < strlen(candidate); i++ ) {
		temp[0] = candidate[i];
		temp[1] = '\0';
		if( strstr(DIGITS, temp) == NULL && (i !=0 && candidate[i] != '-')) {
			printf("integer must include only digits\n");
			return 0;
		}
	}
		
	/* above verified that the int is short enough to fit in a 
	 * long long int and is comprised of valid digits */
	l = atoi(candidate);

	/* check if the int is larger or smaller than the maximum
	 * or minimum integer value */
	if(l > INT_MAX || l < INT_MIN) {
		printf("The provided integer is out of range\n");
		return 0;
	}
		
	return 1;
}
		
/* get a filename from the user */
void get_fname(char** file, int outfile)
{
	char temp[110];
	*file = NULL;

	/* keep trying to get a filename util the user gives valid input */
	while(*file == NULL) {
		if(!outfile) {
			printf("Enter the name of the input file (without file extension): ");
		} else {
			printf("Enter the name of the output file (without file extension): ");
		}
		
		/* check that the file name was read in properly */		
		if( fgets(temp, FILE_LEN, stdin) == NULL ){
			printf("No file input found\n");
			continue;
		/* check that all chars are alphanumberic */
		}
		
		/* get rid of the newline character */
		if (temp[strlen(temp)-1] == '\n') {
			temp[strlen(temp)-1] = '\0';
		}
		
		if(non_alpha_chars(temp)){
			printf("Invalid characters\n");
			continue;
		/* make sure the file name is not the same as the file that holds data */	
		} else if(!strncmp(temp, "data", 5)) {
			printf("Cannot use that filename\n");
			continue;
		} else {
			/* +1 to null terminate */
			*file = (char*) malloc(sizeof(strlen(temp)+1) * sizeof(char));
			strncpy(*file, temp, strlen(temp));
		}		
	}
}

/* return the length of the shorter of 2 strings */
int min_string_len(char* a, char *b)
{
	if( strlen(a) < strlen(b) ) {
		return strlen(a);
	}
	
	return strlen(b);
}

/* check that all characters in a string are alphanumeric */
int non_alpha_chars(char* s)
{
	int i;	
	for( i = 0; i < strlen(s); i++) {
		
		/* checks if the character is a letter */
		if(!isalnum(s[i])) {
			printf("%c, %d\n", s[i], i);
			return 1;
		}
	}
	return 0;
}

/* append the defined file extension to a filename */
void append_extension(char **s)
{
	char * new_str = (char*) malloc(strlen(*s) + sizeof(char)*(EXT_LEN+1));
	
	if(new_str == NULL) {
		printf("Memory alloc failed\n");
		exit(EXIT_FAILURE);
	}
	
	new_str[0] = '\0';
	strcat(new_str, *s);
	strcat(new_str, EXTENSION);
	
	*s = new_str;
}

void init_password(FILE * data)
{
	char temp[50];
	char *pw;
	int valid_pw = 0;
	
	while(!valid_pw){
		printf("Enter your password (6-24 characters): ");
		fgets(temp, sizeof(temp)/sizeof(char) -1, stdin);
		
		if( strlen(temp) < 6 || strlen(temp) > 24 ) {
			printf("Password not in size range\n");
			continue;
		}  
		
		pw = (char*) malloc((sizeof(strlen(temp))+1)*sizeof(char));
		if( pw == NULL ){
			fprintf(stderr, "Password memory allocation failed\n");
			exit(EXIT_FAILURE);
		}
	
		/* copy the password into its holder */
		strncpy(pw, temp, strlen(temp));
		valid_pw = 1;
	}
	
	while(encrypt_password(&pw, data)){
		fprintf(stderr, "password encryption failed\n");
			continue;
	}
}
	
/* slightly modified from the resposnse by indiv at:
 * http://stackoverflow.com/questions/9488919/openssl-password-to-key */
int encrypt_password(char **pw, FILE * data) 
{
	const EVP_CIPHER *cipher;
    const EVP_MD *dgst = NULL;
    unsigned char key[EVP_MAX_KEY_LENGTH], iv[EVP_MAX_IV_LENGTH];
    unsigned char *password = (unsigned char*) *pw;
    const unsigned char *salt = NULL;
    int i;

    OpenSSL_add_all_algorithms();

    cipher = EVP_get_cipherbyname("aes-256-cbc");
    if(!cipher) { fprintf(stderr, "no such cipher\n"); return 1; }

    dgst=EVP_get_digestbyname("md5");
    if(!dgst) { fprintf(stderr, "no such digest\n"); return 1; }

    if(!EVP_BytesToKey(cipher, dgst, salt,
        (unsigned char *) password,
        strlen((char*) password), 1, key, iv))
    {
        fprintf(stderr, "EVP_BytesToKey failed\n");
        return 1;
    }
	
	*pw = (char*) key;

    /* these will be used for testing only presubmssion */
    printf("Key: "); for(i=0; i<cipher->key_len; ++i) { printf("%02x", key[i]); } printf("\n");
    printf("IV: "); for(i=0; i<cipher->iv_len; ++i) { printf("%02x", iv[i]); } printf("\n");
    
    fprintf(data, "%s\n", key);
    
    return 0;
	
}

int verify_password(FILE* data)
{
	char temp[110];
	char *pw, *line, *hash;
	int valid_pw = 0;
	
	line = hash = NULL;
	while(!valid_pw){		
		printf("Verify your password (6-24 characters): ");
		fgets(temp, PW_LEN, stdin);
		
		if( strlen(temp) < 6 || strlen(temp) > 24 ) {
			printf("Password not in size range\n");
			continue;
		}  
		
		/* copy the password into its holder */
		pw = (char*) malloc((sizeof(temp)/sizeof(char)) + 1);
		strncpy(pw, temp, strlen(temp));
		break;
	}
	
	/* repeat this until eof */
	while(fgets(temp, LINE_LEN, data) != NULL) {
	
		hash = strtok(temp, DELIMIT);
			
		if( hash == NULL ) {
			fprintf(stderr, "Error: data.txt has been tampered with\n");
			printf("password storage error.\n");
			return 1;
		} else if (strlen(hash) != HASH_LENGTH || strtok(line, DELIMIT) != NULL) {
			fprintf(stderr, "The data has been corrupted\n");
			printf("password file corruption\n");
			return 1;
		}
		
		if( encrypt_password(&pw, data) ) {
			return 1;
		} 
		
		if( !strncmp(pw, hash, HASH_LENGTH) ) {
			printf("Password accepted.\n");
			return 0;
		}
	}
	
	printf("Invalid password\n");
	return 1;
}

/* posted by jscmier at :
 * http://stackoverflow.com/questions/2187474/i-am-not-able-to-flush-stdin */
void flush()
{
	int c;
	while ((c = getchar()) != '\n' && c != EOF);
}

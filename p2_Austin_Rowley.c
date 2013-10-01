/*Austin Rowley
  cse340
  project 2
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <ctype.h>
#include <string.h>

#define TRUE  1
#define FALSE 0

#define DEBUG 1     // 1 => Turn ON debugging, 0 => Turn OFF debugging

void print_debug(const char * format, ...)
{
    va_list args;
    if (DEBUG)
    {
        va_start (args, format);
        vfprintf (stdout, format, args);
        va_end (args);
    }
}

//----------------------------- token types ------------------------------
#define KEYWORDS 	12
#define RESERVED 	38
#define VAR 		1
#define BEGIN 		2
#define END 		3
#define ASSIGN 		4
#define IF 			5
#define WHILE 		6
#define DO 			7
#define THEN 		8
#define PRINT 		9
#define INT 		10
#define REAL 		11
#define STRING 		12
#define PLUS 		13
#define MINUS 		14
#define UNDERSCORE 	15
#define DIV 		16
#define MULT 		17
#define EQUAL 		18
#define COLON 		19
#define COMMA 		20
#define SEMICOLON 	21
#define LBRAC 		22
#define RBRAC 		23
#define LPAREN 		24
#define RPAREN 		25
#define NOTEQUAL 	26
#define GREATER 	27
#define LESS 		28
#define LTEQ 		29
#define GTEQ 		30
#define LSHIFT 		31
#define RSHIFT 		32
#define DOT 		33
#define NUM 		34
#define INTID 		35
#define REALID 		36
#define ID 			37
#define ERROR 		38

//------------------- reserved words and token strings -----------------------
char *reserved[] =
	{	"",
		"VAR",
		"BEGIN",
		"END",
		"ASSIGN",
		"IF",
		"WHILE",
		"DO",
		"THEN",
		"PRINT",
		"INT",
		"REAL",
		"STRING",
		"+",
		"-",
		"_",
		"/",
		"*",
		"=",
		":",
		",",
		";",
		"[",
		"]",
		"(",
		")",
		"<>",
		">",
		"<",
		"<=",
		">=",
		"<<",
		">>",
		".",
		"NUM",
		"INTID",
		"REALID",
		"ID",
		"ERROR"
		};

int printReserved(int ttype)
{
	if (ttype <= RESERVED)
	{
		printf("%s\n",reserved[ttype]);
		return 1;
	}
	else
		return 0;
}
//---------------------------------------------------------

//---------------------------------------------------------
// Global Variables associated with the next input token
// This implementation does not allow tokens that are more
// than 100 characters long
#define MAX_TOKEN_LENGTH 100

char token[MAX_TOKEN_LENGTH];     // token string
int  tokenLength;
int  line_no = 0;

//---------------------------------------------------------
// Global Variables associated with the input buffer
// This implementation does not allow lines that are more
// than 500 characters long
#define BUFFER_SIZE     500

int buffer[BUFFER_SIZE];
int start_pos   = 0;	// Signifies the start position in the buffer (#)
int next_pos    = 0;	// Signifies the next character to be read (^)
int maximal_pos = 0;	// Signifies the last character of the maximal 
                        // token found (*)

//---------------------------------------------------------
// Functions associated with the input buffer

void readNextLine()
{
	int  i;
	char c;
	start_pos   = -1; // start position is the position just
                      // before the beginning of the token string
	maximal_pos = -1; // maximal_position points to the end of the
                      // maximal_matched token string
	next_pos    = 0;  // next_pos points to the next input character

	i = 0;
	c = getchar();
	while (c != '\n' && !feof(stdin) && (i < BUFFER_SIZE))
	{
		buffer[i] = c;
		c = getchar();
		i++;
	}
	if (i >= BUFFER_SIZE)
	{
		printf("Maximum allowed line length exceeded\n");
		exit(1);
	}
	else
		buffer[i] = EOF;
	line_no++;
}

/* you can use the following function for Debugging purposes */
void printBuffer()
{
	print_debug("BUFFER: ");
	int i = 0;
	while (buffer[i] != EOF)
	{
		print_debug("%c", (char) buffer[i]);
		i++;
	}
	print_debug("\n");
	print_debug("START_POS   = %d\n", start_pos);
	print_debug("NEXT_POS    = %d\n", next_pos);
	print_debug("MAXIMAL_POS = %d\n", maximal_pos);
}

int skip_space_and_set_positions()
{
	while (isspace((char) buffer[next_pos]))
	{
		next_pos++;
	}
	maximal_pos = next_pos - 1;
	start_pos   = next_pos - 1;
	return 0;
}

// this function copies the maximal token string to the token array
// it assumes the token string is not empty
void copy_token_string_from_buffer()
{
	int i;
	tokenLength = 0;
	for (i = start_pos + 1; i <= maximal_pos; i++)
	{
		token[tokenLength] = (char) buffer[i];
		tokenLength++;
	}
	token[tokenLength] = '\0';
}

//----------------------------------------------------------

// This function checks if a string is a keyword. 
// The implementation is not the most efficient, but probably 
// the simplest!
int isKeyword(char *s)
{
	int i;

	for (i = 1; i <= KEYWORDS; i++)
		if (strcmp(reserved[i],s) == 0)
	   		return i;
	return FALSE;
}

int scan_id_keyword_intid_realid()
{
	int ttype;

    //scan while its a letter or digit
	while (isalnum(buffer[next_pos])) {
		next_pos++;
	}
	
	//keep track of the maximum matched token
	maximal_pos = next_pos - 1;
	
	//its on track for INTID and REALID
	if (buffer[next_pos] == '.') {
	    next_pos++;
	    
	    //still on track for INTID and REALID
	    if (isdigit(buffer[next_pos])) {
	     
	        //loop through while its still a digit
	        if (buffer[next_pos] != '0')
		        while (isdigit(buffer[next_pos]))
			        next_pos++;
	        else // NUM is 0
		        next_pos++;
	        
	        //check for INTID = ID DOT NUM (I)(N)(T)
	        if (buffer[next_pos] == 'I' && buffer[next_pos + 1] == 'N' && buffer[next_pos + 2] == 'T') {
	            ttype = INTID;
	            maximal_pos = next_pos + 2;     //maximum token is the INTID
	            next_pos = maximal_pos + 1;
	            copy_token_string_from_buffer();
	           
	        }
	        //check for REALID = ID DOT NUM (R)(E)(A)(L)
	        else if (buffer[next_pos] == 'R' && buffer[next_pos + 1] == 'E' && buffer[next_pos + 2] == 'A' && buffer[next_pos + 3] == 'L') {
	            ttype = REALID;
	            maximal_pos = next_pos + 3;     //maximum token is the REALID
	            next_pos = maximal_pos + 1;
	            copy_token_string_from_buffer();
	           
	        }
	        //in the case of ie. "var.1IN"
	        else {
	            copy_token_string_from_buffer();
	            next_pos = maximal_pos + 1;
	            ttype = isKeyword(token);
	        }
	    }
	    //in the case of ie. "var.hello"
	    else {
	        copy_token_string_from_buffer();
	        next_pos--;     //the next token should start at '.'
	        ttype = isKeyword(token);
	    }
	}
	//in the case if the current char is anything other than '.', then token must be an ID or KEYWORD
	else {
	    copy_token_string_from_buffer();
	    ttype = isKeyword(token);
	}
	
	//take account for when ttype is just ID
	if (ttype == 0) {
	   ttype = ID;
	}
	   
	return ttype;
}

// this function is called only if the next input character is a digit
int scan_number()
{
	int ttype;

	ttype = NUM;
	if (buffer[next_pos] != '0')
		while (isdigit(buffer[next_pos]))
			next_pos++;
	else // NUM is 0
		next_pos++;

	maximal_pos = next_pos - 1;

	copy_token_string_from_buffer();
	return ttype;
}

int getToken()
{
	char c;
	int ttype;

	skip_space_and_set_positions();

	c = buffer[next_pos];
	next_pos++;

	switch (c)
	{
		case '.': ttype = DOT; break;
		case '+': ttype = PLUS; break;
		case '-': ttype = MINUS; break;
		case '_': ttype = UNDERSCORE; break;
		case '/': ttype = DIV; break;
		case '*': ttype = MULT; break;
		case '=': ttype = EQUAL; break;
		case ':': ttype = COLON; break;
		case ',': ttype = COMMA; break;
		case ';': ttype = SEMICOLON; break;
		case '[': ttype = LBRAC; break;
		case ']': ttype = RBRAC; break;
		case '(': ttype = LPAREN; break;
		case ')': ttype = RPAREN; break;
		case '<':
			/*
			 * TODO: Write code to handle <= and << here
			 */
			 
	        c = buffer[next_pos];
            if (c == '=') {
                ttype = LTEQ;
                next_pos++;     //increment next_pos so that getToken() retrieves the correct char in the buffer
            }
            else if (c == '>') {
	   	        ttype = NOTEQUAL;
	   	        next_pos++;     //increment next_pos so that getToken() retrieves the correct char in the buffer
            } 
		    else if (c == '<') {
			    ttype = LSHIFT;
			    next_pos++;     //increment next_pos so that getToken() retrieves the correct char in the buffer
		    }
            else {
                ttype = LESS;
                maximal_pos = next_pos - 1;
            }
			break;
		case '>':
			/*
			 * TODO: Wriet code to handle >= and >> here
			 */
			 
		    c = buffer[next_pos];
            if (c == '=') {
                ttype = GTEQ;
                next_pos++;     //increment next_pos so that getToken() retrieves the correct char in the buffer
            }
			else if (c == '>') {
				ttype = RSHIFT;
				next_pos++;     //increment next_pos so that getToken() retrieves the correct char in the buffer
			}	
            else {
                ttype = GREATER;
                maximal_pos = next_pos - 1;
            }
			break;
		default :
			if (isdigit(c))
			{
				next_pos--;
				ttype = scan_number();
			}
			else if (isalpha(c)) 
			{
				// token is either a keyword or ID or INTID or REALID
				next_pos--;
				ttype = scan_id_keyword_intid_realid();
				/* 
				 * TODO: Write code to handle INTID and REALID
				 * It might be better to replace scan_id_keyword() 
				 * with a function that handles INTID and REALID 
				 * in addition to ID and keywords
				 */
			}
			else if (c == EOF)
			  ttype = EOF;
			else
			  ttype = ERROR;
			break;
	}	// End Switch
	return ttype;
}

int main()
{
	int ttype;

	while (!feof(stdin))
	{
		readNextLine();
		//printBuffer();
		while ((ttype = getToken()) != EOF)
		{
			/*  EOF indicates that we have reached the end of buffer */
			// printBuffer();
			printf("%d %d ", line_no, ttype);
			if ((ttype == NUM) || (ttype == ID) || 
				(ttype == INTID) || (ttype == REALID))
			{
				printf("%s \n", token);
			}
			else
			{
				printReserved(ttype);
			}
		}
	}
	return 0;
}


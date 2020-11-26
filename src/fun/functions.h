#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "exits.h"
#define LMAXSIZE 3 /* max allowed line length */
#define FSIZE 16     /* max allowed number of characters in a field (cell) include '\0' */
#define FMAX 16      /* max allowed number of fields (columns) in a row */
#define RMAX 16      /* max allowed number of records (rows) in a file */
#define RS '\n'     /* record (row) separator */
#define FS ','     /* record (row) separator */
FILE *ptr;  /* Pointer to the data file. FILE is a structure defined in <stdio.h> */
FILE *mptr; /* Pointer to the metadata file. FILE is a structure defined in <stdio.h> */

int c; /* Character read from the file. */
int rowcount;  /* rowcount: lines counter */
int cc;  /* cc: chars counter */
int totlines; /* saves the total n. of lines read */
int totchars; /* saves the total n. of chars read */
char *field;     /* file table array */
int colcount;    /* fields  counter*/
int fcharcount;  /* field char counter*/
static int ff=0; /* flag goes 1 when a row field is found*/
char temp[FSIZE];
char *buffer; /* buffer containing the chars read from file*/
static size_t bufsize = LMAXSIZE; /* max. size of char buffer */
size_t characters;
static int nrows=RMAX;
static int ncols=FMAX;
/* functions definition */
void parserow(char *mybuffer, int mncols);
void showdata(float *mydata, int mnrows, int mncols);
static float *data;
char *mkeyword[64];  /* array  of metadata keywords */
char *mvalue[64];    /* array  of metadata values   */
int  nmeta;          /* number of metadata items */
static char infile[64];
static char metainfile[64];

void parserow(char *mybuffer, int mncols);
void showdata(float *mydata, int mnrows, int mncols);

void open_metadata_file(const char *metafilen);
void parse_metadata_file();
void close_metadata_file();

void open_data_file(const char *filen);
void parse_data_file();
void close_data_file();
void allocate_buffer();
void allocate_data();
void deallocate_buffer();
void deallocate_data();

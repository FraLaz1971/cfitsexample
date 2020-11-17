/* this is a simple template program reading a FITS binary table 
 processing doing science analysis operations and saving the output on files. 
 Every program which uses the CFITSIO interface must include the
 the fitsio.h header file.  This contains the prototypes for all
 the routines and defines the error status values and other symbolic
 constants used in the interface. fralaz1971@gmail.com November 2020
*/
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "fitsio.h"
/* symbolic constants */
#define CMAX 1024 /* max num of column in the table */
#define RMAX 1024 /* max num of rows in the table */
/* global variables */
int c1; struct PrimaryHeader;
char *filename;
char **header_hdu1; int nkey_hdu1;
char **header_hdu2; int nkey_hdu2;
/* functions definitions */
int main( int argc, char **argv );
void readheader( char *fname );
void readtable( char *fname );
void printerror( int status);
void show_header(char ** hs, int nkeys);
/* functions implementation */
int main(int argc, char **argv)
{
    /*************************************************************************
        This is a simple main program that calls the following routines:
        readheader    - read and print the header keywords in every extension
        readtable     - read columns of data from ASCII and binary tables
    **************************************************************************/
    char * filename;
        if (argc != 2)
        {
                fprintf(stderr, "usage:%s <filename.fit>\n", argv[0]);
                return EXIT_FAILURE;
        } else {
	    filename = malloc(128*sizeof(char));
       nkey_hdu1 = 1024; nkey_hdu2 = 1024;
       header_hdu1 = (char **)malloc(nkey_hdu1 * 80 * sizeof(char));  
        for(int c1=1; c1<=nkey_hdu1;c1++ ){
            header_hdu1[c1-1] = (char *)malloc(80*sizeof(char)); 
        }

       header_hdu2 = (char **)malloc(nkey_hdu2 * 80 * sizeof(char));  
        for(int c1=1; c1<=nkey_hdu2;c1++ ){
            header_hdu2[c1-1] = (char *)malloc(80*sizeof(char)); 
        }

        readheader(argv[1]);
/*            readtable(argv[1]); */
        show_header(header_hdu1, nkey_hdu1); 
        show_header(header_hdu2, nkey_hdu2); 
            printf("\nAll the %s routines ran successfully.\n", argv[0]);
	    free(filename);
        free(header_hdu1);
        free(header_hdu2);
            return EXIT_SUCCESS;
        }
}

/*--------------------------------------------------------------------------*/
/* the readheader function reads the header(s) of all the HDUs
 * in the fits data file and loads the content in a memory structure
/*--------------------------------------------------------------------------*/
void readheader( char *fname )

    /**********************************************************************/
    /* Print out all the header keywords in all extensions of a FITS file */
    /**********************************************************************/
{
    int status, nkeys, keypos, hdutype; 
    int ii; /* cursor on the HDUs */
    int jj; /* cursor un the keys records */
    char card[FLEN_CARD];   /* standard string lengths defined in fitsioc.h */
    filename = fname;     /* name of existing FITS file   */
    fitsfile *fptr;       /* pointer to the FITS file, defined in fitsio.h */

    status = 0;

    /* open the fits file */
    if ( fits_open_file(&fptr, filename, READONLY, &status) ) 
         printerror( status );

    /* attempt to move to next HDU, until we get an EOF error */
    for (ii = 1; !(fits_movabs_hdu(fptr, ii, &hdutype, &status) ); ii++) 
    {
        fprintf(stderr, "readheader(): prcessing HDU  #%d:\n", ii);
        /* get no. of keywords */
        if (fits_get_hdrpos(fptr, &nkeys, &keypos, &status) )
            printerror( status );

        fprintf(stderr, "readheader(): the header for HDU #%d contains %d keywords\n", ii, nkeys);
        /* save the number of keys as a globla variable */

        if (ii==1)
            nkey_hdu1 = nkeys; 
        if (ii==2)
            nkey_hdu2 = nkeys;
        /* setup the dimension strings array containing the primary header 
        header_hdu1 = (char **)malloc(nkey_hdu1 * 80 * sizeof(char));  
        for(int c1=1; c1<=nkey_hdu1;c1++ ){
            header_hdu1[c1-1] = (char *)malloc(80*sizeof(char)); 
        }
        */
        fprintf(stderr, "readheader(): Header listing for HDU #%d:\n", ii);
        for (jj = 1; jj <= nkeys; jj++)  {
            if ( fits_read_record(fptr, jj, card, &status) )
                 printerror( status );
            fprintf(stderr, "%s\n", card); /* print the keyword card on stderr */
            /* save the complete card in the string array */
            if (ii==1)
                strcpy(header_hdu1[jj-1], card);
            else 
                strcpy(header_hdu2[jj-1], card);

            /* extract the KEYWORD name */
            /* extract the VALUE */
            /* extract the content */
            /* header_hdu1=header_hdu1+640;*/
        }
        printf("END\n\n");  /* terminate listing with END */
        jj=1;
        fprintf(stderr, "readheader(): Header scanning for HDU #%d:\n", ii);
        if ( fits_read_record(fptr, jj, card, &status) )
                 printerror( status );
    }

    if (status == END_OF_FILE)   /* status values are defined in fitsioc.h */
        status = 0;              /* got the expected EOF error; reset = 0  */
    else
       printerror( status );     /* got an unexpected error                */

    if ( fits_close_file(fptr, &status) )
         printerror( status );
    return;
}
/*--------------------------------------------------------------------------*/
void readimage( char *fname )

    /************************************************************************/
    /* Read a FITS image and determine the minimum and maximum pixel values */
    /************************************************************************/
{
    fitsfile *fptr;       /* pointer to the FITS file, defined in fitsio.h */
    int status,  nfound, anynull;
    long naxes[2], fpixel, nbuffer, npixels, ii;

#define buffsize 1000
    float datamin, datamax, nullval, buffer[buffsize];
    filename = malloc(128*sizeof(char));
    filename = fname;     /* name of existing FITS file   */

    status = 0;

    if ( fits_open_file(&fptr, filename, READONLY, &status) )
         printerror( status );

    /* read the NAXIS1 and NAXIS2 keyword to get image size */
    if ( fits_read_keys_lng(fptr, "NAXIS", 1, 2, naxes, &nfound, &status) )
         printerror( status );

    npixels  = naxes[0] * naxes[1];         /* number of pixels in the image */
    fpixel   = 1;
    nullval  = 0;                /* don't check for null values in the image */
    datamin  = 1.0E30f;
    datamax  = -1.0E30f;

    while (npixels > 0)
    {
      nbuffer = npixels;
      if (npixels > buffsize)
        nbuffer = buffsize;     /* read as many pixels as will fit in buffer */

      /* Note that even though the FITS images contains unsigned integer */
      /* pixel values (or more accurately, signed integer pixels with    */
      /* a bias of 32768),  this routine is reading the values into a    */
      /* float array.   Cfitsio automatically performs the datatype      */
      /* conversion in cases like this.                                  */

      if ( fits_read_img(fptr, TFLOAT, fpixel, nbuffer, &nullval,
                  buffer, &anynull, &status) )
           printerror( status );

      for (ii = 0; ii < nbuffer; ii++)  {
        if ( buffer[ii] < datamin )
            datamin = buffer[ii];

        if ( buffer[ii] > datamax )
            datamax = buffer[ii];
      }
      npixels -= nbuffer;    /* increment remaining number of pixels */
      fpixel  += nbuffer;    /* next pixel to be read in image */
    }

    printf("\nMin and max image pixels =  %.0f, %.0f\n", datamin, datamax);

    if ( fits_close_file(fptr, &status) )
         printerror( status );
	free(filename);
    return;
}
/*--------------------------------------------------------------------------*/
void readtable( char *fname )

    /************************************************************/
    /* read and print data values from an ASCII or binary table */
    /************************************************************/
{
    fitsfile *fptr;       /* pointer to the FITS file, defined in fitsio.h */
    int status, hdunum, hdutype,  nfound, anynull, ii;
    long frow, felem, nelem, longnull, dia[6];
    float floatnull, den[6];
    char strnull[10], *name[6], *ttype[3]; 

    filename = malloc(128*sizeof(char));
    filename = fname;     /* name of existing FITS file   */

    status = 0;

    if ( fits_open_file(&fptr, filename, READONLY, &status) )
         printerror( status );

    for (ii = 0; ii < 3; ii++)      /* allocate space for the column labels */
        ttype[ii] = (char *) malloc(FLEN_VALUE);  /* max label length = 69 */

    for (ii = 0; ii < 6; ii++)    /* allocate space for string column value */
        name[ii] = (char *) malloc(10);   

    for (hdunum = 2; hdunum <= 3; hdunum++) /*read ASCII, then binary table */
    {
      /* move to the HDU */
      if ( fits_movabs_hdu(fptr, hdunum, &hdutype, &status) ) 
           printerror( status );

      if (hdutype == ASCII_TBL)
          printf("\nReading ASCII table in HDU %d:\n",  hdunum);
      else if (hdutype == BINARY_TBL)
          printf("\nReading binary table in HDU %d:\n", hdunum);
      else
      {
          printf("Error: this HDU is not an ASCII or binary table\n");
          printerror( status );
      }

      /* read the column names from the TTYPEn keywords */
      fits_read_keys_str(fptr, "TTYPE", 1, 3, ttype, &nfound, &status);

      printf(" Row  %10s %10s %10s\n", ttype[0], ttype[1], ttype[2]);

      frow      = 1;
      felem     = 1;
      nelem     = 6;
      strcpy(strnull, " ");
      longnull  = 0;
      floatnull = 0.;

      /*  read the columns */  
      fits_read_col(fptr, TSTRING, 1, frow, felem, nelem, strnull,  name,
                    &anynull, &status);
      fits_read_col(fptr, TLONG, 2, frow, felem, nelem, &longnull,  dia,
                    &anynull, &status);
      fits_read_col(fptr, TFLOAT, 3, frow, felem, nelem, &floatnull, den,
                    &anynull, &status);

      for (ii = 0; ii < 6; ii++)
        printf("%5d %10s %10ld %10.2f\n", ii + 1, name[ii], dia[ii], den[ii]);
    }

    for (ii = 0; ii < 3; ii++)      /* free the memory for the column labels */
        free( ttype[ii] );

    for (ii = 0; ii < 6; ii++)      /* free the memory for the string column */
        free( name[ii] );

    if ( fits_close_file(fptr, &status) ) 
         printerror( status );
	free(filename);
    return;
}
/*--------------------------------------------------------------------------*/
void printerror( int status)
{
    /*****************************************************/
    /* Print out cfitsio error messages and exit program */
    /*****************************************************/
    if (status)
    {
       fits_report_error(stderr, status); /* print error report */
       exit( status );    /* terminate the program, returning error status */
    }
    return;
}

/* prints on the screen all the strings in the read header */
void show_header(char ** hs, int nkeys){
    fprintf(stderr, "**** show_header() START ***\n");
    int pn=0;
    for(c1=0; c1<=nkeys; c1++){
/*        fprintf("show_header() card%d: %s\n", c1, hs[c1]); */
        fprintf(stderr, "show_header() card%d: %s\n", c1, hs[c1]); 
    }

    fprintf(stderr, "**** show_header() STOP ***\n");
}

struct PrimaryHeader
{
    char simple[40];
    int bitpix;
    int naxis;
    int extend;
    char *comments[];
};

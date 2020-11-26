/* functions to plot science data using gnuplot */
#include "plot.h"
/* create the file containing 2D points to be plotted
saving it on an ascii text file, takes in input
the string with the file name ofname, points are real
numbers separated by tabs */

int create_data_file(char *ofname){
         /* open output file for writing */
     strcpy(ofname, "temp.tsv");
     strcat(es, ": Can't open file "); strcat(es, ofname); strcat(es, " for writing \n");
     ofptr = fopen(ofname,"w"); 
     if ( ofptr == NULL  )  /* if can't open outfile receive an herror on opening file */
     {
       printf("Error OPENING FILE: err msg = %s\n", strerror(errno));
       fprintf(stderr,"fopen() failed in source file %s at line # %d\n", __FILE__,__LINE__);
       perror(es);  /* then handle the error */
       printf("exit value = %d : exiting\n", EXIT_FAILURE);
         exit(EXIT_FAILURE);
     } else {
       ret = ferror ( ofptr );
    }
#ifdef DEBUG
    fprintf(stderr, "%s: file %s correctly open for writing\n", "plot.c", ofname);
#endif
    /* process input data */
/*     while ( ( ch = fgetc(ifptr)) != EOF ) */ /* until you don't get the end of input file */
     fprintf(ofptr, "%s\n", "#ascii 2D points test.tsv");
     a=1;
     while ( a < 11 ) 
     {
/*       fputc(ch,ofptr);  */ /* write the file content on outfile */
        fprintf(ofptr, "  %i\t%i\n", a, a*a);
       if(ferror(ofptr))
       {
         printf("File Error writing rows ..!!\n");
         fprintf(stderr,"fopen() failed in source file %s at line # %d\n", __FILE__,__LINE__);
       }
       a++;
     }
        fprintf(ofptr, "  %s\n", "e");
        fprintf(ofptr, "%s\n", "EOF");
}

/* create a gnuplot commands file with directives on how to plot
the points */

int create_gp_cmd_file(char *gp_cmds_fn){
             /* open output file for writing */
     strcat(es, ": Can't open file "); strcat(es, gp_cmds_fn); strcat(es, " for writing \n");
     ofptr = fopen(gp_cmds_fn,"w"); 
     if ( ofptr == NULL  )  /* if can't open outfile receive an herror on opening file */
     {
       printf("Error OPENING FILE: err msg = %s\n", strerror(errno));
       fprintf(stderr,"fopen() failed in source file %s at line # %d\n", __FILE__,__LINE__);
       perror(es);  /* then handle the error */
       printf("exit value = %d : exiting\n", EXIT_FAILURE);
         exit(EXIT_FAILURE);
     } else {
       ret = ferror ( ofptr );
    }
#ifdef DEBUG
    fprintf(stderr, "%s: file %s correctly open for writing\n", "plot.c", ofname);
#endif
    /* process input data */
/*     while ( ( ch = fgetc(ifptr)) != EOF ) */ /* until you don't get the end of input file */
        fprintf(ofptr, "%s\n", "#!/usr/bin/env gnuplot");
        fprintf(ofptr, "%s\n", "# gnuplot commandfile created by fralaz1971@gmail.com");
        fprintf(ofptr, "%s\n", "# time(s)\tcounts(#)");
        fprintf(ofptr, "%s\n", "set terminal qt persist");
        fprintf(ofptr, "%s\n", "set xlabel 'time (s)'");
        fprintf(ofptr, "%s\n", "set ylabel 'counts (#)'");
        fprintf(ofptr, "%s\n", "set title 'My Awesome Plot'");
        fprintf(ofptr, "%s\n", "plot 'temp.tsv' using 1:2");
//      a=1;
//      while ( a < 11 ) 
//      {
//         fprintf(ofptr, "  %i\t%i\n", a, a*a);
//        if(ferror(ofptr))
//        {
//          printf("File Error writing rows ..!!\n");
//          fprintf(stderr,"fopen() failed in source file %s at line # %d\n", __FILE__,__LINE__);
//        }
//        a++;
//      }
//         fprintf(ofptr, "  %s\n", "e");

}

/* launch gnuplot cmd withn gp_cmds_ifn as gnuplot command file and plot to screen */
int gp_plot_screen(char * gp_cmds_ifn){
               fprintf(stderr,"gp_plot_screen: trying to plot on screen" );    
               if (system("bash launchgp_screen.sh")){
               fprintf(stderr,"system() failed to launch gnuplot command source file %s at line # %d, is gnuplot installed and its path included in the PATH environment variable?\n", __FILE__,__LINE__);
    }
}
/* launch gnuplot cmd withn gp_cmds_ifn as gnuplot command file 
 and save plot to png file */
int gp_plot_png(char * gp_cmds_ifn){
    if (system("bash launchgp_png.sh")){
               fprintf(stderr,"system() failed to launch gnuplot command source file %s at line # %d, is gnuplot installed and its path included in the PATH environment variable?\n", __FILE__,__LINE__);
    }
}

int pu_graph(char * gp_cmds_ifn){
/*    if (system("gnuplot -p -e \"plot \'ciao.tsv\'\"")){*/
    if (system("graph -T ps test.tsv >out.ps ; okular out.ps")){
               fprintf(stderr,"system() failed to launch plotutils:graph command source file %s at line # %d, is plotutils:graph installed and its path included in the PATH environment variable?\n", __FILE__,__LINE__);
    }
}

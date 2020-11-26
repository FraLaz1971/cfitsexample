/* function to plot science data using gnuplot */
#ifndef PLOT_H
#define PLOT_H

#define MDIM 255  /* fixed max dimension of buffers & arrays */
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* create the file containing 2D points to be plotted
saving it on an ascii text file, takes in input
the string with the file name ofname, points are real
numbers separated by tabs */

FILE *ifptr;  /* define a pointer to input file */
FILE *ofptr;  /* define a pointer to output file */
static char *str = "Test string \n";
static char es[MDIM] = "";
static char buff[MDIM] = "";
static char * datafile = "data.tsv";
static char * gpfile = "cmds.gp";
int ch, i, ret, a;
unsigned int a1d[MDIM];  


int create_data_file(char *ofname);

/* create a gnuplot commands file with directives on how to plot
the points */

int create_gp_cmd_file(char *gp_cmds_fn);

/* launch gnuplot cmd withn gp_cmds_ifn as gnuplot command file */
int gp_plot_screen(char * gp_cmds_ifn);

/* launch gnuplot cmd withn gp_cmds_ifn as gnuplot command file 
 and save plot to png file */
int gp_plot_png(char * gp_cmds_ifn);


int pu_graph(char * gp_cmds_ifn);
#endif

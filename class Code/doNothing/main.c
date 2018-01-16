#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>
/*
 * SYNOPSIS
 *   Show how to use getopt.
 *   Uses "getopt" (see: man -s 3c getopt) to determine command-line
 *   options and arguments.
 *
 *   From the man page:
 *     #include <stdlib.h>
 *
 *     int getopt(int argc, char * const *argv,  const  char  *opt-string);
 *     extern char *optarg: the value of the option
 *     extern int optind:   index into the argv array
 *     extern int opterr:   flag to turn off error reporting
 *     extern int optopt:   the actual option
 */

static char *prgn;

static void usage(char *);

int main(int argc, char *argv[]) {
   int c = 0;
   int error = 0;
   char *options = ":a:bc:d:e";
   prgn = (char *)malloc(sizeof(char)*(strlen(argv[0])+1));
   strcpy(prgn,argv[0]);
   printf("Testing using %s\n\n", options);
   while ((c = getopt(argc,argv,options)) != -1) {
      /* printf("parsing option at position %d\n",optind-1); */
      if (c == '?') {
         c = optopt;
         printf("illegal option %c\n",c);
      } else if (c == ':') {
         c = optopt;
         printf("missing value for option %c\n",c);
      }
      else {
         printf("option is %c ",c);
         switch (c) {
            case 'a':
               /* do stuff to remember this option */
               break;
            case 'b':
               /* do stuff to remember this option */
               break;
            case 'c':
               /* do stuff to remember this option */
               break;
            case 'd':
               /* do stuff to remember this option */
               break;
            case 'e':
               /* do stuff to remember this option */
               break;
            default:
               printf("Shouldn't happen\n");
         }
         if (optarg) {
            printf("with value (optarg) %s\n",optarg);
         } else {
            printf("\n");
         }
      }
   }
   c = 0;
   printf("\nArguments are\n");
   printf(  "-------------\n");
   for (c = optind; c < argc; c++) {
      printf("parameter %d is the argument %s\n", c-optind+1, argv[c]);
   }

   exit(0);
}

void usage(char *list) {
   fprintf(stderr,"usage: %s %s\n", prgn, list);
}


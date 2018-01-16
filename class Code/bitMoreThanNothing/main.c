#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>
/* #define DEBUG 1 */
/*
 * SYNOPSIS
 *   - Show how to use getopt;
 *   - and, just to have a function, split a command line string
 *     into 'n' pieces.
 *   - and, just to have other options, allow options to change
 *     command line argument to all lower or all upper
 *
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

static char *prgn = 0;
static int n_pieces = 1;
static int lower = 0;
static int upper = 0;

static void usage(char *);
static char *alter_it(int , char *);
static char **divide(int, char *);

/*
 * Function: these functions each demonstrate an at_exit function
 */
static void i_m_quitting(void) {
   printf("I'm quitting\n");
}
static void i_m_really_quitting(void) {
   printf("I'm REALLY quitting\n");
}

int main(int argc, char *argv[]) {
   atexit(i_m_really_quitting);
   atexit(i_m_quitting);
   int c = 0;
   int error = 0;
   char *options = ":n:ul";
   /* save the program name */
   prgn = (char *)malloc(sizeof(char)*(strlen(argv[0])+1));
   strcpy(prgn,argv[0]);
#  ifdef DEBUG
      printf("DEBUG: testing using %s\n\n", options);
#  endif
   while ((c = getopt(argc,argv,options)) != -1) {
#     ifdef DEBUG
         printf("parsing option at position %d\n",optind-1);
#     endif
      if (c == '?') {
         c = optopt;
         printf("illegal option %c\n",c);
      } else if (c == ':') {
         c = optopt;
         printf("missing value for option %c\n",c);
      }
      else {
#        ifdef DEBUG
            printf("option is %c ",c);
#        endif
         switch (c) {
            case 'n':
               /* save the number of pieces into which to split the string */
               n_pieces = atoi(optarg);
               break;
            case 'l':
               /* change all to lower case */
               lower = 1;
               break;
            case 'u':
               /* change all to lower case */
               upper = 1;
               break;
            default:
               usage("This shouldn't happen -- send error report\n");
               return 1;
         }
      }
   }
#  ifdef DEBUG
      printf("\nNumber of pieces is %10d\n", n_pieces);
      printf("\nChange all to lower? %10d\n", lower);
      printf("\nChange all to upper? %10d\n", upper);
      printf("\nArguments are\n");
      printf(  "-------------\n");
      for (c = optind; c < argc; c++) {
         printf("parameter %d is the argument %s\n", c-optind+1, argv[c]);
      }
#  endif

   if (optind != argc-1) {
      usage("Wrong number of arguments.");
      return 2;
   }
   if (lower > 0 && upper > 0) {
      usage("Conflicting case change request.");
      return 3;
   }
   char *string = argv[optind];
   if (n_pieces < 1 || strlen(string) < n_pieces) {
      usage("Number of pieces must be > 0 and <= to string length");
      return 4;
   }
   if (lower || upper) {
      alter_it(lower + 2*upper, string);
   }
   printf("Adjusted string is %s\n", string);
   char **pieces = divide(n_pieces, string);
   int i = 0;
   for (i = 0; i < n_pieces; i++) {
      printf("Piece %d is %s\n", i, pieces[i]);
   }
   return 0;
}

/*
 * Function: these functions are used to demonstrate function pointers.
 */
static int to_upper(int c) { return toupper(c); }
static int to_lower(int c) { return tolower(c); }

/*
 * Function: convert a string to all lower or all upper
 * Parameters: In: flag - if 1 all lower; if 2 all upper
 *             In/Out: arg - the string to convert
 *             Out:
 * Return: the modified string
 */
char *alter_it(int flag, char *arg) {
   int i, l;
   /*
      int (*f)(int) = 0;
      if (flag % 2) {
         f = to_lower;
      } else {
         f = to_upper;
      }
   */
   int (*f)(int) = flag % 2 ? to_lower : to_upper;

   for (i = 0, l = strlen(arg); i < l; i++) {
      arg[i] = f(arg[i]);
   }
   return arg;
}

/*
 * Function: partition a string in "n" pieces
 * Parameters: In: n - the number of pieces to create
 *                 str - the str to partition
 *             In/Out:
 *             Out:
 * Return: an array of "n" strings, each being a piece of the original
 */
char **divide(int n, char * str) {
   /* char **result = malloc(n * sizeof(char *)); */
   char **result = calloc(n, sizeof(char *));
   int len = strlen(str);
   int quot = len / n; /* minimum number of chars a piece */
   int rem = len % n; /* number of leftover chars to be distributed */
   int i = 0, j = 0;
   for (i = 0, j = 0; i < n; i++) {
      /* remember to add space for extra char */

      int chars_to_copy = quot + (rem?rem-=1,1:0);
      /*
      int chars_to_copy = quot;
      if (rem) {
         chars_to_copy++;
         rem -= 1;
      }
      */

      result[i] = malloc(sizeof(char) * (chars_to_copy + 1));
      strncpy(result[i], str+j, chars_to_copy);
      result[i][chars_to_copy] = '\0';
      j += chars_to_copy;
   }
   return result;
}

/*
 * Function: print a usage message to stderr
 * Parameters: In: list - the string to print
 *             In/Out:
 *             Out:
 * Return: void
 */
void usage(char *list) {
   fprintf(stderr,"usage: %s %s\n", prgn, list);
}


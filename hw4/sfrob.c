#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int frobcmp (const void *a, const void *b) {

  char * a_val = *(char **) a; // make a_val point to array at *a
  char * b_val = *(char **) b; // make b_val point to array at *b

  int result = 0;

  while ( *a_val != ' ' && *b_val != ' ' ) {

    char astr [2] = {*a_val, '\0'};
    char bstr [2] = {*b_val, '\0'};

    char a = *astr^42;
    char b = *bstr^42;

    if ( a != b ) {
      result = a - b;
      return result;
    }
    else {
      a_val++;
      b_val++;
    }

  }

  return 0;

}

int main() {

  char * tmp; // holds all of the chars read by stdin
  int tmpused = 0; // positions used in tmp array
  size_t tmpsize = 100;

  char ** result; // final array that will be read by qsort
  size_t rsize = 0; // count of char sequences separated by sp

  tmp =  malloc (sizeof(char) * tmpsize);

  if ( tmp == NULL ) {

    fprintf(stderr, "error! memory not allocated.");
    exit(1);

  }

  // report to stderr if problems reading input

  if ( ferror(stdin) ) {

    fprintf(stderr, "error reading input!");
    exit(1);

  }

  int ch = 0;

  while (  (ch = getchar()) != EOF ) {

    if ( tmpused == tmpsize ) {
      tmp = (char *) realloc(tmp, (sizeof(char) * tmpsize * 2));
      
      if ( tmp == NULL ) {

	fprintf(stderr, "error! memory not allocated.");
	exit(1);

      }

      tmpsize = sizeof(tmp);
    
    }

    char c = (char) ch;

    if ( c == ' ' )
      rsize++;

    tmp[tmpused++] = c;
  } 

  // if the last char in the tmp array is not a space

  if ( tmp[tmpused-1] != ' ' ) {

    if ( tmpused == tmpsize ) {
 
      tmp = (char *) realloc(tmp, (sizeof(char) * tmpsize * 2));
      
      if ( tmp == NULL ) {

	fprintf(stderr, "error! memory not allocated.");
	exit(1);
      }

      tmpsize = sizeof(tmp);
    }

    tmp[tmpused] = ' ';
    tmpused++;
    rsize++;
  }

  result = malloc (sizeof(char *) * rsize);

  if ( result == NULL ) {

    fprintf(stderr, "error! memory not allocated.");
    exit(1);

  }

  result[0] = tmp;
  int s;
  int index = 0;

  for ( s = 0; s < tmpused; s++ ) {

    if ( tmp[s] == ' ' ) {
      index++;

      if ( s + 1 < tmpused )
	result[index] = &tmp[s+1];

    }
  }

  qsort(result, rsize, sizeof(char *), frobcmp);
    
  int i = 0;
    
  for ( ; i < rsize; i++ ) {
        
    int j = 0;
        
    for ( ; result[i][j] != ' '; j++ ) {
            
      putchar(result[i][j]);

    }
    putchar(result[i][j]);
  }

  free(result);
  free(tmp);

  exit(0);
}

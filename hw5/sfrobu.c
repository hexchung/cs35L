#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <limits.h>

int cases = 0;
#define max 1024

int frobcmp (const void *a, const void *b) {

  char * a_val = *(char **) a; // make a_val point to array at *a
  char * b_val = *(char **) b; // make b_val point to array at *b
  
  int result = 0;

  while ( *a_val != ' ' && *b_val != ' ' ) {

    char astr [2] = {*a_val, '\0'};
    char bstr [2] = {*b_val, '\0'};

    char a = *astr^42;
    char b = *bstr^42;

    if ( cases != 0 ) {

      unsigned char aa; 
      aa = toupper((unsigned char) a);
      unsigned char bb;
      bb = toupper((unsigned char) b);

      if ( aa != bb ) {
	result = aa - bb;
	return result;
      }

    }

    else if ( a != b ) {
      result = a - b;
      return result;
    }

    a_val++;
    b_val++;
  }

  return 0;
}

int main(int argc, char *argv[]) {

  struct stat fileinfo;
  size_t fsize = 0;

  char * tmp; // holds all of the chars read by stdin
  char st [max];

  if ( fstat(0, &fileinfo) < 0 ) {
    fprintf(stderr, "error reading file info from stdin! \n");
    exit(1);
  }

  int isfile = 0;

  if ( S_ISREG(fileinfo.st_mode) ) {
    isfile = 1;
    fsize = (int) fileinfo.st_size;
    tmp = (char *) malloc(sizeof(char) * fsize);

    if ( tmp == NULL ) {
      fprintf(stderr, "error! memory not allocated. \n");
      exit(1);
    }

    read(0, st, fsize);
  }

  else if ( S_ISFIFO(fileinfo.st_mode) ) {
    fsize = read(0, st, max);
    tmp = (char *) malloc(sizeof(char) * fsize);
  }

  int k;

  for ( k = 0; k < fsize; k++ )
    *(tmp + k) = st[k];

  if ( tmp[fsize - 1] != ' ' ) {
    tmp = realloc(tmp, sizeof(char) * (fsize + 1));

    if ( tmp == NULL ) {
      fprintf(stderr, "error! memory not allocated. \n");
      exit(1);
    }

    tmp[fsize] = ' ';
    fsize++;
  }

  if ( argv[1] != NULL )
    cases = 1;

  int i;
  char ** result; // final array that will be read by qsort
  int rsize = 0; // count of char sequences separated by sp

  for ( i = 0; i < fsize; i++ ) {
    if ( tmp[i] == ' ' )
      rsize++;
  }

  result = (char **) malloc (sizeof(char *) * rsize);

  if ( result == NULL ) {
    fprintf(stderr, "error! memory not allocated. \n");
    exit(1);
  }

  result[0] = tmp;
  int index = 1;
  int j;

  for ( j = 0; j < fsize; j++ ) {
    if ( tmp[j] == ' ' ) {
      if ( j + 1 < fsize )
	result[index++] = &(tmp[j+1]);
    }
  }

  int m;
  int n;
  int count = 0;

  qsort(result, rsize, sizeof(char *), frobcmp);

  for ( m = 0; m < rsize; m++ ) {
    for ( n = 0; n < fsize; n++ ) {

      if ( result[m][n] != ' ' )
	count++;

      else {
	count++;
	write (1, result[m], count);
	count = 0;
	break;
      }
    }
  }
  
  free(tmp);
  free(result);
  fclose(stdin);
  fclose(stdout);
  fclose(stderr);

  return 0;
}

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {

  if ( sizeof(argv) != 3 ) {

    fprintf(stderr, "incorrect arguments provided.");
    exit(1);

  }

  char *from = argv[1];
  char *to = argv[2];

  if ( strlen(from) != strlen(to) ) {

    fprintf(stderr, "from and to do not have the same number of bytes.");
    exit(1);
    
  }

  int i;
  int j;

  for ( i = 0; i < strlen(from); i++ )
    for ( j = i + 1; j < strlen(to); j++ )
      if ( from[i] == from[j] ) {
	fprintf(stderr, "duplicates in found!");
	exit(1);

      }

  int s;

  while ( (s = getchar()) != EOF ) {

    char c = (char) s;
    int i;

    for ( i = 0; i < strlen(from); i++ )
      if ( c == from[i] )
	s = to[i];

    putchar(s);

  }
}

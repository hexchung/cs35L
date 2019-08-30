#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int main (int argc, char *argv[]) {

  if ( sizeof(argv) < 3 ) {

    fprintf(stderr, "incorrect # of arguments provided. \n");
    exit(1);

  }

  char * from = argv[1];
  char * to = argv[2];

  if ( strlen(from) != strlen(to) ) {

    fprintf(stderr, "from and to do not have the same number of bytes. \n");
    exit(1);

  }

  int i;
  int j;

  for ( i = 0; i < strlen(from); i++ )
    for ( j = i + 1; j < strlen(to); j++ )
      if ( from[i] == from[j] ) {
        fprintf(stderr, "duplicates in found! \n");
        exit(1);

      }

  char c;

  while ( read (0, &c, 1) == 1 ) {

    int i;

    for ( i = 0; i < strlen(from); i++ )
      if ( c == from[i] )
	c = to[i];

    write(1, &c, 1);

  }

}

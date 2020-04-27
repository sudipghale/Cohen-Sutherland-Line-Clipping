#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#include "line.h"
#include "view.h"

//----------------------------------------------------------
int main( int argc, char *argv[] )
{
  if ( argc != 3 ) {
    fprintf( stderr, "Usage: %s <lineFileName> <viewFileName\n", argv[0] );
    exit( 1 );
  }

  char *lineFileName = argv[1];
  char *viewFileName = argv[2];

  //--------------------------------------
  // Load the view information.  We're interested in the canvas
  // size and the portal dimensions (both measured in pixels).
  View *v;

  v = loadView( viewFileName );
  dumpView( v );

  //--------------------------------------
  // Print the canvas size for the SDF file.
  printf( "c %4d %4d\n", v->m_width, v->m_height );

  //--------------------------------------
  // Open the file with proposed lines to draw.
  FILE *fp = fopen( lineFileName, "r" );
  if ( fp == NULL ) {
    fprintf( stderr, "%s: Unable to open '%s' for read.\n",
      argv[0], lineFileName );
    exit( 1 );
  }

  //--------------------------------------
  // Process each proposed line ...
  // Read each line from the proposed line file (it was
  //         opened for you above).
  //       For every line whose first non-whitespace character is
  //         an 'l':
  //         Scan the four numbers (floating point!) following the
  //           'l' to get the p1X, p1Y and p2X, p2Y of the two
  //           endpoints of the line.
  //         Construct a Line holding these values.
  //         Call clipLine() with a pointer to that Line and the
  //           for sides of the portal (from the View structure).
  //         If clipLine() returns 1, use dumpLine() to dump the
  //           line to the output.
  //         If clipLine() returns 0, print a Rejected message.
  //         In either case, count how many lines get dumped and
  //           how many lines get rejected.
  //
  //       After all lines from the file have been processed,
  //         print the line statistics (i.e., how many dumped,
  //         how many rejected.)
  //
  //       You can see the format of the messages by taking a look
  //         at any of the Results/ files.

  //--------------------------------------
  // Tidy up:  free any allocated memory, close the line file.
  char   *line  = NULL;
  size_t  len   = 0;

  int     lineNum = 0;
  int     lineDump = 0;
  int     lineRej = 0;

  while ( getline( &line, &len, fp ) != -1 ) { // reused from the view.c code given and modified accordingly to fit the requirement
    lineNum++;

    char *ptr = line;
    while ( *ptr && isspace( *ptr ) ) ptr++;
   
    if ( *ptr == 'l' ) 
    {
      double p1x, p1y, p2x, p2y;
      int conv = sscanf( ptr+1, " %lf %lf %lf %lf", &p1x, &p1y, &p2x, &p2y);

      if ( conv != 4 ) 
      {
        fprintf( stderr, "loadline: Unable to load the line points at line %d.", lineNum );
      }
      else if ( conv ==4)
      {
        Line inputLine;

        inputLine.p1X = p1x;
        inputLine.p1Y = p1y;
        inputLine.p2X = p2x;
        inputLine.p2Y = p2y;

        int clip = clipLine(&inputLine, v->m_portalXMin, v->m_portalYMin, v->m_portalXMax,  v->m_portalYMax);

        if ( clip == 1)
        {
          dumpLine(&inputLine);
          lineDump++;
        }
        else if ( clip == 0)
        {
          printf("# Rejected l %8.1f %8.1f %8.1f %8.1f\n",inputLine.p1X,inputLine.p1Y,inputLine.p2X,inputLine.p2Y);
          lineRej++;
        }
        else 
        {
          fprintf(stderr, "Call to clipLine() error\n");
          exit(0);
        }

      }
      
    }


  }

  printf( "#- Line statistics ---------------------\n" );
  printf( "# %6d lines drawn.\n", lineDump);
  printf( "# %6d lines rejected.\n", lineRej);
  printf( "#---------------------------------------\n" );


  if(v != NULL)
  {
    freeView( v );
  }
  if(fp !=NULL)
  {
    fclose( fp );
  }
  if(line != NULL)
  {
    free(line);
  }

  //--------------------------------------
  // Ta-da!  All done and no errors.

  return 0;
}

//----------------------------------------------------------

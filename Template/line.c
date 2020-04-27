#include <stdio.h>
#include <stdlib.h>

#include "line.h"

//----------------------------------------------------------
#define INSIDE (0)
#define LEFT   (1)
#define RIGHT  (2)
#define BELOW  (4)
#define ABOVE  (8)

#define EPSILON (1e-13)

int _regionCode( double x, double y, double xMin, double yMin, double xMax, double yMax );

//----------------------------------------------------------
int clipLine( Line *l, double xMin, double yMin, double xMax, double yMax )
{
  // TODO: Implement the clipLine algorithm here.
  //       Arguments:
  //           l : a pointer to the line to clip.
  //
  //           xMin, yMin, xMax, yMax
  //             : the four bounding lines of the view region to
  //               clip against.
  //
  //       Compute the codes of the two endpoints of the line l
  //         using _regionCode().
  //
  //       In an infinite while loop,
  //         Do a trivial accept if possible.
  //         Do a trivial reject if possible.
  //         If neither is possible, select one of the point
  //           codes that's not in the INSIDE region.
  //         If it's ABOVE, slide the point to the yMax line.
  //         ElIf it's BELOW, slide the point to the yMin line.
  //         ElIf it's RIGHT, slide the point to the xMax line.
  //         Elif it's LEFT, slide the point to the xMin line.
  //         Else an error occurred.  Print a message and exit.
  //         Update whichever point got slid in l.
  //         Recompute the code of that point.
  //
  // This routine should return 1 if trivial accept happens, 0 if
  // trivial reject happens.
  //
  // IMPORTANT -- IMPORTANT -- IMPORTANT -- IMPORTANT -- IMPORTANT
  //   You can look at the code in the Clipping handout as a
  //   reference, but remember that code is written in Python and
  //   this is C.
  // IMPORTANT -- IMPORTANT -- IMPORTANT -- IMPORTANT -- IMPORTANT
  
  int code1 =0, code2 = 0, outCode=0;
  double xNew, yNew;
  
  code1 = _regionCode(l->p1X, l->p1Y, xMin, yMin, xMax, yMax);
  code2 = _regionCode(l->p2X, l->p2Y, xMin, yMin, xMax, yMax);

 while(1)
 {
   int pIndex=0;

   if(!(code1 | code2))
   {
     return 1;
   }
   else if ( code1 & code2)
   {
     return 0;
   }
 
   
  if(code1 != INSIDE) 
  {
    outCode= code1;
    pIndex =1;
  }
  else if (code2 != INSIDE)
  {
    outCode = code2;
    pIndex =2;
  }
  else
  {
    fprintf(stderr, "CODE error: check trivial accept and reject condition \n");
    exit(0);
  }
  
 
  if( outCode & ABOVE)
  {
    xNew = l->p1X + (l->p2X - l->p1X) * (yMax - l->p1Y)/(l->p2Y - l->p1Y);
    yNew = yMax;    
  }
  else if( outCode & BELOW)
  {
    xNew = l->p1X + (l->p2X - l->p1X) * (yMin - l->p1Y)/(l->p2Y - l->p1Y);
    yNew = yMin;    
  }
  else if( outCode & RIGHT)
  {
    xNew = xMax;
    yNew = l->p1Y + (l->p2Y - l->p1Y) * (xMax - l->p1X)/(l->p2X - l->p1X);
  }
  else if( outCode & LEFT)
  {
    xNew = xMin;
    yNew = l->p1Y + (l->p2Y - l->p1Y) * (xMin - l->p1X)/(l->p2X - l->p1X);
  }
  else
  {
    fprintf(stderr, "Err: error in sliding the point\n");
    exit(0);
  }
  
  if(pIndex ==1)
  {
    l->p1X = xNew;
    l->p1Y = yNew;
    code1 = _regionCode(l->p1X, l->p1Y, xMin, yMin, xMax, yMax);
  }
  else if(pIndex ==2)
  {
    l->p2X = xNew;
    l->p2Y = yNew;
    code2 = _regionCode(l->p2X, l->p2Y, xMin, yMin, xMax, yMax);
  }
  else 
  {
    fprintf(stderr, "Err:updating new point and code error\n");
  }   

 }

}

//----------------------------------------------------------
void dumpLine( Line *l )
{
  // TODO: Print an 'l' line for the given Line l.
  printf("l %8.1f %8.1f %8.1f %8.1f\n", l->p1X, l->p1Y, l->p2X, l->p2Y);
}

//----------------------------------------------------------
int _regionCode( double x, double y, double xMin, double yMin, double xMax, double yMax )
{
  // TODO: Implement the region code computation here.
  //       Arguments:
  //           x, y
  //             : the point whose region must be computed.
  //
  //           xMin, yMin, xMax, yMax
  //             : the four bounding lines of the view region to
  //               check against.
  //
  //       Assume the region is INSIDE to start.
  //       Check against xMin to see if the point is LEFT.
  //       Check against xMax to see if the point is RIGHT.
  //       Check against yMin to see if the point is BELOW.
  //       Check against yMax to see if the point is ABOVE.
  //
  // This routine should return the code with the proper bits set.
  // (The bits are already defined above for your use.)

  // IMPORTANT -- IMPORTANT -- IMPORTANT -- IMPORTANT -- IMPORTANT
  //   (1) Ensure that you do EPSILON comparisions when
  //       checking against xMin, yMin, xMax, yMax.  EPSILON is
  //       already defined above for your use.
  //   (2) You can look at the code in the Clipping handout as a
  //       reference, but remember that code is written in Python
  //       and this is C.
  // IMPORTANT -- IMPORTANT -- IMPORTANT -- IMPORTANT -- IMPORTANT
  int regionCode = INSIDE;

  if((xMin - x) > EPSILON)
  {
    regionCode |= LEFT;
  }
  else if ((x - xMax) > EPSILON)
  {
    regionCode |= RIGHT;
  }

  if((yMin - y) > EPSILON)
  {
    regionCode |= BELOW;
  }
  else if ((y - yMax) > EPSILON)
  {
    regionCode |= ABOVE;
  }

  return regionCode;

}

//----------------------------------------------------------

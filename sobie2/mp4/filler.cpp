/**
 * @file filler.cpp
 * Implementation of functions in the filler namespace. Heavily based on
 * old MP4 by CS225 Staff, Fall 2010.
 *
 * @author Chase Geigle
 * @date Fall 2012
 */

#include "filler.h"

animation filler::dfs::fillSolid(PNG& img, int x, int y, RGBAPixel fillColor,
                                 int tolerance, int frameFreq)
{
    solidColorPicker solid = solidColorPicker(fillColor);
    return filler::dfs::fill(img, x, y, solid, tolerance, frameFreq);
}

animation filler::dfs::fillGrid(PNG& img, int x, int y, RGBAPixel gridColor,
                                int gridSpacing, int tolerance, int frameFreq)
{
    gridColorPicker grid = gridColorPicker(gridColor, gridSpacing);
    return filler::dfs::fill(img, x, y, grid, tolerance, frameFreq);
}

animation filler::dfs::fillGradient(PNG& img, int x, int y,
                                    RGBAPixel fadeColor1, RGBAPixel fadeColor2,
                                    int radius, int tolerance, int frameFreq)
{
    gradientColorPicker gradient = gradientColorPicker(fadeColor1, fadeColor2, radius, x, y);
    return filler::dfs::fill(img, x, y, gradient, tolerance, frameFreq);
}

animation filler::dfs::fill(PNG& img, int x, int y, colorPicker& fillColor,
                            int tolerance, int frameFreq)
{
    return filler::fill<Stack>(img, x, y, fillColor, tolerance, frameFreq);
}

animation filler::bfs::fillSolid(PNG& img, int x, int y, RGBAPixel fillColor,
                                 int tolerance, int frameFreq)
{
    solidColorPicker solid = solidColorPicker(fillColor);
    return filler::bfs::fill(img, x, y, solid, tolerance, frameFreq);
}

animation filler::bfs::fillGrid(PNG& img, int x, int y, RGBAPixel gridColor,
                                int gridSpacing, int tolerance, int frameFreq)
{
    
    gridColorPicker grid = gridColorPicker(gridColor, gridSpacing);
    return filler::bfs::fill(img, x, y, grid, tolerance, frameFreq);
}

animation filler::bfs::fillGradient(PNG& img, int x, int y,
                                    RGBAPixel fadeColor1, RGBAPixel fadeColor2,
                                    int radius, int tolerance, int frameFreq)
{
    gradientColorPicker gradient = gradientColorPicker(fadeColor1, fadeColor2, radius, x, y);
    return filler::bfs::fill(img, x, y, gradient, tolerance, frameFreq);
}

animation filler::bfs::fill(PNG& img, int x, int y, colorPicker& fillColor,
                            int tolerance, int frameFreq)
{
    
    return filler::fill<Queue>(img, x, y, fillColor, tolerance, frameFreq);
}

template <template <class T> class OrderingStructure>
animation filler::fill(PNG& img, int x, int y, colorPicker& fillColor,
                       int tolerance, int frameFreq)
{
    animation end;
    RGBAPixel* curr;
    int count = 0;
    OrderingStructure<int> xcoord;
    OrderingStructure<int> ycoord;
    int H = img.height();
    int W = img.width();
    int xtemp;
    int ytemp;
    int tolDist;
    //construction of new boolean array for each pixel
    bool** proc = new bool*[W];
    for (int i=0; i<W; i++) {
	proc[i] = new bool[H];
	for (int j=0; j<H; j++)
	    proc[i][j] = false;
    }
    xcoord.add(x);
    ycoord.add(y);
    RGBAPixel orig = *img(x, y);

    while(!xcoord.isEmpty() && !ycoord.isEmpty()) {
	
	xtemp = xcoord.remove();
	ytemp = ycoord.remove();
	curr = img(xtemp, ytemp);
	tolDist = (curr->red - orig.red)*(curr->red - orig.red)+(curr->green - orig.green)*(curr->green - orig.green)+(curr->blue - orig.blue)*(curr->blue - orig.blue);
	//If pixel is not processed and tolerance distance is <= tolerance
        if (!proc[xtemp][ytemp] && tolDist<=tolerance) {
	    proc[xtemp][ytemp] = true;
 	    *(img(xtemp, ytemp)) = fillColor(xtemp, ytemp);
	    count++;
	    //RIGHT
	    if ((xtemp+1) < W) {
	        xcoord.add(xtemp+1);
	        ycoord.add(ytemp);
	    }
	    //DOWN
	    if ((ytemp+1) < H) {
	        xcoord.add(xtemp);
	        ycoord.add(ytemp+1);
	    }    
	    //LEFT
	    if ((xtemp-1) >= 0) {
	        xcoord.add(xtemp-1);
	        ycoord.add(ytemp);
	    }
	
	    //UP
	    if ((ytemp-1) >= 0) {
	        xcoord.add(xtemp);
	        ycoord.add(ytemp-1);
	    }
	    if (count % frameFreq == 0) {
	        end.addFrame(img);
	    }
        }
    }
      

    for (int w=0; w<W; w++) {
	delete[] proc[w]; }
    delete[] proc;
    return end;

	
    
    /**
     * @todo You need to implement this function!
     *
     * This is the basic description of a flood-fill algorithm: Every fill
     * algorithm requires an ordering structure, which is passed to this
     * function via its template parameter. For a breadth-first-search
     * fill, that structure is a Queue, for a depth-first-search, that
     * structure is a Stack. To begin the algorithm, you simply place the
     * given point in the ordering structure. Then, until the structure is
     * empty, you do the following:
     *
     * 1.     Remove a point from the ordering structure.
     *
     *        If it has not been processed before and if its color is
     *        within the tolerance distance (up to and **including**
     *        tolerance away in square-RGB-space-distance) to the original
     *        point's pixel color [that is, \f$(currentRed - OriginalRed)^2 +
              (currentGreen - OriginalGreen)^2 + (currentBlue -
              OriginalBlue)^2 \leq tolerance\f$], then:
     *        1.    indicate somehow that it has been processed (do not mark it
     *              "processed" anywhere else in your code)
     *        2.    change its color in the image using the appropriate
     *              colorPicker
     *        3.    add all of its neighbors to the ordering structure, and
     *        4.    if it is the appropriate frame, send the current PNG to the
     *              animation (as described below).
     * 2.     When implementing your breadth-first-search and
     *        depth-first-search fills, you will need to explore neighboring
     *        pixels in some order.
     *
     *        While the order in which you examine neighbors does not matter
     *        for a proper fill, you must use the same order as we do for
     *        your animations to come out like ours! The order you should put
     *        neighboring pixels **ONTO** the queue or stack is as follows:
     *        **RIGHT(+x), DOWN(+y), LEFT(-x), UP(-y). IMPORTANT NOTE: *UP*
     *        here means towards the top of the image, so since an image has
     *        smaller y coordinates at the top, this is in the *negative y*
     *        direction. Similarly, *DOWN* means in the *positive y*
     *        direction.** To reiterate, when you are exploring (filling out)
     *        from a given pixel, you must first try to fill the pixel to
     *        it's RIGHT, then the one DOWN from it, then to the LEFT and
     *        finally UP. If you do them in a different order, your fill may
     *        still work correctly, but your animations will be different
     *        from the grading scripts!
     * 3.     For every k pixels filled, **starting at the kth pixel**, you
     *        must add a frame to the animation, where k = frameFreq.
     *
     *        For example, if frameFreq is 4, then after the 4th pixel has
     *        been filled you should add a frame to the animation, then again
     *        after the 8th pixel, etc.  You must only add frames for the
     *        number of pixels that have been filled, not the number that
     *        have been checked. So if frameFreq is set to 1, a pixel should
     *        be filled every frame.
     */
    
}

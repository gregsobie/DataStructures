#include <cstdlib>
#include "png.h"
#include <iostream>
using namespace std;
//
// sets up the output image
PNG* setupOutput(int w, int h)
{
    PNG* image = new PNG(w, h);
    return image;
}

// Returns my favorite color
RGBAPixel* myFavoriteColor(int intensity)
{
    /* Color must point to memory on heap
	because stack frame is torn down
	after we exit this function */
    RGBAPixel* color=new RGBAPixel();
    color->red   = 0;
    color->green = intensity / 2;
    color->blue  = intensity;
    return color;
}

void sketchify()
{
    // Load in.png
    /* Pointer must point to memory on heap
	before we dereference it */
    PNG* original=new PNG();

    //cout << "Reached line 28" << endl;
    original->readFromFile("in.png");
    int width = original->width();
    int height = original->height();
    //cout << "Reached line 32" << endl;

    // Create out.png
    PNG* output;
    output=setupOutput(width, height);

    // Load our favorite color to color the outline
    RGBAPixel* myPixel = myFavoriteColor(192);

    // Go over the whole image, and if a pixel differs from that to its upper
    // left, color it my favorite color in the output
    for (int y = 1; y > 0 && y < height; y++) {
        for (int x = 1; x > 0 && x < width; x++) {
            // Calculate the pixel difference
            RGBAPixel* prev = (*original)(x - 1, y - 1);
            RGBAPixel* curr = (*original)(x, y);
            int diff = abs(curr->red - prev->red)
                       + abs(curr->green - prev->green)
                       + abs(curr->blue - prev->blue);

            // If the pixel is an edge pixel,
            // color the output pixel with my favorite color
            RGBAPixel* currOutPixel = (*output)(x, y);
            if (diff > 100)
                *currOutPixel = *myPixel;
        }
    }

    // Save the output file
    output->writeToFile("out.png");

    // Clean up memory
    delete myPixel;
    delete output;
    delete original;
}

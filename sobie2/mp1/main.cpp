/**
 * @file main.cpp
 * A simple C++ program that manipulates an image.
 */
#include <algorithm>
#include <iostream>

#include "rgbapixel.h"
#include "png.h"

using namespace std;

/**
 * This function rotates a rectangle of a PNG by 180 degrees, flipping
 * the image vertically.
 *
 * @param original A PNG object which holds the image data to be modified.
 *
 * @return The rotated image.
 */
PNG rotate(PNG original)
{
	//creates a temp image to store the vertically flipped image information
	PNG mod;
	mod = PNG(original.width(), original.height());
	for (size_t j = 0; j < original.height(); j++) {
		for (size_t i = 0; i < original.width(); i++) {
			mod(mod.width()-i-1, mod.height()-j-1)->red = original(i, j)->red;
			mod(mod.width()-i-1, mod.height()-j-1)->green = original(i, j)->green;
			mod(mod.width()-i-1, mod.height()-j-1)->blue = original(i, j)->blue;
        	}
 	}
    return mod;
}

/**
 * The main function in this program (the starting point of the execution of our
 * code).
 *
 * @return An integer indicating whether execution was successful.
 */
int main()
{
    // Open a new PNG image from the file in.png.
    PNG image("in.png");

    // Rotate the image read from in.png by 180 degrees
    image = rotate(image);

    // Save the modified image to a file called out.png, overwriting the file
    // if it already exists.
    image.writeToFile("out.png");

    return 0;
}

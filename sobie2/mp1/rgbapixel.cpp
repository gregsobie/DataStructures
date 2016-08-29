#include <cstdint>

#include "rgbapixel.h"

using std::uint8_t;

//default constructor -- white pixel
RGBAPixel::RGBAPixel(){
	alpha = 255;
	red=255;
	green=255;
	blue=255;
}

//custom constructor -- custom pixel
RGBAPixel::RGBAPixel(uint8_t red, uint8_t green, uint8_t blue){
	alpha = 255;		//all pixels will start completely opaque
	this->red = red;
	this->green = green;
	this->blue = blue;
}

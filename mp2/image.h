#ifndef IMAGE_H
#define IMAGE_H

#include "rgbapixel.h"
#include "png.h"

class Image : public PNG {
	public:
		void flipleft();
		void adjustbrightness(int r, int g, int b);
		void invertcolors();
};

#endif

#include "image.h"

void Image::flipleft() {
	RGBAPixel temp=*(*this)(0,0);
	for(int i=0; i<int(this->width())/2; i++){
		for(int j=0; j<int(this->height()); j++){
			temp=*(*this)(i,j);
			*(*this)(i,j)=*(*this)(int(this->width())-i-1, j);
			*(*this)(int(this->width())-i-1, j)=temp;
		}
	}
}

void Image::adjustbrightness(int r, int g, int b) {
	for(int k=0; k<int(this->width()); k++){
		for(int l=0; l<int(this->height()); l++){
			if((*this)(k,l)->red + r > 255)
				(*this)(k,l)->red=255;
			else if((*this)(k,l)->red + r < 0)
				(*this)(k,l)->red=0;
			else
				(*this)(k,l)->red += r;
			if((*this)(k,l)->green + g > 255)
				(*this)(k,l)->green=255;
			else if((*this)(k,l)->green + g < 0)
				(*this)(k,l)->green=0;
			else
				(*this)(k,l)->green += g;
			if((*this)(k,l)->blue + b > 255)
				(*this)(k,l)->blue=255;
			else if((*this)(k,l)->blue + b < 0)
				(*this)(k,l)->blue=0;
			else
				(*this)(k,l)->blue += b;
		}
	}
	
}

void Image::invertcolors() {
	for(int m=0; m<int(this->width()); m++){
		for(int n=0; n<int(this->height()); n++){
			(*this)(m,n)->red = 255 - (*this)(m,n)->red;
			(*this)(m,n)->blue = 255- (*this)(m,n)->blue;
			(*this)(m,n)->green = 255 - (*this)(m,n)->green;
		}
	}
}



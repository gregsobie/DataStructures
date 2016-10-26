/**
 * @file quadtree.cpp
 * Quadtree class implementation.
 * @date Spring 2008
 */

#include "quadtree.h"
using namespace std;

#define QUAD_NW 1
#define QUAD_NE 2
#define QUAD_SW 3
#define QUAD_SE 4
#define QUAD_COUNT 4

/* Default constructor */
Quadtree::Quadtree(){
	root=NULL;
}

/* Custom constructor, calls helper function */
Quadtree::Quadtree(PNG const &source, int resolution){
	buildTree(source, resolution);
}

/* Copy constructor */
Quadtree::Quadtree(Quadtree const &other){
	root = copy(other.root);
}

/* Copy helper function */
Quadtree::QuadtreeNode* Quadtree::copy(QuadtreeNode* copyFrom){
	/* Recursive base case */
	if(copyFrom==NULL)
		return NULL;
	/* Node to copy to. Recursively copy child nodes */
	QuadtreeNode* copyTo = new QuadtreeNode::QuadtreeNode(copyFrom);
	copyTo->nwChild = copy(copyFrom->nwChild);
	copyTo->neChild = copy(copyFrom->neChild);
	copyTo->swChild = copy(copyFrom->swChild);
	copyTo->seChild = copy(copyFrom->seChild);
	return copyTo;
}

/* Destructor */
Quadtree::~Quadtree(){
	clear(root);
}

/* Destructor helper function */
void Quadtree::clear(QuadtreeNode* &currNode){
	/* Recursive base case */
	if(currNode==NULL)
		return;
	/* Recursively clear ccccchild nodes */
	clear(currNode->nwChild);
	clear(currNode->neChild);
	clear(currNode->swChild);
	clear(currNode->seChild);
	delete(currNode);
	currNode=NULL;
}


/*
 * Member Functions
 */

/* Assignment operator overload -- frees memory associated
   with this quadtree and sets contents to that of parameter's */
Quadtree const & Quadtree::operator=(Quadtree const &other){
	clear(root);
	root=copy(other.root);
	/* Returns constant reference to copied Quadtree value */
	return *this;
}

/* Builds the tree by deleting contents of this quadtree and 
   replacing with contents of upper (res)x(res) block of source */
void Quadtree::buildTree(PNG const &source, int resolution){
	root = new QuadtreeNode(0,0,resolution);
	build(source, resolution, root);
}

/* BuildTree helper function */
void Quadtree::build(PNG const &source, int resolution, QuadtreeNode* currNode){
	/* Recursive base case -- 1x1 square */
	if(resolution==1){
		currNode->element = *(source(currNode->x, currNode->y));
		return;
	}

	/* Resolution reduced by power of 2 for each layer */
	int newResolution = resolution/2;
	/* Initalize nodes in next layer of tree */
	currNode->nwChild = new QuadtreeNode(currNode->x, currNode->y, newResolution);
	currNode->neChild = new QuadtreeNode(currNode->x + newResolution, currNode->y, newResolution);
	currNode->swChild = new QuadtreeNode(currNode->x, currNode->y + newResolution, newResolution);
	currNode->seChild = new QuadtreeNode(currNode->x + newResolution, currNode->y + newResolution, newResolution);

	/* Recursively build tree */
	build(source, newResolution, currNode->nwChild);
	build(source, newResolution, currNode->neChild);
	build(source, newResolution, currNode->swChild);
	build(source, newResolution, currNode->seChild);

	/* Update colors */
	currNode->element.red = getAverage(currNode, 'R');
	currNode->element.green = getAverage(currNode, 'G');
	currNode->element.blue = getAverage(currNode, 'B');
}

uint8_t Quadtree::getAverage(QuadtreeNode* node, char color){
	switch(color){
		case 'R': return (node->nwChild->element.red +
				  node->neChild->element.red +
				  node->swChild->element.red +
				  node->seChild->element.red) / QUAD_COUNT;
				  break;
		case 'B': return (node->nwChild->element.blue +
				  node->neChild->element.blue +
				  node->swChild->element.blue +
				  node->seChild->element.blue) / QUAD_COUNT;
				  break;
		case 'G': return (node->nwChild->element.green +
				  node->neChild->element.green +
				  node->swChild->element.green +
				  node->seChild->element.green) / QUAD_COUNT;
				  break;
		default: return 0; break;
	}
}

/* Gets the RGBAPixel at the (x,y) location in the bitmap image
	that the quadtree represents */
RGBAPixel Quadtree::getPixel(int x, int y) const {
	return getPixelHelper(x,y,root);
}

RGBAPixel Quadtree::getPixelHelper(int x, int y, QuadtreeNode* currNode) const {
	/* Recursive base case -- we need only check if one child is empty,
		since either all child nodes or none of them are empty */
	if(((currNode->x == x) && (currNode->y == y) && (currNode->resolution == 1)) ||
		(currNode->nwChild == NULL))
		return currNode->element;
	/* Recurse through quadtree to find where pixel resides */
	switch(findQuadrant(x,y,currNode)){
		case QUAD_NW: return getPixelHelper(x,y,currNode->nwChild); break;
		case QUAD_NE: return getPixelHelper(x,y,currNode->neChild); break;
		case QUAD_SW: return getPixelHelper(x,y,currNode->swChild); break;
		case QUAD_SE: return getPixelHelper(x,y,currNode->seChild); break;
		default:      return *(new RGBAPixel()); break;
	}
}

/* Finds the quadrant of next layer of quadtree that the pixel at (x,y) resides in */
int Quadtree::findQuadrant(int x, int y, QuadtreeNode* currNode) const {
	/* Check if pixel is in NW quadrant of next layer */
	if(((x >= currNode->nwChild->x) && (x < currNode->nwChild->x + currNode->nwChild->resolution)) &&
	   ((y >= currNode->nwChild->y) && (y < currNode->nwChild->y + currNode->nwChild->resolution)))
		return QUAD_NW;
	/* Check if pixel is in NE quadrant of next layer */
	else if(((x >= currNode->neChild->x) && (x < currNode->neChild->x + currNode->neChild->resolution)) &&
	   ((y >= currNode->neChild->y) && (y < currNode->neChild->y + currNode->neChild->resolution)))
		return QUAD_NE;
	/* Check if pixel is in SW quadrant of next layer */
	else if(((x >= currNode->swChild->x) && (x < currNode->swChild->x + currNode->swChild->resolution)) &&
	   ((y >= currNode->swChild->y) && (y < currNode->swChild->y + currNode->swChild->resolution)))
		return QUAD_SW;
	/* Check if pixel is in SE quadrant of next layer */
	else if(((x >= currNode->seChild->x) && (x < currNode->seChild->x + currNode->seChild->resolution)) &&
	   ((y >= currNode->seChild->y) && (y < currNode->seChild->y + currNode->seChild->resolution)))
		return QUAD_SE;
	else 	return -1;
}

/* Returns the underlying PNG object represented by the quadtree */
PNG Quadtree::decompress() const {
	if(root==NULL)
		return *(new PNG());
	PNG ret(root->resolution, root->resolution);
	for(int i=0; i<root->resolution; i++){
		for(int j=0; j<root->resolution; j++)
			*ret(i,j)=getPixel(i,j);
	}
	return ret;
}

void Quadtree::clockwiseRotate(){

}

void Quadtree::clockwiseRotate(QuadtreeNode* currNode){

}

void Quadtree::prune(int tolerance){

}

void Quadtree::prune(int tolernce, QuadtreeNode* currNode){

}

int Quadtree::difference(QuadtreeNode* a, QuadtreeNode* b) const{
	return 0;
}

int Quadtree::pruneSize(int tolerance) const{
	return 0;
}

int Quadtree::pruneSize(int tolerance, QuadtreeNode* currNode) const{
	return 0;
}

int Quadtree::idealPrune(int numLeaves) const{
	return 0;
}


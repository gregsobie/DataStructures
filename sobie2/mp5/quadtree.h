/**
 * @file quadtree.h
 * Quadtree class definition.
 * @date Spring 2008
 */

#ifndef QUADTREE_H
#define QUADTREE_H

#include "png.h"

/**
 * A tree structure that is used to compress PNG images.
 */
class Quadtree
{
  public:
	Quadtree();
	Quadtree(PNG const &source, int resolution);
	Quadtree(Quadtree const &other);
	~Quadtree();

	Quadtree const &operator=(Quadtree const &other);
	void buildTree(PNG const &source, int resolution);
	RGBAPixel getPixel(int x, int y) const;
	PNG decompress() const;
	void clockwiseRotate();
	void prune(int tolerance);
	int pruneSize(int tolerance) const;
	int idealPrune(int numLeaves) const;
  private:
    /**
     * A simple class representing a single node of a Quadtree.
     * You may want to add to this class; in particular, it could
     * probably use a constructor or two...
     */
    class QuadtreeNode
    {
      public:
        QuadtreeNode* nwChild; /**< pointer to northwest child */
        QuadtreeNode* neChild; /**< pointer to northeast child */
        QuadtreeNode* swChild; /**< pointer to southwest child */
        QuadtreeNode* seChild; /**< pointer to southeast child */

        RGBAPixel element; /**< the pixel stored as this node's "data" */
	int x;
	int y;
	int resolution;

	/* Internal node constructor */
	QuadtreeNode(int xposition, int yposition, int res){
		x=xposition;
		y=yposition;
		resolution=res;
		nwChild=neChild=swChild=seChild=NULL;
	}

	/* Leaf node constructor */
	QuadtreeNode(int xposition, int yposition, int res, PNG &source){
		x=xposition;
		y=yposition;
		resolution=res;
		nwChild=neChild=swChild=seChild=NULL;
		element=*(source(x,y));
	}

	/* Copy node constructor */
	QuadtreeNode(QuadtreeNode const *other){
		x=other->x;
		y=other->y;
		resolution=other->resolution;
		nwChild=neChild=swChild=seChild=NULL;
		element=other->element;
	}
    };

	void clear(QuadtreeNode* &currNode);
	QuadtreeNode* copy(QuadtreeNode* other);
	void build(PNG const &source, int res, QuadtreeNode* currNode);
	RGBAPixel getPixelHelper(int x, int y, QuadtreeNode* currNode) const;
	int findQuadrant(int x, int y, QuadtreeNode* currNode) const;
	uint8_t getAverage(QuadtreeNode* node, char color);
	void clockwiseRotate(QuadtreeNode* currNode);
	void prune(int tolerance, QuadtreeNode* currNode);
	int difference(QuadtreeNode* a, QuadtreeNode* b) const;
	int pruneSize(int tolerance, QuadtreeNode* currNode) const;
	int idealPrune(int numLeaves, int n, int interval) const;
	

    QuadtreeNode* root; /**< pointer to root of quadtree */


/**** Functions for testing/grading                      ****/
/**** Do not remove this line or copy its contents here! ****/
#include "quadtree_given.h"
};

#endif

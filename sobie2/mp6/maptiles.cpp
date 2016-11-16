/**
 * @file maptiles.cpp
 * Code for the maptiles function.
 */

#include <iostream>
#include <map>
#include "maptiles.h"

using namespace std;

MosaicCanvas* mapTiles(SourceImage const& theSource,
                       vector<TileImage> const& theTiles)
{
    /**
     * @todo Implement this function!
     */
    MosaicCanvas * mapTiles = new MosaicCanvas(theSource.getRows(), theSource.getColumns());
    vector<Point<3>> avgColors;
    map<Point<3>, TileImage> avgColorMap;
    RGBAPixel temp;
    for (size_t i=0; i<theTiles.size(); i++)
    {
    temp = theTiles[i].getAverageColor();
        Point<3> color(temp.red, temp.green, temp.blue);
    avgColorMap[color] = theTiles[i];
        avgColors.push_back(color);
    }

    KDTree<3> tempTree(avgColors);
    for (int i=0; i<theSource.getRows(); i++) {
    for (int j=0; j<theSource.getColumns(); j++) {
        temp = theSource.getRegionColor(i, j);
        Point<3> point(temp.red, temp.green, temp.blue);
        Point<3> nearest = tempTree.findNearestNeighbor(point);
        mapTiles->setTile(i, j, avgColorMap[nearest]);
        }
    }

    return mapTiles;
} 

/**
 * @file maptiles.cpp
 * Code for the maptiles function.
 */

#include <iostream>
#include <map>

#include "maptiles.h"
#include "sourceimage.h"

using namespace std;


Point<3> convertToXYZ(LUVAPixel pixel) {
    return Point<3>( pixel.l, pixel.u, pixel.v );
}

MosaicCanvas* mapTiles(SourceImage const& theSource,
                       vector<TileImage>& theTiles)
{
    int rows = theSource.getRows();
    int cols = theSource.getColumns();
    MosaicCanvas* result = new MosaicCanvas(rows, cols);
    std::vector<Point<3>> tileColors;
    for (TileImage const& tile : theTiles) 
    {
        LUVAPixel average = tile.getAverageColor();
        Point<3> color = convertToXYZ(average);
        tileColors.push_back(color);
    }
    KDTree<3> colorTree(tileColors);
    int rows2 = result->getRows();
    int cols2 = result->getColumns();
    for (int row = 0; row < rows2; ++row) 
    {
        for (int col = 0; col < cols2; ++col) 
        {
            Point<3> key = convertToXYZ(theSource.getRegionColor(row, col));
            Point<3> closest = colorTree.findNearestNeighbor(key);
            unsigned long temp = 0;
            for (unsigned long i = 0; i < tileColors.size(); ++i) 
            {
                if (tileColors[i] == closest) 
                {
                    temp = i;
                    break;
                }
            }
            TileImage const& closest2 = theTiles[temp];
            TileImage* ptr = new TileImage(closest2);
            result->setTile(row, col, ptr);
        }
    }
    return result;
}

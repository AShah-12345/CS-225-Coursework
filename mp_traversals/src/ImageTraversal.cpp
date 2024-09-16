#include <cmath>
#include <iterator>
#include <iostream>

#include "cs225/HSLAPixel.h"
#include "cs225/PNG.h"
#include "Point.h"

#include "ImageTraversal.h"

namespace Traversals {
  /**
  * Calculates a metric for the difference between two pixels, used to
  * calculate if a pixel is within a tolerance.
  *
  * @param p1 First pixel
  * @param p2 Second pixel
  * @return the difference between two HSLAPixels
  */
  double calculateDelta(const HSLAPixel & p1, const HSLAPixel & p2) {
    double h = fabs(p1.h - p2.h);
    double s = p1.s - p2.s;
    double l = p1.l - p2.l;

    // Handle the case where we found the bigger angle between two hues:
    if (h > 180) { h = 360 - h; }
    h /= 360;

    return sqrt( (h*h) + (s*s) + (l*l) );
  }
  
  /**
  * Adds a Point for the bfs traversal to visit at some point in the future.
  * @param work_list the structure which stores the list of points which need to be visited by the traversal
  * @param point the point to be added
  */
  void bfs_add(std::deque<Point> & work_list, const Point & point) {
    /** @todo [Part 1] */
    work_list.push_front(point);
  }

  /**
  * Adds a Point for the dfs traversal to visit at some point in the future.
  * @param work_list the structure which stores the list of points which need to be visited by the traversal
  * @param point the point to be added
  */
  void dfs_add(std::deque<Point> & work_list, const Point & point) {
    /** @todo [Part 1] */
    work_list.push_front(point);
  }

  /**
  * Removes and returns the current Point in the bfs traversal
  * @param work_list the structure which stores the list of points which need to be visited by the traversal
  */
  Point bfs_pop(std::deque<Point> & work_list) {
    /** @todo [Part 1] */
    //return Point(0, 0);
    Point curr = work_list.back();
    work_list.pop_back();
    return curr;
  }

  /**
  * Removes and returns the current Point in the dfs traversal
  * @param work_list the structure which stores the list of points which need to be visited by the traversal
  */
  Point dfs_pop(std::deque<Point> & work_list) {
    /** @todo [Part 1] */
    //return Point(0, 0);
    Point curr = work_list.front();
    work_list.pop_front();
    return curr;
  }

  /**
  * Initializes a ImageTraversal on a given `png` image,
  * starting at `start`, and with a given `tolerance`.
  * @param png The image this traversal is going to traverse
  * @param start The start point of this traversal
  * @param tolerance If the current point is too different (difference larger than tolerance) with the start point,
  * it will not be included in this traversal
  * @param traversal_add a function pointer to an implemented function which takes in a reference to the work list
  * and the point to be added
  * @param traversal_pop a function pointer to an implemented function which takes in a reference to the work list
  * and returns the next point to be processed in the traversal
  */
  ImageTraversal::ImageTraversal(const PNG & png, const Point & start, double tolerance, add_function traversal_add, pop_function traversal_pop) {
    /** @todo [Part 1] */
    png_ = png;
    start_ = start;
    tolerance_ = tolerance;
    traversal_add_ = traversal_add;
    traversal_pop_ = traversal_pop;
  }

  /**
  * Returns an iterator for the traversal starting at the first point.
  */
  ImageTraversal::Iterator ImageTraversal::begin() {
    /** @todo [Part 1] */
    return ImageTraversal::Iterator(png_, start_, tolerance_, traversal_add_, traversal_pop_, png_.width(), png_.height());
  }

  /**
  * Returns an iterator for the traversal one past the end of the traversal.
  */
  ImageTraversal::Iterator ImageTraversal::end() 
  {
    Point end(-1, 1);
    ImageTraversal::Iterator temp;
    return temp.setPoint(end);
  }
  
  ImageTraversal::Iterator& ImageTraversal::Iterator::setPoint(Point &newpt)
  {
    curr = newpt;
    return *this;
  }

  /**
  * Default iterator constructor.
  */
  ImageTraversal::Iterator::Iterator() {
    /** @todo [Part 1] */
    
  }

  ImageTraversal::Iterator::Iterator(const PNG & png, Point & start, double tolerance, add_function traversal_add, pop_function traversal_pop, int width, int height)
  {
    png_ = png;
    start_ = start;
    tolerance_ = tolerance;
    traversal_add_ = traversal_add;
    traversal_pop_ = traversal_pop;
    curr = start;
    visitedPoint.resize(width); //allocate width for visited points vector
    bool alwaysf = false;
    for(int i = 0; i < width; i++)
    {
        visitedPoint[i].resize(height, alwaysf);
    }
    work_list.push_front(start_);
  } 

  /**
  * Iterator increment opreator.
  *
  * Advances the traversal of the image.
  */
ImageTraversal::Iterator& ImageTraversal::Iterator::operator++() {
  unsigned int currX = curr.x;
  unsigned int currY = curr.y;
  if (work_list.size() == 1 && work_list.front() == start_) {
    work_list.pop_front();
    visitedPoint[start_.x][start_.y] = true;
  }
  std::vector<Point> neighbors;
  neighbors.emplace_back(currX + 1, currY);
  neighbors.emplace_back(currX, currY + 1);
  neighbors.emplace_back(currX - 1, currY);
  neighbors.emplace_back(currX, currY - 1);
  for (const auto& neighbor : neighbors) {
    if (neighbor.x < png_.width() && neighbor.y < png_.height() && !visitedPoint[neighbor.x][neighbor.y])
    {
      if (calculateDelta(png_.getPixel(start_.x, start_.y), png_.getPixel(neighbor.x, neighbor.y)) < tolerance_) 
      {
        traversal_add_(work_list, neighbor);
      }
    }
  }
  if (!work_list.empty()) 
  {
    do 
    {
      curr = traversal_pop_(work_list);
    } 
    while (visitedPoint[curr.x][curr.y] && !work_list.empty());
    visitedPoint[curr.x][curr.y] = true;
  } 
  else 
  { 
    Point end(-1, -1);
    curr = end;
  }
  return *this;
}

   

  /**
  * Iterator accessor opreator.
  *
  * Accesses the current Point in the ImageTraversal.
  */
  Point ImageTraversal::Iterator::operator*() {
    /** @todo [Part 1] */
    return curr;
  }

  /**
  * Iterator inequality operator.
  *
  * Determines if two iterators are not equal.
  */
  bool ImageTraversal::Iterator::operator!=(const ImageTraversal::Iterator &other) {
    if ((work_list.empty() && other.work_list.empty()) || (curr.x == other.curr.x && curr.y == other.curr.y)) 
    {
      return false;
    } 
    else if (work_list.empty() || other.work_list.empty()) 
    {
      return true;
    } 
    return true;
  }
}
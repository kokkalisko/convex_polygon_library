#ifndef CONVEX_HULL_H
#define CONVEX_HULL_H

#include "convex_polygon_library/utilities.h"

/*!
 * Computes a convex hull of a number of points in 2D using Graham scan with 
 * O(nlogn) complexity where n is the number of the points.
 * It returns a stack of points where the points are rotated counterclockwise
 * starting from the point at the bottom of the stack. If an empty stack is
 * return, then it was not possible to come up with a convex hull of the points
 * given.
 * \param  points  A vector of Point
 * \return A stack of points composing the convex hull
 */
std::stack<Point> convex_hull_from_points(std::vector<Point> points);

#endif

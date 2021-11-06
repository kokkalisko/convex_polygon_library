#ifndef CONVEX_POLYGON_H
#define CONVEX_POLYGON_H

#include "polygon_operations/utilities.h"
#include <stack>

/*!
 * Finds whether a given point is contained inside a given polygon with
 * complexity O(n) where n is the number of vertices of the polygon
 * The polygon is given in a V-representation and more particularly as a
 * stack where the points are rotated counterclockwise starting from the
 * bottom point of the stack 
 * \param pointInConsideration Point that we want to check whether it is inside the polygon
 * \param convexPolygon Stack of points 
 * \return Boolean indicating whether the point is indeed included in the polygon
 */
bool point_is_in_polygon(const Point& pointInConsideration, std::stack<Point> convexPolygon);

/*!
 * Finds whether two polygons intersect with each other using Seperating Axis Theorem (SAP).
 * This function takes as arguments two polygons as stack of points/vertices moving clockwise 
 * as the stack is traversed from top to bottom. This function first transforms the
 * stack to vector (that is why the stack is passed by value).
 * For more on SAP see <a href="http://web.archive.org/web/20141127210836/http://content.gpwiki.org/index.php/Polygon_Collision">here</a>.
 * \param polygon1 Stack of Point for the first polygon
 * \param polygon2 Stack of Point for the second polygon
 * \return Boolean indicating whether the two polygons intersect
 */
bool do_intersect(std::stack<Point> polygon1, std::stack<Point> polygon2);

/*!
 * Finds whether two polygons intersect with each other using Seperating Axis Theorem (SAP).
 * This function takes as arguments two polygons as a vector of points/vertices moving counterclockwise 
 * starting from the beginning of the vector.
 * For more on SAP see <a href="http://web.archive.org/web/20141127210836/http://content.gpwiki.org/index.php/Polygon_Collision">here</a>.
 * \param polygon1 Vector of Point for the first polygon
 * \param polygon2 Vector of Point for the second polygon
 * \return Boolean indicating whether the two polygons intersect
 */
bool do_intersect(const std::vector<Point>& polygon1, const std::vector<Point>& polygon2);


#endif

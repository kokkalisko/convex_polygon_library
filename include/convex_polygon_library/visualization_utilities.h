#include "convex_polygon_library/utilities.h"
#include <string>

/*!
 * Get the coordinates of a polygon in V-representation into two vectors
 * \param  polygon The polygon to be plotted as a vector of points
 * \return Two vectors of x and y coordinates
*/
std::vector<std::vector<double>> VisualizePolygon(const std::vector<Point>& polygon);

/*!
 * Get the coordinates of a polygon in V-representation into two vectors
 * \param  polygon The polygon to be plotted as a stack of points
 * \return Two vectors of x and y coordinates
*/
std::vector<std::vector<double>> VisualizePolygon(std::stack<Point> polygon);


std::vector<std::vector<double>> VisualizePoints(const std::vector<Point>& points);

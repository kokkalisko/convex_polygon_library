#include "convex_polygon_library/convex_hull.h"
#include <functional>
#include <algorithm>
#include <stdexcept>

// Pass by value in order to sort the vector later
std::stack<Point> convex_hull_from_points(std::vector<Point> points)
{
    // It is not possible to compute a convex hull with less than 3 points
    if (points.size() < 3)
        throw std::invalid_argument("Attempted to define a convex polygon with less than 3 points");

    // Check if all points are collinear
    bool allCollinear = CheckPointsCollinear(points);
    if (allCollinear)
        throw std::invalid_argument("Attempted to define a convex polygon when all points all collinear");

    // Find the points with the lowest and the highest y value: O(n) complexity
    // If more than one points have the lowest y value, then select the point with the lowest x value
    Point lowestPoint = points[0];
    int lowestDistanceFromBegin = 0;
    for (auto point = points.begin(); point != points.end(); ++point)
    {
        if ((lowestPoint.y > point->y) || (lowestPoint.y == point->y && lowestPoint.x > point->x))
        {
            lowestPoint = *point;
            lowestDistanceFromBegin = std::distance(points.begin(), point);
        }
    }
    // Erase the lowestPoint
    points.erase(points.begin()+lowestDistanceFromBegin);

    // Function that compares the polar angle with respect to the lowest point
    auto compareWithLowestPoint =  std::bind(CompareOrientation, lowestPoint, std::placeholders::_1, std::placeholders::_2);
    
    // Sort the remaining points by their polar angle: O(nlogn) complexity
    std::sort(points.begin(), points.end(), compareWithLowestPoint);

    // Stack containing the convex hull, where the points are oriented counter-clockwise
    std::stack<Point> convexHull = {};

    convexHull.push(lowestPoint);
    convexHull.push(points[0]);
    convexHull.push(points[1]);

    // Rearrange the points inside the stack: O(n) complexity
    for (size_t pointId = 2; pointId < points.size(); ++pointId) {
        Point top = convexHull.top();
        convexHull.pop();

        // Keep removing the top element of the stack while the angle formed by
        // next-on-top, top and point-in-question makes a non-counterclockwise turn
        while (ThreePointOrientation(convexHull.top(), top, points[pointId]) != 2)
        {
            top = convexHull.top();
            convexHull.pop();
        }
        convexHull.push(top);
        convexHull.push(points[pointId]);
    }

    return convexHull;
}
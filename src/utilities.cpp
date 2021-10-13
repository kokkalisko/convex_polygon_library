#include "convex_polygon_library/utilities.h"
#include <cmath>
#include <stdexcept>

void Vector::Normalize()
{
    // Calculate norm of the vector
    double norm = sqrt(x*x+y*y);
    if (norm == 0)
        throw std::runtime_error("Attempted to normalize a point");
    x /= norm;
    y /= norm;
}

double EuclideanDistance(const Point &p1, const Point &p2)
{
    return sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}

bool CheckPointsCollinear(const std::vector<Point> points)
{
    if (points.size() < 3)
        throw std::invalid_argument("Attempted to define a convex polygon with less than 3 points");

    for (size_t iter = 0; iter<points.size()-2; ++iter)
    {
        if (ThreePointOrientation(points[iter], points[iter+1], points[iter+2]))
            return false;
    }
    return true;
}

// 0 --> P, Q and R are collinear
// 1 --> Clockwise
// 2 --> Counterclockwise
int ThreePointOrientation(const Point &P, const Point &Q, const Point &R)
{
    if ((P==Q) || (Q==R) || (R==P))
        throw std::invalid_argument("Attempted to compute the orientation of three points when at least two of them are identical");

    double value = (Q.y - P.y) * (R.x - Q.x) -
                    (Q.x - P.x) * (R.y - Q.y);

    if (value == 0)
        return 0;               // collinear
    return (value > 0) ? 1 : 2; // clock or counterclock wise
}

bool CompareOrientation(const Point &P, const Point &Q, const Point &R)
{
    // Find orientation
    int threePointOrientation = ThreePointOrientation(P, Q, R);
    // If three points are collinear, then the nearest point should be placed first 
    if (threePointOrientation == 0)
        return (EuclideanDistance(P, Q) <= EuclideanDistance(P, R));

    return threePointOrientation == 2;
}

bool IsPointRightToTheEdge(const Point &tail, const Point &head, const Point &examinedPoint)
{
    return !(ThreePointOrientation(tail, head, examinedPoint) == 2); // counterclockwise
}

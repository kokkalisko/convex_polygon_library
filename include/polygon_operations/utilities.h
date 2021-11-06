#ifndef UTILITIES_H
#define UTILITIES_H

#include <vector>
#include <stack>
#include <algorithm>    // std::reverse

/*!
 * Class representing a 2D point
 */
struct Point
{
    double x;
    double y;

    /// Unique constructor for 2D point
    Point(double X, double Y): x(X), y(Y) {}

    /// Equality operator for two points
    bool operator==(const Point& p2) const {return (x == p2.x && y == p2.y);}

};

struct Vector: public Point
{
    /// Construction of a vector from a single point the coordinates of a single point
    Vector(double X, double Y): Point(X,Y) {}

    /// Construction of a vector from a single point 
    Vector(Point p): Point(p.x,p.y) {}

    /// Construction of a vector from two points where the first argument/point is the tail 
    /// and the second argument/point is the head
    Vector(Point p1, Point p2): Point(p2.x - p1.x, p2.y - p1.y) {}

    // Normalize vector
    void Normalize();

    /// Dot product operator for two vectors
    double operator*(const Vector &p2) {return x*p2.x + y*p2.y;}
};

/// Function that computes the Euclidean distance between two points
double EuclideanDistance(const Point& p1, const Point& p2);

/// Function that computes the Euclidean distance between two points
double DotProduct(const Point& p1, const Point& p2);

/// Function that checks if the given points are all collinear
bool CheckPointsCollinear(const std::vector<Point> points);

/*!
 * Find the orientation of the ordered triplet (P, Q, R).
 * If 0 is returned, the three points are collinear.
 * If 1 is returned, the three points are rotated clockwise
 * If 2 is returned, the three points are rotated counterclockwise
 * \param  P  The first point considered
 * \param  Q  The second point considered
 * \param  R  The second point considered
 * \return Integer indicating the rotation order of the points
 */
int ThreePointOrientation(const Point &P, const Point &Q, const Point &R);

/*!
 * Comparison function indicating whether the three points are rotated counterclowise.
 * Can be used for sorting
 * \param  P  The first point considered
 * \param  Q  The second point considered
 * \param  R  The third point considered
 * \return Boolean: True when P,Q,R are rotated counterclockwise
*/
bool CompareOrientation(const Point& P, const Point& Q, const Point& R);

/*!
 * Find whether a point is on the right of a vector formed by two points.
 * \param  tail The tail of the vector
 * \param  Qhead The head of the vector
 * \param  examinedPoint The point that needs to be check
 * \return Boolean: True when R point is strictly on the right of the PQ edge
*/
bool IsPointRightToTheEdge(const Point &tail, const Point &head, const Point &examinedPoint);

template<class T> 
std::vector<T> StackToVectorFromTop(std::stack<T> stackToCopy)
{
    std::vector<T> vectorFromStack;
    const auto stackSize = stackToCopy.size();
    vectorFromStack.reserve(stackSize);

    for (size_t iter = 0; iter < stackSize; ++iter)
    {
        vectorFromStack.emplace_back(stackToCopy.top());
        stackToCopy.pop();
    }

    return vectorFromStack;
}

template<class T> 
std::vector<T> StackToVectorFromBottom(std::stack<T> stackToCopy)
{
    std::vector<T> vectorFromStack = StackToVectorFromTop(stackToCopy);
    std::reverse(vectorFromStack.begin(), vectorFromStack.end());
    return vectorFromStack;
}

#endif

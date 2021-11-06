#include "polygon_operations/convex_polygon.h"
#include <stdexcept>

namespace Polygon 
{
    /// Calculate vectors expressing the normal lines to the polygon edges
    std::vector<Vector> CalculatePolygonEdgesNormals(const std::vector<Point>& polygon)
    {
        std::vector<Vector> normals;
        for(auto vertex = polygon.begin(); vertex != polygon.end(); ++vertex)
        {
            Vector edge(0,0);
            // Calculate the edges 
            if (vertex+1 == polygon.end())
                edge = Vector(*vertex, *(polygon.begin()));
            else
                edge = Vector(*vertex, *(vertex+1));
            
            // Calculate the normals of the edges 
            Vector normalToEdge = Vector(-edge.y,edge.x);
            // Normalize the normal vector and place into the vector
            normalToEdge.Normalize();
            normals.emplace_back(normalToEdge);
        }

        return normals;
    }

    /// Project all the points of the polygon to a single normal line using the dot product
    std::vector<double> PolygonProjectionsToLine(const Vector& line, const std::vector<Point>& polygon)
    {
        std::vector<double> projections;
        // Project points of polygon1 to normal
        for (auto point: polygon)
        {
            double dotProduct = Vector(point) * line;
            projections.emplace_back(dotProduct);
        }
        return projections;
    }

    /// Find whether the ranges of the projections to the normal overlap
    bool ProjectionsOverlap(const Vector& normal, const std::vector<Point>& polygon1, const std::vector<Point>& polygon2)
    {
        // Calculate all the projections of the vertices on the normal for polygon1
        std::vector<double> projectionsPolygon1 = PolygonProjectionsToLine(normal, polygon1);
        // Standard algorithm for finding minimum and maximum values
        double maximumProjection1 = *max_element(std::begin(projectionsPolygon1), std::end(projectionsPolygon1));
        double minumumProjection1 = *min_element(std::begin(projectionsPolygon1), std::end(projectionsPolygon1));

        // Calculate all the projections of the vertices on the normal for polygon1
        std::vector<double> projectionsPolygon2 = PolygonProjectionsToLine(normal, polygon2);
        // Standard algorithm for finding minimum and maximum values
        double maximumProjection2 = *max_element(std::begin(projectionsPolygon2), std::end(projectionsPolygon2));
        double minumumProjection2 = *min_element(std::begin(projectionsPolygon2), std::end(projectionsPolygon2));

        // Check whether the ranges of the projections are overlapping
        if ((maximumProjection2 >= minumumProjection1) && (maximumProjection1 >= minumumProjection2))
            return true;
        else 
            return false;
    }

    /// Find whether there is an overlap between two polygons using only the edges of one of them.
    /// Not definitive result
    bool CheckPolygonOverlaps(const std::vector<Point>& polygon1, const std::vector<Point>& polygon2)
    {
        // Calculate all the normal lines on the edges of the first polygon
        std::vector<Vector> normals = CalculatePolygonEdgesNormals(polygon1);

        // For every normal line, find whether the projections are overlapping
        for (auto& normal : normals)
        {
            bool projectionsOverlapping = ProjectionsOverlap(normal, polygon1, polygon2);
            if (!projectionsOverlapping)
            {
                return false;
                break;
            }
        }

        return true;
    }

}



bool point_is_in_polygon(const Point& pointInConsideration, std::stack<Point> convexPolygon)
{
    // It is not possible to define a polygon with less than 3 points
    if (convexPolygon.size() < 3)
        throw std::invalid_argument("Attempted to define a convex polygon with less than 3 points");

    const auto originalTopPoint = convexPolygon.top();
    const size_t polygonSize = convexPolygon.size();

    for (size_t iter = 0; iter < polygonSize-1; ++iter)
    {
        auto previousTop = convexPolygon.top();
        convexPolygon.pop();
        if (!IsPointRightToTheEdge(previousTop, convexPolygon.top(), pointInConsideration))
            return false;
    }
    if (!IsPointRightToTheEdge(convexPolygon.top(), originalTopPoint, pointInConsideration))
        return false;

    return true;
}

bool do_intersect(std::stack<Point> polygon1, std::stack<Point> polygon2)
{
    // Convert from stack to vector for both polygons
    auto polygon1Vector = StackToVectorFromBottom<Point>(polygon1);
    auto polygon2Vector = StackToVectorFromBottom<Point>(polygon2);
    
    return do_intersect(polygon1Vector, polygon2Vector);
}


bool do_intersect(const std::vector<Point>& polygon1, const std::vector<Point>& polygon2)
{
    if ((polygon1.size() < 3) || (polygon2.size() < 3))
        throw std::invalid_argument("Attempted to define a convex polygon with less than 3 points");

    // Check whether there is a separating axis i.e. the projections do not overlap for every polygon

    // First, consider only the edges of polygon1 
    bool allOverlap = Polygon::CheckPolygonOverlaps(polygon1, polygon2);
    // If a separating axis was found above, then return false since there is no need to further investigate
    // for polygon2
    if (!allOverlap)
        return false;

    // Now, consider only the edges of polygon2
    allOverlap = Polygon::CheckPolygonOverlaps(polygon2, polygon1);
    if (!allOverlap)
        return false;

    return true;
}
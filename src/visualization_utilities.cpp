#include "convex_polygon_library/visualization_utilities.h"

std::vector<std::vector<double>> VisualizePolygon(const std::vector<Point>& polygon)
{
    std::vector<double> xCoordinates, yCoordinates;
    xCoordinates.reserve(polygon.size()+1);
    yCoordinates.reserve(polygon.size()+1);

    for (auto& point: polygon)
    {
        xCoordinates.emplace_back(point.x);
        yCoordinates.emplace_back(point.y);
    }
    xCoordinates.emplace_back(polygon[0].x);
    yCoordinates.emplace_back(polygon[0].y);

    return {xCoordinates,yCoordinates};
}


std::vector<std::vector<double>>  VisualizePolygon(std::stack<Point> polygon)
{
    auto polygonVector = StackToVectorFromBottom<Point>(polygon);
    return VisualizePolygon(polygonVector);
}


std::vector<std::vector<double>> VisualizePoints(const std::vector<Point>& points)
{
    std::vector<double> xCoordinates, yCoordinates;
    for (auto& point: points)
    {
        xCoordinates.emplace_back(point.x);
        yCoordinates.emplace_back(point.y);
    }

    return {xCoordinates,yCoordinates};
}

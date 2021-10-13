#include "convex_polygon_library/convex_hull.h"
#include "convex_polygon_library/convex_polygon.h"
#include "convex_polygon_library/visualization_utilities.h"
#include "convex_polygon_library/matplotlibcpp.h"
namespace plt = matplotlibcpp;

#include <iostream>
#include <random>
#include <chrono>

std::random_device rd;  // Will be used to obtain a seed for the random number engine
std::mt19937 gen(rd()); // Standard mersenne_twister_engine seeded with rd()

void exampleRectangularWithRandomPoints()
{
    Point p1 = {1.0,1.0};
    Point p2 = {-1.0,1.0};
    Point p3 = {-1.0,-1.0};
    Point p4 = {1.0,-1.0};
    std::vector<Point> pointsForConvexHull = {p1,p2,p3,p4};

    // Generate 1000 random points from a uniform distribution inside the rectangular
    std::uniform_real_distribution<double> distribution(-1.0, 1.0);

    for (size_t iter = 0; iter < 1000; ++iter)
        pointsForConvexHull.emplace_back(Point(distribution(gen), distribution(gen)));

    std::stack<Point> convexHull = convex_hull_from_points(pointsForConvexHull);

    std::vector<std::vector<double>> polygonCoordinates = VisualizePolygon(convexHull);
    std::vector<std::vector<double>> pointsCoordinates = VisualizePoints(pointsForConvexHull);

    plt::plot(polygonCoordinates[0],polygonCoordinates[1], {{"label", "polygon"}});
    plt::scatter(pointsCoordinates[0],pointsCoordinates[1], {{"label", "random points"}, {"c", "r"}, {"linewidths", "2.5"}});
    plt::legend();
    plt::show();

}

void exampleRandomPolygonUniformDistribution()
{
    std::vector<Point> pointsForConvexHull = {};

    // Generate 100 random points from a uniform distribution inside a rectangular
    std::uniform_real_distribution<double> distribution(-2.0, 2.0);

    for (size_t iter = 0; iter < 100; ++iter)
        pointsForConvexHull.emplace_back(Point(distribution(gen), distribution(gen)));

    std::stack<Point> convexHull = convex_hull_from_points(pointsForConvexHull);

    std::vector<std::vector<double>> polygonCoordinates = VisualizePolygon(convexHull);
    std::vector<std::vector<double>> pointsCoordinates = VisualizePoints(pointsForConvexHull);

    plt::plot(polygonCoordinates[0],polygonCoordinates[1], {{"label", "polygon"}});
    plt::scatter(pointsCoordinates[0],pointsCoordinates[1], {{"label", "random points"}, {"c", "r"}, {"linewidths", "2.5"}});
    plt::legend();
    plt::show();
}

void exampleRandomPolygonNormalDistribution()
{
    std::vector<Point> pointsForConvexHull = {};

    // Generate 100 random points from a normal distribution 
      std::normal_distribution<double> distribution(5.0,2.0);

    for (size_t iter = 0; iter < 100; ++iter)
        pointsForConvexHull.emplace_back(Point(distribution(gen), distribution(gen)));

    std::stack<Point> convexHull = convex_hull_from_points(pointsForConvexHull);

    std::vector<std::vector<double>> polygonCoordinates = VisualizePolygon(convexHull);
    std::vector<std::vector<double>> pointsCoordinates = VisualizePoints(pointsForConvexHull);

    plt::plot(polygonCoordinates[0],polygonCoordinates[1], {{"label", "polygon"}});
    plt::scatter(pointsCoordinates[0],pointsCoordinates[1], {{"label", "random points"}, {"c", "r"}, {"linewidths", "2.5"}});
    plt::legend();
    plt::show();
}



int main()
{
    exampleRectangularWithRandomPoints();

    exampleRandomPolygonUniformDistribution();

    exampleRandomPolygonNormalDistribution();

}


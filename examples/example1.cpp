#include "polygon_operations/convex_hull.h"
#include "polygon_operations/convex_polygon.h"
#include "visualization_utilities.h"
#include "matplotlibcpp.h"
namespace plt = matplotlibcpp;

#include <iostream>
#include <random>
#include <chrono>

std::random_device rd;  // Will be used to obtain a seed for the random number engine
std::mt19937 gen(rd()); // Standard mersenne_twister_engine seeded with rd()

void exampleRectangularWithRandomPoints()
{
    // Create the 2x2 rectangular polygon
    Point p1 = {1.0,1.0};
    Point p2 = {-1.0,1.0};
    Point p3 = {-1.0,-1.0};
    Point p4 = {1.0,-1.0};
    std::vector<Point> pointsForConvexHull = {p1,p2,p3,p4};

    // Generate 1000 random points from a uniform distribution inside the rectangular
    std::uniform_real_distribution<double> distribution(-1.0, 1.0);

    for (size_t iter = 0; iter < 1000; ++iter)
        pointsForConvexHull.emplace_back(Point(distribution(gen), distribution(gen)));

    // Calculate the convex hull polygon
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

    // Calculate the convex hull polygon of the uniformly distributed points
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

    // Calculate the convex hull polygon of the normally distributed points
    std::stack<Point> convexHull = convex_hull_from_points(pointsForConvexHull);

    std::vector<std::vector<double>> polygonCoordinates = VisualizePolygon(convexHull);
    std::vector<std::vector<double>> pointsCoordinates = VisualizePoints(pointsForConvexHull);

    plt::plot(polygonCoordinates[0],polygonCoordinates[1], {{"label", "polygon"}});
    plt::scatter(pointsCoordinates[0],pointsCoordinates[1], {{"label", "random points"}, {"c", "r"}, {"linewidths", "2.5"}});
    plt::legend();
    plt::show();
}

void examplePointsInsideRectangular()
{
    // Create the 2x2 rectangular polygon
    Point p1 = {1.0,1.0};
    Point p2 = {-1.0,1.0};
    Point p3 = {-1.0,-1.0};
    Point p4 = {1.0,-1.0};
    std::vector<Point> pointsForConvexHull = {p1,p2,p3,p4};
    std::stack<Point> convexHull = convex_hull_from_points(pointsForConvexHull);

    std::normal_distribution<double> distribution(0.0,1.0);

    // Find which points are included in the polygon and which are not
    std::vector<Point> insideThePolygon, outsideThePolygon; 
    for (size_t iter = 0; iter < 100; ++iter)
    {
        Point randomPoint(distribution(gen), distribution(gen));
        if (point_is_in_polygon(randomPoint, convexHull))
            insideThePolygon.emplace_back(randomPoint);
        else 
            outsideThePolygon.emplace_back(randomPoint);
    }

    std::vector<std::vector<double>> polygonCoordinates = VisualizePolygon(convexHull);
    std::vector<std::vector<double>> pointsInsideThePolygon = VisualizePoints(insideThePolygon);
    std::vector<std::vector<double>> pointsOutsideThePolygon = VisualizePoints(outsideThePolygon);

    plt::plot(polygonCoordinates[0],polygonCoordinates[1], {{"label", "polygon"}});

    plt::scatter(pointsInsideThePolygon[0],pointsInsideThePolygon[1], {{"label", "inside the polygon"}, {"c", "r"}, {"linewidths", "2.5"}});
    plt::scatter(pointsOutsideThePolygon[0],pointsOutsideThePolygon[1], {{"label", "outside the polygon"}, {"c", "y"}, {"linewidths", "2.5"}});

    plt::legend();
    plt::show();
}


void exampleIntersectingRectangulars()
{
    // Generate two normal distributions
    std::normal_distribution<double> distribution1(0.0,1.0);
    std::normal_distribution<double> distribution2(2.0,1.0);

    // Randomly generated polygon number 1
    std::vector<Point> pointsForConvexHull1 = {};
    for (size_t iter = 0; iter < 10; ++iter)
    {
        Point randomPoint(distribution1(gen), distribution1(gen));
        pointsForConvexHull1.emplace_back(randomPoint);
    }
    std::stack<Point> convexHull1 = convex_hull_from_points(pointsForConvexHull1);

    std::vector<std::vector<double>> polygonCoordinates1 = VisualizePolygon(convexHull1);

    plt::plot(polygonCoordinates1[0],polygonCoordinates1[1], {{"label", "polygon1"}});

    // Randomly generated polygon number 2
    std::vector<Point> pointsForConvexHull2 = {};
    for (size_t iter = 0; iter < 10; ++iter)
    {
        Point randomPoint(distribution2(gen), distribution2(gen));
        pointsForConvexHull2.emplace_back(randomPoint);
    }
    std::stack<Point> convexHull2 = convex_hull_from_points(pointsForConvexHull2);

    std::vector<std::vector<double>> polygonCoordinates2 = VisualizePolygon(convexHull2);

    plt::plot(polygonCoordinates2[0],polygonCoordinates2[1], {{"label", "polygon2"}});

    // Check whether the two polygon intersect and print an appropriate message
    if (do_intersect(convexHull1, convexHull2))
        std::cout << "The two polygons do intersect" << std::endl;
    else
        std::cout << "The two polygons do not intersect" << std::endl;

    plt::legend();
    plt::show();
}

int main()
{
    std::cout << "Initiating examples" << std::endl;

    std::cout << "Here is a first example with a 2X2 rectangular with randomly generated points inside." << std::endl;
    std::cout << "The 4 corners of the rectangular are given by hand and the points are distributed uniformly." << std::endl;
    std::cout << "A convex hull polygon of these points is computed." << std::endl;
    exampleRectangularWithRandomPoints();

    std::cout << "This example finds a convex hull polygon out of points distributed with a uniform distribution." << std::endl;
    exampleRandomPolygonUniformDistribution();

    std::cout << "This example finds a convex hull polygon out of points distributed with a normal distribution." << std::endl;
    exampleRandomPolygonNormalDistribution();

    std::cout << "This example shows with red and yellow color the points that were found to be included and not included respectively inside the rectangular." << std::endl;
    std::cout << "The points are normally distributed and the points of the convex hull are." << std::endl;
    examplePointsInsideRectangular();

    std::cout << "This example shows whether two randomly generated polygons intercept with each other. It prints an appropriate message" << std::endl;
    for (size_t iter = 0; iter < 5; ++iter)
    {
        std::cout << "Iteration " << iter+1 << ": ";
        exampleIntersectingRectangulars();
    }
}


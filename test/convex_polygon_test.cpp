#include "convex_polygon_library/convex_polygon.h"
#include "convex_polygon_library/convex_hull.h"
#include "gtest/gtest.h"
#include <random>
#include <chrono>

std::random_device rd;  // Will be used to obtain a seed for the random number engine
std::mt19937 gen(rd()); // Standard mersenne_twister_engine seeded with rd()

// Utility functions
std::stack<Point> CreateRectangular()
{
    Point p1 = {-1.0, -1.0};
    Point p2 = {1.0, -1.0};
    Point p3 = {1.0, 1.0};
    Point p4 = {-1.0, 1.0};
    std::stack<Point> convexPolygon = {};
    convexPolygon.push(p1);
    convexPolygon.push(p2);
    convexPolygon.push(p3);
    convexPolygon.push(p4);

    return convexPolygon;
}



TEST(ConvexPolygonIncludePoint, Invalid_arguments_exception) 
{
    Point p1 = {0, 0};
    Point p2 = {3, 4};
    std::stack<Point> convexHull = {};
    convexHull.push(p1);
    convexHull.push(p2);

    Point pInConsideration = {1, 0};

    EXPECT_THROW({
        try
        {
            bool pointInside = point_is_in_polygon(pInConsideration, convexHull);
        }
        catch (std::invalid_argument const& ex)
        {
            // and this tests that it has the correct message
            EXPECT_STREQ("Attempted to define a convex polygon with less than 3 points", ex.what());
            throw;
        }
    }, std::invalid_argument);
}

TEST(ConvexPolygonIncludePoint, Positive_test_random) 
{
    std::stack<Point> convexPolygon = CreateRectangular();

    // Generate 10000 points inside the unitary rectangular
    std::uniform_real_distribution<double> distribution(-1.0, 1.0);

    std::vector<Point> randomPoints = {};
    for (size_t iter = 0; iter < 10000; ++iter)
        randomPoints.emplace_back(Point(distribution(gen), distribution(gen)));

    for (auto randomPoint : randomPoints)
        ASSERT_TRUE(point_is_in_polygon(randomPoint, convexPolygon));
}

TEST(ConvexPolygonIncludePoint, Negative_test_random) 
{
    std::stack<Point> convexPolygon = CreateRectangular();

    // Generate 10000 points inside the unitary rectangular
    std::uniform_real_distribution<double> distribution(-10.0, 10.0);

    std::vector<Point> randomPoints = {};
    while (randomPoints.size()<10000)
    {
        Point randomPoint(distribution(gen), distribution(gen));
        if (randomPoint.x >= -1 && randomPoint.x < 1 &&
            randomPoint.y >= -1 && randomPoint.y < 1) 
            continue;

        randomPoints.emplace_back(randomPoint);
    }

    for (auto randomPoint : randomPoints)
        ASSERT_FALSE(point_is_in_polygon(randomPoint, convexPolygon));
}

TEST(ConvexPolygonIncludePoint, On_the_edge)
{
    std::stack<Point> convexPolygon = CreateRectangular();

    Point pointOnTheEdge(-1,0);
    ASSERT_TRUE(point_is_in_polygon(pointOnTheEdge, convexPolygon));

    Point pointOnTheEdgeOutside(-1+1e10,0);
    ASSERT_FALSE(point_is_in_polygon(pointOnTheEdgeOutside, convexPolygon));
}

TEST(ConvexPolygonIncludePoint, Time_comparison1)
{
    // In case this test becomes flaky, increase maximumIterations
    const size_t maximumIterations = 10;

    std::stack<Point> convexPolygon =  CreateRectangular();

    auto start = std::chrono::system_clock::now();
    for (size_t iter = 0; iter < maximumIterations; ++iter)
        point_is_in_polygon({0.0, 0.0}, convexPolygon);
    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> timeWhenIncluded = end - start;

    start = std::chrono::system_clock::now();
    for (size_t iter = 0; iter < maximumIterations; ++iter)
        point_is_in_polygon({2,2}, convexPolygon);
    end = std::chrono::system_clock::now();
    std::chrono::duration<double> timeWhenDoNotIncluded = end - start;

    ASSERT_GT(timeWhenIncluded.count(), timeWhenDoNotIncluded.count());
}

TEST(ConvexPolygonIncludePoint, Time_comparison2)
{
    std::stack<Point> convexPolygon =  CreateRectangular();

    auto start = std::chrono::system_clock::now();
    point_is_in_polygon({0.0, 0.0}, convexPolygon);
    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> timeWhenIncluded = end - start;

    start = std::chrono::system_clock::now();
    point_is_in_polygon({-1,0.5}, convexPolygon);
    end = std::chrono::system_clock::now();
    std::chrono::duration<double> timeWhenDoNotIncluded = end - start;

    // In case this test becomes flaky, increase tolerance/abs_error
    EXPECT_NEAR(timeWhenIncluded.count(), timeWhenDoNotIncluded.count(), 1e-6);
}

TEST(ConvexPolygonIntersect, Invalid_arguments_exception) 
{
    std::vector<Point> polygon1 = {{-1,-1}, {1,1}};
    std::vector<Point> polygon2 = {{-1,-1}, {1,-1}, {1,1}, {-1,1}};

    EXPECT_THROW({
        try
        {
            bool intersectionExists = do_intersect(polygon1, polygon2);
        }
        catch (std::invalid_argument const& ex)
        {
            // and this tests that it has the correct message
            EXPECT_STREQ("Attempted to define a convex polygon with less than 3 points", ex.what());
            throw;
        }
    }, std::invalid_argument);
}

TEST(ConvexPolygonIntersect, Intersection_existence) 
{
    std::stack<Point> polygon1 = CreateRectangular();

    Point p1 = {0.0, 0.0};
    Point p2 = {2.0, 0.0};
    Point p3 = {2.0, 2.0};
    Point p4 = {0.0, 2.0};

    std::stack<Point> polygon2 = convex_hull_from_points({p1,p2,p3,p4});

    ASSERT_TRUE(do_intersect(polygon1, polygon2));
}

TEST(ConvexPolygonIntersect, Intersection_non_existence) 
{
    std::stack<Point> polygon1 = CreateRectangular();

    Point p1 = {1.5, 1.0};
    Point p2 = {2.5, 1.0};
    Point p3 = {1.5, -1.0};
    Point p4 = {2.5, -1.0};

    std::stack<Point> polygon2 = convex_hull_from_points({p1,p2,p3,p4});

    ASSERT_FALSE(do_intersect(polygon1, polygon2));
}

TEST(ConvexPolygonIntersect, Intersection_polygon_contained) 
{
    std::stack<Point> polygon1 = CreateRectangular();

    Point p1 = {-0.5, -0.5};
    Point p2 = {0.5, -0.5};
    Point p3 = {0.5, 0.5};
    Point p4 = {-0.5, 0.5};

    std::stack<Point> polygon2 = convex_hull_from_points({p1,p2,p3,p4});

    ASSERT_TRUE(do_intersect(polygon1, polygon2));
}

TEST(ConvexPolygonIntersect, Time_comparison)
{
    // In case this test becomes flaky, increase maximumIterations
    const size_t maximumIterations = 1;
    std::stack<Point> polygon1 = CreateRectangular();

    Point p1 = {0.0, 0.0};
    Point p2 = {2.0, 0.0};
    Point p3 = {2.0, 2.0};
    Point p4 = {0.0, 2.0};

    std::stack<Point> polygon2 = convex_hull_from_points({p1,p2,p3,p4});

    auto start = std::chrono::system_clock::now();
    for (size_t iter = 0; iter < maximumIterations; ++iter)
        do_intersect(polygon1, polygon2);
    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> timeWhenIntersect = end - start;

    Point p5 = {1.5, 1.0};
    Point p6 = {2.5, 1.0};
    Point p7 = {1.5, -1.0};
    Point p8 = {2.5, -1.0};

    std::stack<Point> polygon3 = convex_hull_from_points({p5,p6,p7,p8});

    start = std::chrono::system_clock::now();
    for (size_t iter = 0; iter < maximumIterations; ++iter)
        do_intersect(polygon1, polygon3);
    end = std::chrono::system_clock::now();
    std::chrono::duration<double> timeWhenDoNotIntersect = end - start;

    ASSERT_GT(timeWhenIntersect.count(), timeWhenDoNotIntersect.count());
}

TEST(ConvexPolygonIntersect, On_the_edge)
{
    std::stack<Point> polygon1 = CreateRectangular();

    Point p1 = {1.0, -1.0};
    Point p2 = {2.0, -1.0};
    Point p3 = {2.0, 1.0};
    Point p4 = {1.0, 1.0};

    std::stack<Point> polygon2 = convex_hull_from_points({p1,p2,p3,p4});

    ASSERT_TRUE(do_intersect(polygon1, polygon2));
}

int main(int argc, char **argv) 
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

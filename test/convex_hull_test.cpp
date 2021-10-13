#include "convex_polygon_library/convex_hull.h"
#include "gtest/gtest.h"
#include <random>
#include <chrono>

std::random_device rd;  // Will be used to obtain a seed for the random number engine
std::mt19937 gen(rd()); // Standard mersenne_twister_engine seeded with rd()

TEST(ConvexHull, Invalid_arguments_exception) 
{
    Point p1 = {0,0};
    Point p2 = {3,4};

    EXPECT_THROW({
        try
        {
            std::stack<Point> convexHull = convex_hull_from_points({p1,p2});
        }
        catch (std::invalid_argument const& ex)
        {
            // and this tests that it has the correct message
            EXPECT_STREQ("Attempted to define a convex polygon with less than 3 points", ex.what());
            throw;
        }
    }, std::invalid_argument);   
}

TEST(ConvexHull, Simple_rectangular)
{
    Point p1 = {1.0,1.0};
    Point p2 = {-1.0,1.0};
    Point p3 = {-1.0,-1.0};
    Point p4 = {1.0,-1.0};
    Point p0 = {0.0,0.0};
    const std::vector<Point> pointsForConvexHull = {p1,p2,p3,p4,p0};

    std::stack<Point> convexHull = convex_hull_from_points(pointsForConvexHull);

    ASSERT_TRUE(p2==convexHull.top());
    convexHull.pop();
    ASSERT_TRUE(p1==convexHull.top());
    convexHull.pop();
    ASSERT_TRUE(p4==convexHull.top());
    convexHull.pop();
    ASSERT_TRUE(p3==convexHull.top());
    convexHull.pop();
    ASSERT_TRUE(convexHull.empty());
}

TEST(ConvexHull, Unitary_rectangular_with_random_points)
{
    Point p1 = {0.0,1.0};
    Point p2 = {1.0,1.0};
    Point p3 = {1.0,0.0};
    Point p4 = {0.0,0.0};

    std::vector<Point> pointsForConvexHull = {p1,p2,p3,p4};

    auto start = std::chrono::system_clock::now();
    std::stack<Point> convexHull = convex_hull_from_points(pointsForConvexHull);
    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> diff_4_points = end - start;
    
    // Generate 10000 points inside the unitary rectangular
    std::uniform_real_distribution<double> distribution(0.0, 1.0);

    for (size_t iter = 0; iter < 10000; ++iter)
    {
        Point pRandom = {distribution(gen), distribution(gen)};
        pointsForConvexHull.emplace_back(pRandom);
    }

    start = std::chrono::system_clock::now();
    convex_hull_from_points(pointsForConvexHull);
    end = std::chrono::system_clock::now();
    std::chrono::duration<double> diff_10004_points = end - start;

    ASSERT_TRUE(p1==convexHull.top());
    convexHull.pop();
    ASSERT_TRUE(p2==convexHull.top());
    convexHull.pop();
    ASSERT_TRUE(p3==convexHull.top());
    convexHull.pop();
    ASSERT_TRUE(p4==convexHull.top());
    convexHull.pop();
    ASSERT_TRUE(convexHull.empty());

    ASSERT_LT(diff_4_points.count(), diff_10004_points.count());
}

TEST(ConvexHull, Random_polygons)
{
    std::vector<Point> pointsForConvexHull = {};
    
    // Generate 10000 points inside the unitary rectangular
    std::uniform_real_distribution<double> distribution(0.0, 1.0);

    for (size_t iter = 0; iter < 10000; ++iter)
    {
        Point pRandom = {distribution(gen), distribution(gen)};
        pointsForConvexHull.emplace_back(pRandom);
    }

    // Calculate the convex hull of these random 10000 points
    std::stack<Point> convexHull = convex_hull_from_points(pointsForConvexHull);

    const size_t convexHullVertices = convexHull.size();
    ASSERT_LE(convexHull.empty(), convexHullVertices);

    for (size_t vertexId = 0; vertexId < convexHullVertices; ++vertexId)
    {
        ASSERT_GE(convexHull.top().x, 0);
        ASSERT_LT(convexHull.top().x, 1);
        ASSERT_GE(convexHull.top().y, 0);
        ASSERT_LT(convexHull.top().y, 1);
        convexHull.pop();
    }
}

TEST(ConvexHull, Unitary_rectangular_with_additional_external_point)
{
    Point p1 = {0.0,1.0};
    Point p2 = {1.0,1.0};
    Point p3 = {1.0,0.0};
    Point p4 = {0.0,0.0};
    Point pExternal = {2.0,1.5};

    std::vector<Point> pointsForConvexHull = {p1,p2,p3,p4,pExternal};
    std::stack<Point> convexHull = convex_hull_from_points(pointsForConvexHull);
    const size_t convexHullVertices = convexHull.size();

    bool vertexOutside = false;
    for (size_t vertexId = 0; vertexId < convexHullVertices; ++vertexId)
    {
        if (convexHull.top().x < 0 || convexHull.top().x >= 1 ||
            convexHull.top().y < 0 || convexHull.top().y >= 1) 
            vertexOutside = vertexOutside || true;
        convexHull.pop();
    }

    ASSERT_TRUE(vertexOutside);
}

TEST(ConvexHull, Collinear_points)
{
    Point p1 = {0,0};
    Point p2 = {1,1};
    Point p3 = {2,2};
    Point p4 = {3,3};

    EXPECT_THROW({
        try
        {
            std::stack<Point> convexHull = convex_hull_from_points({p1,p2,p3,p4});
        }
        catch (std::invalid_argument const& ex)
        {
            // and this tests that it has the correct message
            EXPECT_STREQ("Attempted to define a convex polygon when all points all collinear", ex.what());
            throw;
        }
    }, std::invalid_argument);   
}


int main(int argc, char **argv) 
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
